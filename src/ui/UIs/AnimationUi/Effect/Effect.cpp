#include "Effect.h"
#include "Devices.h"

std::vector<Effect*> Effect::effects = {};
uint16_t Effect::speed = DEFAULT_TAB_SPEED;

Effect::Effect(const char* name, DMXDevice* device, byte defaultSpeed, float increase, byte spreadLeft, byte spreadRight, Direction direction, byte overrideValue, bool doOverlap, bool rainbow) : name(name), parameter({device, defaultSpeed, increase, spreadLeft, spreadRight, direction, overrideValue, doOverlap, rainbow}) {
    // NOT WORKING
    effects.push_back(this);
    addEffect(this);
}

// NOT WORKING
void Effect::addEffect(Effect* effect) {
    effects.push_back(effect);
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

void Effect::setSpeed(uint16_t speed) {
    Effect::speed = speed;
}

uint16_t Effect::getSpeed() {
    return speed;
}

void Effect::setSpeedMultiplier(float multiplier) {
    parameter.speedMultiplier = multiplier;
}

void Effect::toggle(bool value) {
    active = value;
    if(!active) {
        parameter.device->setOutputCalculation([](byte channel, byte device, byte value){return value;});
        if(handle!=NULL) vTaskDelete(handle);
        handle = NULL;
        return;
    }

    bool isAdded = false;

    // turn of all other effects for same device
    for(Effect* effect : getEffects()) {
        if(effect == this) {
            isAdded = true;
            continue;
        }
        if(effect->getActive() && effect->getDevice() == getDevice())
            effect->toggle(false);
    }

    if(!isAdded) effects.push_back(this);

    xTaskCreate([](void* parm){
        Parameter* p = (Parameter*) parm;
        DMXDevice* d = p->device;
        uint8_t devices = d->getDevices(true);
        if(p->direction == OUT || p->direction == IN) devices/=2;
        for(;;) {
            for(float j = 0; j < devices; j+=p->increase) {
                if(p->increase == RANDOM) j = random(0, devices);
                float current;
                switch(p->direction) {
                    case LEFT: current = devices-j;   break;
                    case OUT:   current = devices-j;   break;
                    default:    current = j;           break;
                }
                d->setOutputCalculation([p, d, current, devices](byte channel, byte device, byte value) {
                    // check channel type
                    // Serial.println();

                    // TODO

                    // byte i = d->getFormatSize()-channel-1;
                    // if(!FORMATEQUALS(R) && !FORMATEQUALS(G) && !FORMATEQUALS(B) && !FORMATEQUALS(W)) return value;

                    // get device position
                    // Serial.print(" channel: ");
                    // Serial.print(channel);
                    // Serial.print(" device: ");
                    // Serial.print(device);
                    // Serial.print(" formatsize: ");
                    // Serial.print(d->getFormatSize(true));
                    byte x = floor(channel/d->getFormatSize(true))+d->getRepeat()*device;
                    // Serial.print(floor(channel/(d->getFormatSize()+d->getDistance()))); Serial.print(" "); Serial.println(channel);
                    // Serial.print(" current: ");
                    // Serial.print(current);
                    // Serial.print(" x: ");
                    // Serial.print(x);
                    if((p->direction == OUT || p->direction == IN) && x > devices) x = 2*devices-x;
                    float distance = x-current;

                    if(p->increase == RANDOM) {
                        if(random(0, 4) == 0) distance = 0;
                        else distance = 1;
                    }

                    // Serial.print(" distance: ");
                    // Serial.print(distance);
                    
                    // check overlap
                    if(p->doOverlap) {
                        if(distance <= -devices+p->spreadRight) SETABSOLUTESMALLER(distance, distance+devices);
                        if(distance >=  devices-p->spreadLeft)  SETABSOLUTESMALLER(distance, distance-devices);
                    }
                    // Serial.print(" ");
                    // Serial.print(bars.getDevices(true)/4.);
                    // Serial.print(" spreadl: ");
                    // Serial.print(p->spreadLeft);
                    // Serial.print(" spreadr: ");
                    // Serial.print(p->spreadRight);
                    // prevent false spread
                    if(p->rainbow) vTaskDelay(2);
                    // if(p->increase==0) vTaskDelay(1);
                    if(distance < -p->spreadLeft) return value;
                    if(distance > p->spreadRight) return value;
                    if(x>devices && ((p->direction == IN && distance < 0) || (p->direction == OUT && distance > 0))) return value;
                    // Serial.print(" percentage: ");
                    // calculate new brightness
                    float percentage;
                    if(distance == 0) percentage = 1;
                    else percentage = 1-(distance<0 ? abs(distance)/((float)p->spreadLeft) : distance/((float)p->spreadRight));
                    uint8_t outval = MAX(percentage*p->overrideValue, (1-percentage)*value);
                    return outval;
                });
                // if(p->increase == RANDOM) vTaskDelete(NULL); 
                if(p->increase == RANDOM) vTaskDelay(1000);
                else vTaskDelay(Effect::getSpeed()/p->defaultSpeed*p->increase/p->speedMultiplier);
            }
        }
    }, name, 1024, &parameter, 6, &handle);
}

std::vector<MultiEffect*> MultiEffect::meffects;

MultiEffect::MultiEffect(const char* name, DMXDevice* device, short speed, std::vector<EffectPoint*> effectPoints, byte overrideValue, bool doOverlap) : name(name), mparameter({device, speed, effectPoints, overrideValue, doOverlap}) {
    meffects.push_back(this);
}

std::vector<MultiEffect*> MultiEffect::getEffects() {
    return meffects;
}

bool MultiEffect::getActive() {
    return active;
}

DMXDevice* MultiEffect::getDevice() {
    return mparameter.device;
}

void MultiEffect::toggle() {
    active = !active;
    if(!active) {
        mparameter.device->setOutputCalculation([](byte channel, byte device, byte value){return value;});
        vTaskDelete(handle);
        return;
    }

    // turn of all other effects for same device
    for(MultiEffect* effect : getEffects())
        if(effect->getActive() && effect->getDevice() == getDevice())
            effect->toggle();

    xTaskCreate([](void* parm){
        MParameter* p = (MParameter*) parm;
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
    }, name, 1024, &mparameter, 6, &handle);
}

EffectButton::EffectButton(const char* name, std::vector<DMXDevice*> devices, short speed, float increase, byte spreadLeft, byte spreadRight, Effect::Direction direction, byte overrideValue, bool doOverlap, bool rainbow) : Button(ContainerProperties(Size(60), Size(60), Spacing(7, 7), Spacing(0), Spacing(2)), ButtonProperties(),
    [this](){
        toggle(!getActive());
        return 0;
    },
    {
        new Text(ContainerProperties(), TextProperties(), name)
    }), name(name) {
    for(DMXDevice* device : devices) {
        Effect* effect = new Effect(name, device, speed, increase, spreadLeft, spreadRight, direction, overrideValue, doOverlap, rainbow);
        Effect::addEffect(effect);
        effects.push_back(effect);
    }
}

void EffectButton::toggle(bool value) {
    for(Effect* effect : effects)
        effect->toggle(value);
}

void EffectButton::setMultiplier(float multiplier) {
    for(Effect* effect : effects)
        effect->setSpeedMultiplier(multiplier);
}

bool EffectButton::getActive() {
    return effects[0]->getActive();
}

EffectGroup::EffectGroup(const char* name, std::vector<float> multipliers, std::vector<EffectButton*> effectButtons) : Container(*ContainerProperties(Size(15+(60+15)*effectButtons.size()), Size(74+30), Spacing(0, 10)).setInvisible(true), {}), effectButtons(effectButtons) {
    Container* header = new Container(*ContainerProperties(Size(1., -1), Size(30)).setInvisible(true), {});
    header->addContent(new Container(*ContainerProperties(Size(50), Size(30-2*2), Spacing(7, 2)).setInvisible(true), {new Text(ContainerProperties(), TextProperties(), name)}));
    for(float multiplier : multipliers)
        header->addContent(new Button(ContainerProperties(Size(30), Size(30-2*2), Spacing(7, 2), Spacing(0), Spacing(1)), ButtonProperties(), [effectButtons, multiplier](){for(EffectButton* button : effectButtons) button->setMultiplier(multiplier); return 0;}, {new Text(ContainerProperties(), TextProperties(), String(multiplier, 1)+"x")}));
    addContent(header);
    for(EffectButton* button : effectButtons)
        addContent((Container*) button);
    
}


