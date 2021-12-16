/*
 ContainerGrid.cpp - ContainerGrid-Library for Librarys.
*/

#include "ContainerGrid.h"

ContainerGrid::ContainerGrid(ContainerProperties properties, ContainerProperties contentProperties, bool autoSize, std::vector<Container*> content) : Container(properties, content), _contentProperties(contentProperties), _autoSize(autoSize) {
}

#define PADDING(direction) (padding.get(direction).getMode()==ABSOLUTE?(short)padding.get(direction):(padding.get(direction).getProportion()*size))
#define SIDE(x, y) (MAX(PADDING(x), margin.get(y)))
#define MIDDLE(x, y) (MAX(PADDING(x), PADDING(y)))
#define LENGTH (size*columns+SIDE(LEFT, RIGHT)+SIDE(RIGHT, LEFT))
#define HEIGHT (size*rows*_contentProperties.getFormat()+SIDE(TOP, BOTTOM)+SIDE(BOTTOM, TOP))
#define EQUAL_AMOUNT (floor(columns)*floor(rows)>=getContentAmount())

void ContainerGrid::init() {
  if(getContentAmount() == 0)
    return Container::init();
  if(_autoSize) {
    // get some sizes
    ContainerProperties properties = getPorperties();
    Spacing padding = _contentProperties.getPadding();
    Spacing margin = properties.getMargin();
    byte distanceHorizontal = MAX(padding.get(LEFT), padding.get(RIGHT));
    byte distanceVertical = MAX(padding.get(TOP), padding.get(BOTTOM));
    short length = properties.getContentLength() - MAX(margin.get(LEFT), padding.get(LEFT)) - MAX(margin.get(RIGHT), padding.get(RIGHT)) + distanceHorizontal;
    short height = properties.getContentHeight() - MAX(margin.get(TOP), padding.get(TOP)) - MAX(margin.get(BOTTOM), padding.get(BOTTOM)) + distanceVertical;
    short contentLength = _contentProperties.getLength() + MAX(padding.get(LEFT), padding.get(RIGHT));
    short contentHeight = _contentProperties.getHeight() + MAX(padding.get(TOP), padding.get(BOTTOM));
    float format = _contentProperties.getHeight().getMode()==RELATIVE?_contentProperties.getFormat():contentHeight/contentLength;
    // calculate rows and columns
    float columns = sqrt(getContentAmount()*(length/(double)height)*format);
    float rows = sqrt(getContentAmount()*(height/(double)length)/format);
    if(!EQUAL_AMOUNT) {
      if(columns-floor(columns)>rows-floor(rows))
        columns = ceil(columns);
      else
        rows = ceil(rows);
      if(!EQUAL_AMOUNT) {
        columns = ceil(columns);
        rows = ceil(rows);
      } else {
        columns = floor(columns);
        rows = floor(rows);
      }
      if(!EQUAL_AMOUNT)
        if(DEBUG)
          Serial.println(F("WARNING:\tfailed to calculate rows and columns of container grid"));
    }
    Serial.println(rows);
    Serial.println(columns);
    // calculate size
    length = properties.getContentLength();
    height = properties.getContentHeight();
    Serial.println(length);
    Serial.println(height);
    float pProportionVertical = 0;
    float pProportionHorizontal = 0;
    if(padding.get(LEFT).getMode() == ABSOLUTE || padding.get(RIGHT).getMode() == ABSOLUTE)
      length -= columns*distanceHorizontal;
    else
      pProportionHorizontal += max(padding.get(LEFT).getProportion(), padding.get(RIGHT).getProportion());
    if(padding.get(TOP).getMode() == ABSOLUTE ||padding.get(BOTTOM).getMode() == ABSOLUTE)
      height -= rows*distanceVertical;
    else
      pProportionVertical += max(padding.get(TOP).getProportion(), padding.get(BOTTOM).getProportion());
    short size = MIN(length/columns*(1-pProportionHorizontal)/(1+pProportionHorizontal), height/rows*(1-pProportionVertical)/(1+pProportionVertical));
    Serial.println(size);
    // correct size
    length = properties.getContentLength();
    height = properties.getContentHeight();
    while(length>LENGTH&&height>HEIGHT)
      size++;
    vTaskDelay(1);
    while(length<LENGTH||height<HEIGHT)
      size--;
    Serial.println(size);
    // set size
    _contentProperties.setHeight(size*_contentProperties.getFormat());
    _contentProperties.setLength(size);
    // _contentProperties.setPadding(*_contentProperties.getPadding().setReference(size, _contentProperties.getHeight()));
    // _contentProperties.setMargin(*_contentProperties.getMargin().setReference(_contentProperties.getContentLength(),_contentProperties.getContentHeight()));
    // _contentProperties.setBorderThickness(*_contentProperties.getBorderThickness().setReference(size));
  }
  setContentProperties(_contentProperties);
  Container::init();
}