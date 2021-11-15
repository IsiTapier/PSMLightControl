/*
  Button.h - Button-Library for Airduino.
*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "../container/Container.h"
#include "ButtonProperties/ButtonProperties.h"
class Button;
#include "../buttonManager/ButtonManager.h"

class Button : public Container {
  public:
    Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<void()> touchEvent);

    void draw() override;
    byte checkTouch();
    void trigger();

  private:
    ButtonProperties _buttonProperties;
    std::function<void()> _touchEvent;
    bool triggered = false;

};

#endif
