/*
 Spacing.cpp - Spacing-Library for Librarys.
*/

#include "Spacing.h"

Spacing::Spacing(int spacingAll) : _spacingAll(Size(spacingAll)), _spacingEqual(EQUAL) {

}

Spacing::Spacing(Size spacingAll) : _spacingAll(spacingAll), _spacingEqual(EQUAL) {

}

Spacing::Spacing(Size spacingLeft, Size spacingRight, Size spacingTop, Size spacingBottom) : _spacingLeft(spacingLeft), _spacingRight(spacingRight), _spacingTop(spacingTop), _spacingBottom(spacingBottom), _spacingEqual(SEPERATE) {

}

Spacing::Spacing(Size spacingAll, Size spacingLeft, Size spacingRight, Size spacingTop, Size spacingBottom, bool spacingEqual) : _spacingAll(spacingAll), _spacingLeft(spacingLeft), _spacingRight(spacingRight), _spacingTop(spacingTop), _spacingBottom(spacingBottom), _spacingEqual(spacingEqual) {

}

Spacing* Spacing::set(Orientation orientation, Size size) {
    if(getEqual())
        setAll(size);
    else
        switch(orientation) {
            case LEFT: setLeft(size); break;
            case RIGHT: setRight(size); break;
            case TOP: setTop(size); break;
            case BOTTOM: setBottom(size); break;
        }
    return this;
}

Spacing* Spacing::setAll(Size size) {
    _spacingAll = size;
    return this;
}

Spacing* Spacing::setLeft(Size size) {
    _spacingLeft = size;
    return this;
}

Spacing* Spacing::setRight(Size size) {
    _spacingRight = size;
    return this;
}

Spacing* Spacing::setTop(Size size) {
    _spacingTop = size;
    return this;
}

Spacing* Spacing::setBottom(Size size) {
    _spacingBottom = size;
    return this;
}

Spacing* Spacing::setReference(short length, short height, bool changeMode) {
    _spacingAll.setReference(length, changeMode);
    _spacingLeft.setReference(length, changeMode);
    _spacingRight.setReference(length, changeMode);
    _spacingTop.setReference(height, changeMode);
    _spacingBottom.setReference(height, changeMode);
    return this;
}

bool Spacing::setEqual(bool spacingEqual) {
    if(VALID_SPACING(spacingEqual)) {
        _spacingEqual = spacingEqual;
        return true;
    }
    return false;
}

Size Spacing::get(Orientation orientation) {
    if(getEqual())
        return getAll();
    switch(orientation) {
        case LEFT: return getLeft(); break;
        case RIGHT: return getRight(); break;
        case TOP: return getTop(); break;
        case BOTTOM: return getBottom(); break;
    }
}

Size Spacing::getAll() {
    return _spacingAll;
}

Size Spacing::getLeft() {
    return _spacingLeft;
}

Size Spacing::getRight() {
    return _spacingRight;
}

Size Spacing::getTop() {
    return _spacingTop;
}

Size Spacing::getBottom() {
    return _spacingBottom;
}

bool Spacing::getEqual() {
    return _spacingEqual;
}

#undef EQUAL
#undef SEPERATE
#undef VALID_EQUAL
#undef VALID_SEPERATE
#undef VALID_SPACING