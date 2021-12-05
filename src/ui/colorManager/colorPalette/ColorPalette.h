/*
  ColorPalette.h - ColorPalette-Library for Airduino.
*/

#ifndef ColorPalette_h
#define ColorPalette_h

#include "Arduino.h"

class ColorPalette {
  public:
    ColorPalette(uint16_t contrastColor, uint16_t backgroundColor, std::vector<uint16_t> containerColors);
    ColorPalette(uint16_t borderColor, uint16_t textColor, uint16_t backgroundColor, std::vector<uint16_t> containerColors);
    uint16_t getContrastColor();
    uint16_t getBorderColor();
    uint16_t getTextColor();
    uint16_t getBackgroundColor();
    uint16_t getContainerColor(uint8_t order);

  private:
    uint16_t  _contrastColor,
              _borderColor,
              _textColor,
              _backgroundColor;
    std::vector<uint16_t> _containerColors;
    bool commonContrastColor;

};

#endif