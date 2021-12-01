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
    Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<void()> touchEvent, std::vector<Container*> content);

    void init(short x, short y) override;
    void draw() override;

    ButtonProperties getProperties();

    byte checkTouch(TSPoint p);
    void trigger();
    void untrigger();

  private:
    ButtonProperties _buttonProperties;
    std::function<void()> _touchEvent;
    bool triggered = false;

};

#endif
