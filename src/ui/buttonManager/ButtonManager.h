/*
  ButtonManager.h - ButtonManager-Library for Airduino.
*/

#ifndef ButtonManager_h
#define ButtonManager_h

#include "Arduino.h"
#include "FS.h"
#include "../button/Button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define CALIBRATION_FILE "/TouchCalData2"
#define REPEAT_CAL false
#define TOUCH_CYCLE 10

class ButtonManager {
  public:
    static void init();
    static void addButton(Button* button);
    static void calibrateTouch();
    
  private:
    static std::vector<Button*> buttons;

    static void checkTouch(void*);

};

#endif
