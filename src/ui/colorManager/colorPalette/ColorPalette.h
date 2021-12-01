/*
  ColorPalette.h - ColorPalette-Library for Airduino.
*/

#ifndef ColorPalette_h
#define ColorPalette_h

#include "Arduino.h"

class ColorPalette {
  public:
    ColorPalette(uint32_t contrastColor, uint32_t backgroundColor, std::vector<uint32_t> containerColors);
    ColorPalette(uint32_t borderColor, uint32_t textColor, uint32_t backgroundColor, std::vector<uint32_t> containerColors);
    uint32_t getContrastColor();
    uint32_t getBorderColor();
    uint32_t getTextColor();
    uint32_t getBackgroundColor();
    uint32_t getContainerColor(uint8_t order);

  private:
    uint32_t  _contrastColor,
              _borderColor,
              _textColor,
              _backgroundColor;
    std::vector<uint32_t> _containerColors;
    bool commonContrastColor;

};

#endif