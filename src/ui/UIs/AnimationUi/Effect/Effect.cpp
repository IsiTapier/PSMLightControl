#include "Effect.h"

std::vector<Effect*> Effect::effects;

Effect::Effect(const char* name, DMXDevice* device, short speed, float increase, byte spreadLeft, byte spreadRight, Direction direction, byte overrideValue, bool doOverlap) : name(name), parameter({device, speed, increase, spreadLeft, spreadRight, direction, overrideValue, doOverlap}) {
    effects.push_back(this);
}

std::vector<Effect*> Effect::getEffects() {
    return effects;
}

bool Effect::getActive() {
    return active;
}

DMXDevice* Effect::getDevice() {
    return parameter.device;
}

void Effect::toggle() {
    active = !active;
    if(!active) {
        parameter.device->setOutputCalculation([](byte channel, byte device, byte value){return value;});
        vTaskDelete(handle);
        return;
    }

    // turn of all other effects for same device
    for(Effect* effect : getEffects())
        if(effect->getActive() && effect->getDevice() == getDevice())
            effect->toggle();

    xTaskCreate([](void* parm){
        Parameter* p = (Parameter*) parm;
        DMXDevice* d = p->device;
        uint8_t devices = d->getDevices(true);
        if(p->direction == OUT || p->direction == IN) devices/=2;
        for(;;) {
            for(float j = 0; j < devices; j+=p->increase) {
                float current;
                switch(p->direction) {
                    case RIGHT: current = devices-j;   break;
                    case OUT:   current = devices-j;   break;
                    default:    current = j;           break;
                }
                d->setOutputCalculation([p, d, current, devices](byte channel, byte device, byte value) {
                    // check channel type

                    // TODO

                    // byte i = d->getFormatSize()-channel-1;
                    // if(!FORMATEQUALS(R) && !FORMATEQUALS(G) && !FORMATEQUALS(B) && !FORMATEQUALS(W)) return value;

                    // get device position
                    byte x = floor(channel/d->getFormatSize(true))+d->getRepeat()*device;
                    // Serial.print(floor(channel/(d->getFormatSize()+d->getDistance()))); Serial.print(" "); Serial.println(channel);
                    
                    if((p->direction == OUT || p->direction == IN) && x > devices) x = 2*devices-x;
                    float distance = x-current;
                    
                    // check overlap
                    if(p->doOverlap) {
                        if(distance <= -devices+p->spreadRight) SETABSOLUTESMALLER(distance, distance+devices);
                        if(distance >=  devices-p->spreadLeft)  SETABSOLUTESMALLER(distance, distance-devices);
                    }
                    
                    // prevent false spread
                    if(distance < -p->spreadLeft) return value;
                    if(distance > p->spreadRight) return value;
                    if(x>devices && ((p->direction == IN && distance < 0) || (p->direction == OUT && distance > 0))) return value;

                    // calculate new brightness
                    float percentage = 1-(distance<0 ? abs(distance/(float)p->spreadLeft) : distance/(float)p->spreadRight);
                    return (byte) MAX(percentage*p->overrideValue, (1-percentage)*value);
                });
                vTaskDelay(p->speed);
            }
        }
    }, name, 1024, &parameter, 6, &handle);
}

std::vector<MultiEffect*> MultiEffect::effects;

MultiEffect::MultiEffect(const char* name, DMXDevice* device, short speed, std::vector<EffectPoint*> effectPoints, byte overrideValue, bool doOverlap) : name(name), parameter({device, speed, effectPoints, overrideValue, doOverlap}) {
    effects.push_back(this);
}

std::vector<MultiEffect*> MultiEffect::getEffects() {
    return effects;
}

bool MultiEffect::getActive() {
    return active;
}

DMXDevice* MultiEffect::getDevice() {
    return parameter.device;
}

void MultiEffect::toggle() {
    active = !active;
    if(!active) {
        parameter.device->setOutputCalculation([](byte channel, byte device, byte value){return value;});
        vTaskDelete(handle);
        return;
    }

    // turn of all other effects for same device
    for(MultiEffect* effect : getEffects())
        if(effect->getActive() && effect->getDevice() == getDevice())
            effect->toggle();

    xTaskCreate([](void* parm){
        Parameter* p = (Parameter*) parm;
        DMXDevice* d = p->device;
        for(;;) {
            for(EffectPoint* effect : p->effectPoints) {
                effect->next();
                // if((p->direction==IN || p->direction==OUT) && effect->currentX > effect->endX/2) effect->currentX=0;
                // float current;
                // switch(p->direction) {
                //     case RIGHT: current = effect->endX-effect->currentX;    break;
                //     case OUT:   current = effect->endX/2-effect->currentX;  break;
                //     default:    current = effect->currentX;                 break;
                // }
            }
            d->setOutputCalculation([p, d](byte channel, byte device, byte value) {
                // check channel type

                // TODO

                // byte i = (d->getFormatSize()-channel-1)%d->getFormatSize(true);
                // if(!FORMATEQUALS(R) && !FORMATEQUALS(G) && !FORMATEQUALS(B) && !FORMATEQUALS(W)) return value;

                // get device position
                byte x = floor(channel/d->getFormatSize(true))+d->getRepeat()*device;
                // Serial.print(floor(channel/(d->getFormatSize()+d->getDistance()))); Serial.print(" "); Serial.println(channel);
                
                // if((p->direction == OUT || p->direction == IN) && x > effect->endX/2) x = effect->endX-x;
                float percentage = 0;
                for(EffectPoint* effect : p->effectPoints)
                    SETMAX(percentage, effect->getPercentage(p->doOverlap, x));

                return (byte) MAX(percentage*p->overrideValue, (1-percentage)*value);
            });
            vTaskDelay(p->speed);
        }
    }, name, 1024, &parameter, 6, &handle);
}

EffectButton::EffectButton(const char* name, std::vector<DMXDevice*> devices, short speed, float increase, byte spreadLeft, byte spreadRight, Effect::Direction direction, byte overrideValue, bool doOverlap) : Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
    [this](){
        toggle();
        return 0;
    },
    {
        new Text(ContainerProperties(), TextProperties(), name)
    }), name(name) {
    for(DMXDevice* device : devices)
        effects.push_back(new Effect(name, device, speed, increase, spreadLeft, spreadRight, direction, overrideValue, doOverlap));
}

void EffectButton::toggle() {
    for(Effect* effect : effects)
        effect->toggle();
}