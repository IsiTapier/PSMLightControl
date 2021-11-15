/*
  ButtonManager.h - ButtonManager-Library for Airduino.
*/

#ifndef ButtonManager_h
#define ButtonManager_h

#include "Arduino.h"
#include "../button/Button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

class ButtonManager {
  public:
    static void init();
    static void addButton(Button button);
    
  private:
    static std::vector<Button> buttons;

    static void checkTouch(void*);

};

#endif
