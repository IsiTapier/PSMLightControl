/*
  TextProperties.h - TextProperties-Library for Airduino.
*/

#ifndef TextProperties_h
#define TextProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"
#include "../../container/Container.h"

#define MAX_TEXT_SIZE 20

#define VALID_DATUM(datum) (datum >= TL_DATUM && datum <= BR_DATUM)

class TextProperties {
  public:
    TextProperties(uint16_t color = NO_COLOR, Size size = Size(), uint8_t datum = CC_DATUM);
    TextProperties* setSize(Size size);
    TextProperties* setDatum(uint8_t datum);
    TextProperties* setColor(uint16_t color);
    TextProperties* setX(short x);
    TextProperties* setY(short y);
    TextProperties* setXY(short x, short y);
    Size getSize();
    uint8_t getDatum();
    uint16_t getColor();
    short getX();
    short getY();

  private:
    Size _size;
    uint8_t _datum;
    uint16_t _color;
    short _x = -1;
    short _y = -1;

};

#endif
