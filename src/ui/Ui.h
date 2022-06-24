/*
  Ui.h - Ui-Library for Airduino.
*/

#ifndef Ui_h
#define Ui_h

#include "Arduino.h"
#include "button/Button.h"
#include "container/Container.h"
#include "textField/Text.h"
#include "viewManager/ViewManager.h"
#include "containerGrid/ContainerGrid.h"
#include "customView/CustomView.h"
#include "MovingHead.h"
#include "EEPROM.h"

#define ROTATION 3
#define BACKGROUND_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE

class Ui {
  public:

    static void init();

  private:
    // static CustomView buehne;

};

#endif
  