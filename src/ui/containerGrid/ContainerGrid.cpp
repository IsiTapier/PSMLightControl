/*
 ContainerGrid.cpp - ContainerGrid-Library for Librarys.
*/

#include "ContainerGrid.h"

ContainerGrid::ContainerGrid(ContainerProperties properties, ContainerProperties contentProperties, bool autoSize, std::vector<Container*> content) : Container(properties, content), _contentProperties(contentProperties), _autoSize(autoSize) {
}

void ContainerGrid::init() {
  if(_autoSize) {
    ContainerProperties properties = getPorperties();
    Spacing padding = _contentProperties.getPadding();
    Spacing margin = properties.getMargin();
    byte distanceHorizontal = MAX(padding.get(LEFT), padding.get(RIGHT));
    byte distanceVertical = MAX(padding.get(TOP), padding.get(BOTTOM));
    short length = properties.getContentLength() - MAX(margin.get(LEFT), padding.get(LEFT)) - MAX(margin.get(RIGHT), padding.get(RIGHT)) + distanceHorizontal;
    short height = properties.getContentHeight() - MAX(margin.get(TOP), padding.get(TOP)) - MAX(margin.get(BOTTOM), padding.get(BOTTOM)) + distanceVertical;
    short contentLength = _contentProperties.getLength() + MAX(padding.get(LEFT), padding.get(RIGHT));
    short contentHeight = _contentProperties.getHeight() + MAX(padding.get(TOP), padding.get(BOTTOM));
    float columns = sqrt(getContentAmount()*(length/height)*(contentHeight/contentLength));
    float rows = sqrt(getContentAmount()*(height/length)*(contentLength/contentHeight));
    length = properties.getContentLength();
    height = properties.getContentHeight();
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
  }
  Container::init();
}