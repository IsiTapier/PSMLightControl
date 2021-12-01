/*
 ButtonProperties.cpp - ButtonProperties-Library for Librarys.
*/

#include "ButtonProperties.h"

ButtonProperties::ButtonProperties(uint16_t viewId, uint32_t color, uint32_t pressedColor, Spacing touchExtension) : _viewId(viewId), _color(color), _pressedColor(pressedColor), _touchExtension(touchExtension) {

}

ButtonProperties* ButtonProperties::setColor(uint32_t color) {
    _color = color;
    return this;
}

ButtonProperties* ButtonProperties::setPressedColor(uint32_t pressedColor) {
    _pressedColor = pressedColor;
    return this;
}

ButtonProperties* ButtonProperties::setTouchExtension(Spacing touchExtension) {
    _touchExtension = touchExtension;
    return this;
}

uint16_t ButtonProperties::getView() {
    return _viewId;
}

uint32_t ButtonProperties::getColor() {
    return _color;
}

uint32_t ButtonProperties::getPressedColor() {
    return _pressedColor;
}

Spacing ButtonProperties::getTouchExtension() {
    return _touchExtension;
}