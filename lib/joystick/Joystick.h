/*
  Joystick.h - Joystick-Library for Airduino.
*/

#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"
#include <functional>
#include "Util.h"

#define JOSTCICK_DEBUG              0
#define JOYSTICK_LOOP_SPEED         100
#define JOYSTICK_MOVE_TOLLERANCE    70

#define JOYSTICK_CALLBACK_SIGNATURE std::function<void(float, float)> joystickCallback
#define BUTTON_CALLBACK_SIGNATURE std::function<void()> buttonCallback

class Joystick {
    public:
        Joystick();
        Joystick(uint8_t xPin, uint8_t yPin, uint8_t buttonPin, JOYSTICK_CALLBACK_SIGNATURE, BUTTON_CALLBACK_SIGNATURE);

    private:
        uint8_t _xPin, _yPin, _buttonPin;
        JOYSTICK_CALLBACK_SIGNATURE;
        BUTTON_CALLBACK_SIGNATURE;
        bool buttonState = 0, lastButtonState = 0;
        uint16_t centerX = 0, centerY = 0, xValRaw, yValRaw, xVal, yVal;
        float xPercent, yPercent;

        void joystick_loop_task();
        static void startLoopTask(void* _this);

};

#endif