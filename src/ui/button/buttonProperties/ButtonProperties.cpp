/*
 ButtonProperties.cpp - ButtonProperties-Library for Librarys.
*/

#include "ButtonProperties.h"

ButtonProperties::ButtonProperties(uint32_t color, uint32_t pressedColor) : _color(color), _pressedColor(pressedColor) {

}

ButtonProperties* ButtonProperties::setColor(uint32_t color) {
    _color = color;
    return this;
}

ButtonProperties* ButtonProperties::setPressedColor(uint32_t pressedColor) {
    _pressedColor = pressedColor;
    return this;
}

uint32_t ButtonProperties::getColor() {
    return _color;
}

uint32_t ButtonProperties::getPressedColor() {
    return _pressedColor;
}