/*
  ContainerProperties.h - ContainerProperties-Library for Airduino.
*/

#ifndef ContainerProperties_h
#define ContainerProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"

#define NO_COLOR 0x1

class ContainerProperties {
  public:
    ContainerProperties(Size length = Size(1., -1), Size height = Size(1., -1), Spacing margin = 0, Spacing padding = 0, Spacing borderThickness = 0, Size borderRoundness = 0, bool invisible = false, uint16_t borderColor = NO_COLOR, uint16_t backgroundColor = NO_COLOR);
    ContainerProperties(Size length, float format, Spacing margin = 0, Spacing padding = 0, Spacing borderThickness = 0, Size borderRoundness = 0, bool invisible = false, uint16_t borderColor = NO_COLOR, uint16_t backgroundColor = NO_COLOR);
    ContainerProperties(bool, Size height, float format, Spacing margin = 0, Spacing padding = 0, Spacing borderThickness = 0, Size borderRoundness = 0, bool invisible = false, uint16_t borderColor = NO_COLOR, uint16_t backgroundColor = NO_COLOR);
    ContainerProperties* setLength(Size length);
    ContainerProperties* setHeight(Size height);
    ContainerProperties* setFormat(float format);
    ContainerProperties* setPadding(Spacing padding);
    ContainerProperties* setMargin(Spacing margin);
    ContainerProperties* setBorderThickness(Spacing borderThickness);
    ContainerProperties* setBorderRoundness(Size borderRoundness);
    ContainerProperties* setBorderColor(uint16_t borderColor);
    ContainerProperties* setBackgroundColor(uint16_t backgroundColor);
    ContainerProperties* setDraw(bool draw);
    ContainerProperties* setX(short x);
    ContainerProperties* setY(short y);
    ContainerProperties* setXY(short x, short y);
    ContainerProperties* setInvisible(bool invisible);
    ContainerProperties* setOrder(byte order);
    ContainerProperties* setViewId(uint8_t viewId);
    ContainerProperties* setId(uint8_t id);
    short getContentLength(bool includePadding = false);
    short getContentHeight(bool includePadding = false);
    short getContentX(bool includePadding = false);
    short getContentY(bool includePadding = false);
    Size getLength();
    Size getHeight();
    float getFormat();
    Spacing getPadding();
    Spacing getMargin();
    Spacing getBorderThickness();
    Size getBorderRoundness();
    uint16_t getBorderColor();
    uint16_t getBackgroundColor();
    bool getDraw();
    short getX();
    short getY();
    bool getInvisible();
    uint8_t getOrder();
    uint8_t getViewId();
    int8_t getId();
    int8_t getNextId();
    int8_t getCurrentId();

  private:
    Size _length;
    Size _height;
    float _format;
    Spacing _padding;
    Spacing _margin;
    Spacing _borderThickness;
    Size _borderRoundness;
    uint16_t _borderColor;
    uint16_t _backgroundColor;
    bool _draw = 1;
    short _x = -1;
    short _y = -1;
    bool _invisible;
    uint8_t _order;
    uint8_t _viewId;
    uint8_t _id;
    int8_t _currentId = -1;

};

#endif
