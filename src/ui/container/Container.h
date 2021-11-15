/*
  Container.h - Container-Library for Airduino.
*/

#ifndef Container_h
#define Container_h

#include "Arduino.h"
#include "containerProperties/ContainerProperties.h"
#include "Util.h"
#include "../../Settings.h"                                                                                                                                                              

class Container {
  public:
    Container(ContainerProperties properties, std::vector<Container*> content);

    virtual void init(short x, short y);
    virtual void draw();
    void drawBorder();

    ContainerProperties getPorperties();
    void setProperties(ContainerProperties properties);

  private:
    ContainerProperties _properties;
    std::vector<Container*> _content;

};

#endif
