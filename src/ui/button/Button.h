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

#define COLOR_SHIFT 40

class Button : public Container {
  public:
    Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<uint16_t()> touchEvent, std::vector<Container*> content);

    void init() override;
    void draw() override;

    void setId(short id);
    short getId();

    ButtonProperties getProperties();

    byte checkTouch(TSPoint p);
    uint16_t trigger();
    void untrigger();

  private:
    ButtonProperties _buttonProperties;
    std::function<uint16_t()> _touchEvent;
    bool triggered = false;
    short _id = -1;

};

#endif
