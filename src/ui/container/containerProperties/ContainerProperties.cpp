/*
 ContainerProperties.cpp - ContainerProperties-Library for Librarys.
*/

#include "ContainerProperties.h"

ContainerProperties::ContainerProperties(Size length, Size height, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, bool invisible, uint16_t borderColor, uint16_t backgroundColor) : _length(length), _height(height), _format(height/length), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor), _invisible(invisible) {

}

ContainerProperties::ContainerProperties(Size length, float format, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, bool invisible, uint16_t borderColor, uint16_t backgroundColor) : _length(length), _height(format*length), _format(format), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor), _invisible(invisible) {

}

ContainerProperties::ContainerProperties(bool, Size height, float format, Spacing padding, Spacing margin, Size borderThickness, Size borderRoundness, bool invisible, uint16_t borderColor, uint16_t backgroundColor) : _length(height/format), _height(height), _format(format), _padding(padding), _margin(margin), _borderThickness(borderThickness), _borderRoundness(borderRoundness), _borderColor(borderColor), _backgroundColor(backgroundColor), _invisible(invisible) {

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

ContainerProperties* ContainerProperties::setBorderColor(uint16_t borderColor) {
    _borderColor = borderColor;
    return this;
}

ContainerProperties* ContainerProperties::setBackgroundColor(uint16_t backgroundColor) {
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

ContainerProperties* ContainerProperties::setInvisible(bool invisible) {
    _invisible = invisible;
    return this;
}

ContainerProperties* ContainerProperties::setOrder(uint8_t order) {
    _order = order;
    return this;
}

ContainerProperties* ContainerProperties::setViewId(uint8_t viewId) {
    _viewId = viewId;
    return this;
}

ContainerProperties* ContainerProperties::setId(uint8_t id) {
    _id = id;
    return this;
}

short ContainerProperties::getContentLength(bool includeMargin) {
    return _length-2*_borderThickness-(includeMargin?(_margin.get(LEFT)+_margin.get(RIGHT)):0);
}

short ContainerProperties::getContentHeight(bool includeMargin) {
    return _height-2*_borderThickness-(includeMargin?(_margin.get(TOP)+_margin.get(BOTTOM)):0);
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

uint16_t ContainerProperties::getBorderColor() {
    return _borderColor;
}

uint16_t ContainerProperties::getBackgroundColor() {
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

bool ContainerProperties::getInvisible() {
    return _invisible;
}

byte ContainerProperties::getOrder() {
    return _order;
}

uint8_t ContainerProperties::getViewId() {
    return _viewId;
}

uint8_t ContainerProperties::getId() {
    return _id;
}

uint8_t ContainerProperties::getNextId() {
    _currentId++;
    return _currentId;
}

uint8_t ContainerProperties::getCurrentId() {
    return _currentId;
}