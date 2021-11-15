/*
  ButtonProperties.h - ButtonProperties-Library for Airduino.
*/

#ifndef ButtonProperties_h
#define ButtonProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"

class ButtonProperties {
  public:
    ButtonProperties(uint32_t color = TFT_LIGHTGREY, uint32_t pressedColor = TFT_DARKGREY);
    ButtonProperties* setColor(uint32_t color);
    ButtonProperties* setPressedColor(uint32_t color);
    uint32_t getColor();
    uint32_t getPressedColor();

  private:
    uint32_t _color;
    uint32_t _pressedColor;
    

};

#endif
