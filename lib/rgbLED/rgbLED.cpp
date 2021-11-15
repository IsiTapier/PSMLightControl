/*
 rgbLED.cpp - rgbLED-Library for Librarys.
*/

#include "rgbLED.h"


RGBLed::RGBLed(uint8_t rPin, uint8_t gPin, uint8_t bPin) : _rPin(rPin), _gPin(gPin), _bPin(bPin) {
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
}

void RGBLed::writeRGB(uint8_t red, uint8_t green, uint8_t blue) {
    if(red == _rVal && green == _gVal && blue == _bVal)
        return;
    _rVal = red;
    _gVal = green;
    _bVal = blue;
    update();
}

void RGBLed::writeRed(uint8_t value) {
    if(value == _rVal)
        return;
    _rVal = value;
    update();
}

void RGBLed::writeGreen(uint8_t value) {
    if(value == _gVal)
        return;
    _gVal = value;
    update();
}

void RGBLed::writeBlue(uint8_t value) {
    if(value == _bVal)
        return;
    _bVal = value;
    update();
}

void RGBLed::writeWhite(uint8_t value) {
    if(value == _wVal)
        return;
    _wVal = value;
    update();
}

void RGBLed::writeOff() {
    writeRGB(0, 0, 0);
}

void RGBLed::update() {
    analogWrite(_rPin, max(_rVal, _wVal));
    analogWrite(_gPin, max(_gVal, _wVal));
    analogWrite(_bPin, max(_bVal, _wVal));
}