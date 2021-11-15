/*
  Size.h - Size-Library for Airduino.
*/

#ifndef Size_h
#define Size_h

#include "Arduino.h"

#define ABSOLUTE 1
#define RELATIVE 0
#define VALID_ABSOLUTE (_length != -1)
#define VALID_RELATIVE (_reference != -1 && _proportion != -1)
#define VALID_SIZE(mode) (mode==ABSOLUTE?VALID_ABSOLUTE:VALID_RELATIVE)

class Size {
  public:
    Size();
    Size(short length);
    Size(float proportion, short reference);
    Size(short length, float proportion, short reference, bool mode = ABSOLUTE);
    Size* setLength(short length);
    Size* setReference(short reference, bool changeMode = true);
    Size* setProportion(float proportion);
    short getSize(bool mode);
    short getSize();
    short getAbsoluteSize();
    short getRelativeSize();
    short getReference();
    float getProportion();
    bool operator==(int v);
    bool operator!=(int v);
    operator int();

  private:
    short _length, _reference;
    float _proportion;
    bool _mode;

    bool checkCalculateMode(bool defaultMode = ABSOLUTE);

};

#endif
