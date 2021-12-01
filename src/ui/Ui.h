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

#define ROTATION 3
#define BACKGROUND_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE

class Ui {
  public:
    Ui();

    static void init();

  private:

};

#endif
  