/*
 Size.cpp - Size-Library for Librarys.
*/

#include "Size.h"

    Size::Size() : _length(-1), _reference(-1), _proportion(-1), _mode(ABSOLUTE) {}

    Size::Size(short length) : _length(length), _reference(-1), _proportion(-1), _mode(ABSOLUTE) {
        
    }

    Size::Size(float proportion, short reference) : _length(-1), _reference(reference), _proportion(proportion), _mode(RELATIVE) {

    }

    Size::Size(short length, float proportion, short reference, bool mode) : _length(length), _reference(reference), _proportion(proportion), _mode(mode) {

    }

    Size* Size::setLength(short length) {
        _length = length;
        checkCalculateMode(ABSOLUTE);
        return this;
    }

    Size* Size::setReference(short reference, bool changeMode) {
        _reference = reference;
        if(changeMode)
            checkCalculateMode(RELATIVE);
        return this;
    }

    Size* Size::setProportion(float proportion) {
        _proportion = proportion;
        checkCalculateMode(RELATIVE);
        return this;
    }

    short Size::getSize(bool mode) {
        return VALID_SIZE(mode)?mode==ABSOLUTE?_length:_reference*_proportion:-1;
    }

    short Size::getSize() {
        // checkCalculateMode();
        return getSize(_mode);
    }

    short Size::getAbsoluteSize() {
        return getSize(ABSOLUTE);
    }

    short Size::getRelativeSize() {
        return getSize(RELATIVE);
    }

    short Size::getReference() {
        return _reference;
    }

    float Size::getProportion() {
        return _proportion;
    }

    bool Size::checkCalculateMode(bool defaultMode) {
        if(!VALID_SIZE(_mode))
            if(!VALID_SIZE(!_mode))
                _mode = defaultMode;
            else
                _mode = !_mode;
        return _mode;
    }

    bool Size::operator==(int v) {
        if(v == -1)
            return !VALID_ABSOLUTE && !VALID_RELATIVE;
        else
            return v == getSize();
    }

    bool Size::operator!=(int v) {
        if(v == -1)
            return VALID_ABSOLUTE || VALID_RELATIVE;
        else
            return v != getSize();
    }

    Size::operator int() {
        return getSize();
    }

#undef ABSOLUTE
#undef RELATIVE
#undef VALID_SIZE
#undef VALID_ABSOLUTE
#undef VALID_RELATIVE