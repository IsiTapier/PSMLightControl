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

#define COLOR_SHIFT 20

class Button : public Container {
  public:
    Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<void()> touchEvent, std::vector<Container*> content);

    void init() override;
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
