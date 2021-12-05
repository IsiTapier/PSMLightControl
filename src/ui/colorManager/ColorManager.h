/*
  ColorManager.h - ColorManager-Library for Airduino.
*/

#ifndef ColorManager_h
#define ColorManager_h

#include "Arduino.h"
#include "colorPalette/ColorPalette.h"
#include "TFT_eSPI.h"

namespace colorModes {
  const byte darkMode = 0;
  const byte lightMode = 1;
}

class ColorManager {
  public:
    static void addColorPalette(ColorPalette colorPalette);
    static void setColorPalette(ColorPalette colorPalette);
    static void setColorPalette(byte colorPalette);
    static ColorPalette getColorPalette(byte colorPalette);
    static ColorPalette getColorPalette();
    static byte getCurrentColorPalette();
    static uint16_t getContrastColor();
    static uint16_t getBorderColor();
    static uint16_t getTextColor();
    static uint16_t getBackgroundColor();
    static uint16_t getContainerColor(uint8_t order);
    
  private:
    static std::vector<ColorPalette> colorPalettes;
    static byte currentColorPalette;

};

#endif