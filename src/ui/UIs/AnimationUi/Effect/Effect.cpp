#include "Effect.h"

Effect::Effect(DMXDevice* device, byte overrideValue, short speed, byte spread, float increase, Direction direction, bool doOverlap) : _parameter({device, overrideValue, speed, spread, increase, direction, doOverlap}) {

}

void Effect::toggle() {
    active = !active;
    if(!active) {
        _parameter._device->setOutputCalculation([](byte channel, byte device, byte value){return value;});
        vTaskDelete(handle);
        return;
    }

    xTaskCreate([](void* parm){
        Parameter* parms = (Parameter*) parm;
        DMXDevice* d = parms->_device;
        uint64_t _format = d->getFormat();
        for(;;) {
            for(float j = parms->_direction==LEFT?d->getDevices(true)-1:0; j < d->getDevices(true) && j >= 0; j+=(parms->_direction==LEFT?-1:1)*parms->_increase) {
                d->setOutputCalculation([j, _format, parms, d](byte channel, byte device, byte value) {
                    // check channel type
                    byte i = d->getFormatSize()-channel-1;
                    // if(!FORMAT_EQUALS(R) && !FORMAT_EQUALS(G) && !FORMAT_EQUALS(B) && !FORMAT_EQUALS(W)) return value;

                    // get device position
                    byte x = floor(channel/(d->getFormatSize()+d->getDistance()))+d->getRepeat()*device;
                    // Serial.print(floor(channel/(d->getFormatSize()+d->getDistance()))); Serial.print(" "); Serial.println(channel);
                    float distance = x-j;

                    // check overlap
                    // isssue if spread > device count
                    if(parms->_doOverlap) {
                        if(distance<0 && distance <= -d->getDevices(true)+parms->_spread) distance += d->getDevices(true);
                        if(distance>0 && distance >= d->getDevices(true)-parms->_spread) distance += -d->getDevices(true);
                    }
                    
                    // prevent false spread
                    if(parms->_direction == LEFT && distance < 0) return value;
                    if(parms->_direction == RIGHT && distance > 0) return value;
                    if(abs(distance) > parms->_spread) return value;

                    // calculate new brightness
                    float percentage = 1-abs(distance/parms->_spread);
                    return (byte) MAX(percentage*parms->_overrideValue, (1-percentage)*value);
                });
                vTaskDelay(parms->_speed);
            }
        }
    }, "Lauflicht", 1024, &_parameter, 6, &handle);
}