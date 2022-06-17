/*
 TextProperties.cpp - TextProperties-Library for Librarys.
*/

#include "TextProperties.h"

TextProperties::TextProperties(uint16_t color, Size size, uint8_t datum) : _size(size), _datum(VALID_DATUM(datum)?datum:TL_DATUM), _color(color) {

}

TextProperties* TextProperties::setSize(Size size) {
    if(size > MAX_TEXT_SIZE)
        size = MAX_TEXT_SIZE;
    _size = size;
    return this;
}

TextProperties* TextProperties::setDatum(uint8_t datum) {
    if(VALID_DATUM(datum))
        _datum = datum;
    return this;
}

TextProperties* TextProperties::setColor(uint16_t color) {
    _color = color;
    return this;
}

TextProperties* TextProperties::setX(short x) {
    _x = x;
    return this;
}

TextProperties* TextProperties::setY(short y) {
    _y = y;
    return this;
}

TextProperties* TextProperties::setXY(short x, short y) {
    _x = x;
    _y = y;
    return this;
}

Size TextProperties::getSize() {
    return _size;
}

uint8_t TextProperties::getDatum() {
    return _datum;
}

uint16_t TextProperties::getColor() {
    return _color;
}

short TextProperties::getX() {
    return _x;
}

short TextProperties::getY() {
    return _y;
}