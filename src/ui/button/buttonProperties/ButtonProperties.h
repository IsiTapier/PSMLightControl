/*
  ButtonProperties.h - ButtonProperties-Library for Airduino.
*/

#ifndef ButtonProperties_h
#define ButtonProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "../../spacing/Spacing.h"
// #include "../../viewManager/ViewManager.h"
#include "../../container/Container.h"

#define DEFAULT_EXTENSION 10

class ButtonProperties {
  public:
    ButtonProperties(uint16_t pressedColor = NO_COLOR, Spacing touchExtension = Spacing(DEFAULT_EXTENSION));
    ButtonProperties* setColor(uint16_t color);
    ButtonProperties* setPressedColor(uint16_t color);
    ButtonProperties* setTouchExtension(Spacing touchExtension);
    uint16_t getColor();
    uint16_t getPressedColor();
    Spacing getTouchExtension();

  private:
    uint16_t _color = NO_COLOR;
    uint16_t _pressedColor;
    Spacing _touchExtension;
    

};

#endif
