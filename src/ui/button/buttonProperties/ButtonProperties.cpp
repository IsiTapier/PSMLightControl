/*
 ButtonProperties.cpp - ButtonProperties-Library for Librarys.
*/

#include "ButtonProperties.h"

ButtonProperties::ButtonProperties(uint16_t pressedColor, Spacing touchExtension) : _pressedColor(pressedColor), _touchExtension(touchExtension) {

}

// ButtonProperties* ButtonProperties::setColor(uint16_t color) {
//     _color = color;
//     return this;
// }

ButtonProperties* ButtonProperties::setPressedColor(uint16_t pressedColor) {
    _pressedColor = pressedColor;
    return this;
}

ButtonProperties* ButtonProperties::setTouchExtension(Spacing touchExtension) {
    _touchExtension = touchExtension;
    return this;
}

// uint16_t ButtonProperties::getColor() {
//     return _color;
// }

uint16_t ButtonProperties::getPressedColor() {
    return _pressedColor;
}

Spacing ButtonProperties::getTouchExtension() {
    return _touchExtension;
}