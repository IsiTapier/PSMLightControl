/*
  Container.h - Container-Library for Airduino.
*/

#ifndef Container_h
#define Container_h

#include "Arduino.h"
#include "containerProperties/ContainerProperties.h"
#include "Util.h"
#include "../../Settings.h"   

#define CONTAINER_SET_REFERENCES(_properties) \
        properties.setLength(*properties.getLength().setReference(_properties.getContentLength(), false));\
        properties.setHeight(*properties.getHeight().setReference(_properties.getContentHeight(), false));\
        properties.setPadding(*properties.getPadding().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setMargin(*properties.getMargin().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setBorderThickness(*properties.getBorderThickness().setReference(properties.getLength(), false));\
        properties.setBorderRoundness(*properties.getBorderRoundness().setReference(properties.getBorderThickness(), false));\

class Container {
  public:
    Container(ContainerProperties properties, std::vector<Container*> content);

    virtual void init(short x, short y);
    virtual void draw();
    void drawBorder();

    ContainerProperties getPorperties();
    void setProperties(ContainerProperties properties);
    void setBackground(uint32_t color);

  private:
    ContainerProperties _properties;
    std::vector<Container*> _content;

};

#endif
