/*
  Container.h - Container-Library for Airduino.
*/

#ifndef Container_h
#define Container_h

#include "Arduino.h"
#include "containerProperties/ContainerProperties.h"
#include "Util.h"
#include "../../Settings.h"   
#include "../colorManager/ColorManager.h"

#define CONTAINER_SET_REFERENCES(_properties) \
        properties.setLength(*properties.getLength().setReference(_properties.getContentLength(), false));\
        properties.setHeight(*properties.getHeight().setReference(_properties.getContentHeight(), false));\
        properties.setPadding(*properties.getPadding().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setMargin(*properties.getMargin().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setBorderThickness(*properties.getBorderThickness().setReference(properties.getLength(), false));\
        properties.setBorderRoundness(*properties.getBorderRoundness().setReference(properties.getBorderThickness(), false));\

#define NO_VIEW UINT8_MAX

class Container {
  public:
    Container(ContainerProperties properties, std::vector<Container*> content);

    virtual void init();
    virtual void draw();
    void drawBorder();

    ContainerProperties getPorperties();
    void setProperties(ContainerProperties properties);

    void setBackground(uint16_t color);
    uint16_t getColor();

    void addContent(Container* content);
    uint8_t getContentAmount();

  private:
    ContainerProperties _properties;
    std::vector<Container*> _content;
    uint8_t _viewId;

};

#endif
