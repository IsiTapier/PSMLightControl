/*
  View.h - View-Library for Airduino.
*/

#ifndef View_h
#define View_h

#include "Arduino.h"
#include "../container/Container.h"
#include "viewProperties/ViewProperties.h"

class View : Container {
  public:
    View(ContainerProperties properties, ViewProperties viewProperties, std::vector<Container*> content);
    
    byte getId();
    void init(short x = 0, short y = 0) override;
    void draw() override;

    static byte getCurrentId();

  private:
    ViewProperties _viewProperties;
    byte id;
    
    static byte currentId;

};

#endif