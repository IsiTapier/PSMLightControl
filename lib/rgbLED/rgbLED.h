/*
  rgbLED.h - rgbLED-Library for Airduino.
*/

#ifndef rgbLED_h
#define rgbLED_h

#include "Arduino.h"
#include "analogWrite.h"

class RGBLed {
    public:
        RGBLed(uint8_t rPin, uint8_t gPin, uint8_t bPin);
        void writeRGB(uint8_t red, uint8_t green, uint8_t blue);
        void writeRed(uint8_t value = UINT8_MAX);
        void writeGreen(uint8_t value = UINT8_MAX);
        void writeBlue(uint8_t value = UINT8_MAX);
        void writeWhite(uint8_t value = UINT8_MAX);
        void writeOff();

    private:
        uint8_t _rPin, _gPin, _bPin,
                _rVal = 0, _gVal = 0, _bVal = 0, _wVal = 0;
        void update();

};

#endif