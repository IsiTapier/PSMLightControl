/*
  ContainerProperties.h - ContainerProperties-Library for Airduino.
*/

#ifndef ContainerProperties_h
#define ContainerProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"

class ContainerProperties {
  public:
    ContainerProperties(Size length, Size height, Spacing padding = 0, Spacing margin = 0, Size borderThickness = 0, Size borderRoundness = 0, uint32_t borderColor = TFT_WHITE, uint32_t backgroundColor = TFT_DARKGREY);
    ContainerProperties(Size length, float format, Spacing padding = 0, Spacing margin = 0, Size borderThickness = 0, Size borderRoundness = 0, uint32_t borderColor = TFT_WHITE, uint32_t backgroundColor = TFT_DARKGREY);
    ContainerProperties(bool, Size height, float format, Spacing padding = 0, Spacing margin = 0, Size borderThickness = 0, Size borderRoundness = 0, uint32_t borderColor = TFT_WHITE, uint32_t backgroundColor = TFT_DARKGREY);
    ContainerProperties* setLength(Size length);
    ContainerProperties* setHeight(Size height);
    ContainerProperties* setFormat(float format);
    ContainerProperties* setPadding(Spacing padding);
    ContainerProperties* setMargin(Spacing margin);
    ContainerProperties* setBorderThickness(Size borderThickness);
    ContainerProperties* setBorderRoundness(Size borderRoundness);
    ContainerProperties* setBorderColor(uint32_t borderColor);
    ContainerProperties* setBackgroundColor(uint32_t backgroundColor);
    ContainerProperties* setDraw(bool draw);
    ContainerProperties* setX(short x);
    ContainerProperties* setY(short y);
    ContainerProperties* setXY(short x, short y);
    short getContentLength(bool includeMargin = false);
    short getContentHeight(bool includeMargin = false);
    Size getLength();
    Size getHeight();
    float getFormat();
    Spacing getPadding();
    Spacing getMargin();
    Size getBorderThickness();
    Size getBorderRoundness();
    uint32_t getBorderColor();
    uint32_t getBackgroundColor();
    bool getDraw();
    short getX();
    short getY();

  private:
    Size _length;
    Size _height;
    float _format;
    Spacing _padding;
    Spacing _margin;
    Size _borderThickness;
    Size _borderRoundness;
    uint32_t _borderColor;
    uint32_t _backgroundColor;
    bool _draw = 1;
    short _x = -1;
    short _y = -1;

};

#endif
