/*
 ContainerProperties.cpp - ContainerProperties-Library for Librarys.
*/

#include "ContainerProperties.h"

ContainerProperties::ContainerProperties(Size length, Size height, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, uint32_t borderColor, uint32_t backgroundColor) : _length(length), _height(height), _format(height/length), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor) {

}

ContainerProperties::ContainerProperties(Size length, float format, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, uint32_t borderColor, uint32_t backgroundColor) : _length(length), _height(format*length), _format(format), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor) {

}

ContainerProperties::ContainerProperties(bool, Size height, float format, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, uint32_t borderColor, uint32_t backgroundColor) : _length(height/format), _height(height), _format(format), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor) {

}

ContainerProperties* ContainerProperties::setLength(Size length) {
    _length = length;
    _format = _height/_length;
    return this;
}

ContainerProperties* ContainerProperties::setHeight(Size height) {
    _height = height;
    _format = _height/_length;
    return this;
}

ContainerProperties* ContainerProperties::setFormat(float format) {
    _format = format;
    _height = _format*_length;
    return this;
}

ContainerProperties* ContainerProperties::setPadding(Spacing padding) {
    _padding = padding;
    return this;
}

ContainerProperties* ContainerProperties::setMargin(Spacing margin) {
    _margin = margin;
    return this;
}

ContainerProperties* ContainerProperties::setBorderThickness(Size borderThickness) {
    _borderThickness = borderThickness;
    return this;
}

ContainerProperties* ContainerProperties::setBorderRoundness(Size borderRoundness) {
    _borderRoundness = borderRoundness;
    return this;
}

ContainerProperties* ContainerProperties::setBorderColor(uint32_t borderColor) {
    _borderColor = borderColor;
    return this;
}

ContainerProperties* ContainerProperties::setBackgroundColor(uint32_t backgroundColor) {
    _backgroundColor = backgroundColor;
    return this;
}

ContainerProperties* ContainerProperties::setDraw(bool draw) {
    _draw = draw;
    return this;
}

ContainerProperties* ContainerProperties::setX(short x) {
    _x = x;
    return this;
}

ContainerProperties* ContainerProperties::setY(short y) {
    _y = y;
    return this;
}

ContainerProperties* ContainerProperties::setXY(short x, short y) {
    _x = x;
    _y = y;
    return this;
}

short ContainerProperties::getContentLength(bool includeMargin) {
    return _length-2*_borderThickness-(includeMargin?_margin.getLeft()-_margin.getRight():0);
}

short ContainerProperties::getContentHeight(bool includeMargin) {
    return _height-2*_borderThickness-(includeMargin?_margin.getTop()-_margin.getBottom():0);
}

Size ContainerProperties::getLength() {
    return _length;
}

Size ContainerProperties::getHeight() {
    return _height;
}

float ContainerProperties::getFormat() {
    return _format;
}

Spacing ContainerProperties::getPadding() {
    return _padding;
}

Spacing ContainerProperties::getMargin() {
    return _margin;
}

Size ContainerProperties::getBorderThickness() {
    return _borderThickness;
}

Size ContainerProperties::getBorderRoundness() {
    return _borderRoundness;
}

uint32_t ContainerProperties::getBorderColor() {
    return _borderColor;
}

uint32_t ContainerProperties::getBackgroundColor() {
    return _backgroundColor;
}

bool ContainerProperties::getDraw() {
    return _draw&&getX()!=-1&&getY()!=-1;
}

short ContainerProperties::getX() {
    return _x;
}

short ContainerProperties::getY() {
    return _y;
}