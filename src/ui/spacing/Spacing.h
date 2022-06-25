/*
  Spacing.h - Spacing-Library for Airduino.
*/

#ifndef Spacing_h
#define Spacing_h

#include "Arduino.h"
#include "../size/Size.h"
#include "Util.h"

#define EQUAL 1
#define SEPERATE 0
#define VALID_EQUAL (_spacingAll != -1)
#define VALID_SEPERATE (_spacingLeft != -1 && _spacingRight != -1 && _spacingTop != -1 && _spacingBottom != -1)
#define VALID_SPACING(mode) (mode==EQUAL?VALID_EQUAL:VALID_SEPERATE)

enum Orientation { LEFT, RIGHT, TOP, BOTTOM };

class Spacing {
  public:
    Spacing(int spacingAll);
    Spacing(Size spacingAll);
    Spacing(Size spacingX, Size spacingY);
    Spacing(Size spacingLeft, Size spacingRight, Size spacingTop, Size spacingBottom);
    Spacing(Size spacingAll, Size spacingLeft, Size spacingRight, Size spacingTop, Size spacingBottom, bool spacingEqual = EQUAL);
    ~Spacing();
    Spacing* set(Orientation orientation, Size size);
    Spacing* setAll(Size size);
    Spacing* setLeft(Size size);
    Spacing* setRight(Size size);
    Spacing* setTop(Size size);
    Spacing* setBottom(Size size);
    Spacing* setReference(short length, short height, bool changeMode = false);
    bool setEqual(bool Equal);
    Size get(Orientation orientation);

    Size getAll();
    Size getLeft();
    Size getRight();
    Size getTop();
    Size getBottom();
    bool getEqual();
    short getMin();
    short getMax();
    operator int();

  private:
    Size _spacingAll;
    Size _spacingLeft;
    Size _spacingRight;
    Size _spacingTop;
    Size _spacingBottom;
    bool _spacingEqual;
};

#endif
