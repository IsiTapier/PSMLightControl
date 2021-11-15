/*
  TextProperties.h - TextProperties-Library for Airduino.
*/

#ifndef TextProperties_h
#define TextProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"

#define MAX_TEXT_SIZE 20

#define VALID_DATUM(datum) (datum >= TL_DATUM && datum <= BR_DATUM)

class TextProperties {
  public:
    TextProperties(uint32_t color = TFT_WHITE, uint32_t backgroundColor = TFT_DARKGREY, Size size = Size(), uint8_t datum = TL_DATUM);
    TextProperties* setSize(Size size);
    TextProperties* setDatum(uint8_t datum);
    TextProperties* setColor(uint32_t color);
    TextProperties* setBackgroundColor(uint32_t color);
    TextProperties* setX(short x);
    TextProperties* setY(short y);
    TextProperties* setXY(short x, short y);
    Size getSize();
    uint8_t getDatum();
    uint32_t getColor();
    uint32_t getBackgroundColor();
    short getX();
    short getY();

  private:
    Size _size;
    uint8_t _datum;
    uint32_t _color;
    uint32_t _backgroundColor;
    short _x = -1;
    short _y = -1;

};

#endif
