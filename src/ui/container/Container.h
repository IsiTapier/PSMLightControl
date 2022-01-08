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
        properties.setLength(*properties.getLength().setReference(_properties.getContentLength(true), false));\
        properties.setHeight(*properties.getHeight().setReference(_properties.getContentHeight(true), false));\
        properties.setPadding(*properties.getPadding().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setMargin(*properties.getMargin().setReference(properties.getLength(), properties.getHeight(), false));\
        properties.setBorderThickness(*properties.getBorderThickness().setReference(properties.getLength(), false));\
        properties.setBorderRoundness(*properties.getBorderRoundness().setReference(properties.getBorderThickness(), false));\

#define NO_VIEW UINT8_MAX

class Container {
  public:
    //temporary
    Container();
    
    Container(ContainerProperties properties, std::vector<Container*> content);

    virtual void init();
    virtual void draw();
    void drawBorder(bool erase = false);

    ContainerProperties getPorperties();
    void setProperties(ContainerProperties properties);

    void setBackground(uint16_t color);
    uint16_t getColor();

    void addContent(Container* content);
    void removeContent(byte id);
    uint8_t getContentAmount();

    void setContentProperties(ContainerProperties properties);

  private:
    ContainerProperties _properties;
    std::vector<Container*> _content;

    Container* getContent(byte id);
    std::vector<Container*>::iterator getIterator(byte id);

};

#endif
