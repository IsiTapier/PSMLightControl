/*
  CustomView.h - CustomView-Library for Airduino.
*/

#ifndef CustomView_h
#define CustomView_h

#include "Arduino.h"
#include "../view/View.h"

class CustomView : public View {
  public:
    CustomView(ContainerProperties properties, ViewProperties viewProperties, std::function<void()> init, std::function<void()> draw, std::function<void(TSPoint)> checkTouch = [](TSPoint){});    
    void init() override;
    void draw() override;
    void checkTouch(TSPoint p) override;

  private:
    std::function<void()> _init;
    std::function<void()> _draw;
    std::function<void(TSPoint)> _checkTouch;

};

#endif
