/*
  ButtonProperties.h - ButtonProperties-Library for Airduino.
*/

#ifndef ButtonProperties_h
#define ButtonProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"
#include "../../viewManager/ViewManager.h"

#define DEFAULT_EXTENSION 100

class ButtonProperties {
  public:
    ButtonProperties(uint16_t viewId = View::getCurrentId(), uint32_t color = TFT_LIGHTGREY, uint32_t pressedColor = TFT_DARKGREY, Spacing touchExtension = Spacing(DEFAULT_EXTENSION));
    ButtonProperties* setColor(uint32_t color);
    ButtonProperties* setPressedColor(uint32_t color);
    ButtonProperties* setTouchExtension(Spacing touchExtension);
    uint16_t getView();
    uint32_t getColor();
    uint32_t getPressedColor();
    Spacing getTouchExtension();

  private:
    uint16_t _viewId;
    uint32_t _color;
    uint32_t _pressedColor;
    Spacing _touchExtension;
    

};

#endif
