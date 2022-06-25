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
        properties.setBorderRoundness(*properties.getBorderRoundness().setReference(properties.getBorderThickness().getMax(), false));\

#define CONDITIONAL_DRAWING (startX != -1 || endX != -1 || startY != -1 || endY != -1)

#define CHECK_DRAW \
        Serial.print("draw: start: ");Serial.print(startX);Serial.print(" ");Serial.print(startY);\
        Serial.print(" end: ");Serial.print(endX);Serial.print(" ");Serial.print(endY);\
        if(!getProperties().getDraw()) return;\
        if(CONDITIONAL_DRAWING) {\
          ContainerProperties props = getProperties();\
          short x = props.getX();\
          short y = props.getY();\
          Serial.print(" container: start: ");Serial.print(x);Serial.print(" ");Serial.print(y);\
          short length = props.getLength();\
          short height = props.getHeight();\
          Serial.print(" end: ");Serial.print(x+length);Serial.print(" ");Serial.println(y+height);\
          if(startX > x+length) return;\
          if(startY > y+height) return;\
          if(endX < x) return;\
          if(endY < y) return;\
        }

#define NO_VIEW UINT8_MAX

class Container {
  public:
    //temporary
    Container();
    
    Container(ContainerProperties properties, std::vector<Container*> content);

    virtual void init();
    virtual void draw(short startX=-1, short startY=-1, short endY=-1, short endX=-1, bool fill=true);
    void drawBorder(bool erase = false, bool fill = true);

    ContainerProperties getProperties();
    void setProperties(ContainerProperties properties);

    void setBackground(uint16_t color);
    uint16_t getColor();

    void addContent(Container* content, bool atFront = false);
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
