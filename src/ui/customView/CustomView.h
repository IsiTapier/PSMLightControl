/*
  CustomView.h - CustomView-Library for Airduino.
*/

#ifndef CustomView_h
#define CustomView_h

#include "Arduino.h"
#include "../view/View.h"

class CustomView : public View {
  public:
    //temporary
    CustomView();
    CustomView(ContainerProperties properties, ViewProperties viewProperties, std::function<void()> init, std::function<void()> draw, std::function<uint16_t(TSPoint)> checkTouch = [](TSPoint){return 0;}, std::vector<Container*> normalContent = {}, std::vector<Container*> navBarContent = {});    
    void init() override;
    void draw(short startX=-1, short startY=-1, short endY=-1, short endX=-1, bool fill=true) override;
    uint16_t checkTouch(TSPoint p) override;

  private:
    std::function<void()> _init;
    std::function<void()> _draw;
    std::function<uint16_t(TSPoint)> _checkTouch;

};

#endif
