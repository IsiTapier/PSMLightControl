/*
 Joystick.cpp - Joystick-Library for Librarys.
*/

#include "Joystick.h"

Joystick::Joystick() {}

Joystick::Joystick(uint8_t xPin, uint8_t yPin, uint8_t buttonPin, JOYSTICK_CALLBACK_SIGNATURE, BUTTON_CALLBACK_SIGNATURE) : _xPin(xPin), _yPin(yPin), _buttonPin(buttonPin), joystickCallback(joystickCallback), buttonCallback(buttonCallback) {
    pinMode(buttonPin, INPUT_PULLUP);
    xTaskCreatePinnedToCore(startLoopTask, "joystick_loop_task", 1024, this, 7, NULL, 0);
}

void Joystick::joystick_loop_task() {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    for(byte i = 0; i < 10; i++) {
        centerX+=analogRead(_xPin);
        centerY+=analogRead(_yPin);
    }
    centerX/=10;
    centerY/=10;
    for(;;) {
        vTaskDelay(JOYSTICK_LOOP_SPEED/portTICK_PERIOD_MS);
        //Joystick
        xValRaw = analogRead(_xPin);
        yValRaw = analogRead(_yPin);
        xVal = abs(xValRaw-centerX);
        yVal = abs(yValRaw-centerY);
        xPercent = xVal/(double)((xValRaw<centerX)?centerX:-(4095-centerX));
        yPercent = yVal/(double)((yValRaw<centerY)?centerY:-(4095-centerY));
        if(xVal > JOYSTICK_MOVE_TOLLERANCE || yVal > JOYSTICK_MOVE_TOLLERANCE)
            joystickCallback(xPercent, yPercent);
        //button
        lastButtonState = buttonState;
        buttonState = !digitalRead(_buttonPin) && yValRaw != 4095;
        if(buttonState && !lastButtonState)
            buttonCallback();
        if(JOSTCICK_DEBUG) {
            Serial.print(F("x: ")); Serial.print(xValRaw);
            Serial.print(F(" xc: ")); Serial.print(centerX);
            Serial.print(F(" y: ")); Serial.print(yValRaw);
            Serial.print(F(" yc: ")); Serial.print(centerY);
            Serial.print(F(" button: ")); Serial.print(buttonState);
            Serial.print(F(" button: ")); Serial.print(lastButtonState);
            Serial.println();
        }
    }
}

void Joystick::startLoopTask(void* _this) {
    ((Joystick*)_this)->joystick_loop_task();
}