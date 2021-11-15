/*
 View.cpp - View-Library for Librarys.
*/

#include "View.h"

byte View::currentId = 0;

View::View(ContainerProperties properties, ViewProperties viewProperties, std::vector<Container*> content) : Container(properties, content), _viewProperties(viewProperties), id(currentId) {
  currentId++;
}

byte View::getId() {
  return id;
}

byte View::getCurrentId() {
  return currentId;
}

void View::init(short x, short y) {
  ContainerProperties properties = getPorperties();
  Spacing padding = properties.getPadding();
  properties.setDraw(true);
  properties.setXY(padding.get(LEFT), padding.get(TOP));
  properties.setLength(TFT_HEIGHT-padding.get(LEFT)-padding.get(RIGHT));
  properties.setHeight(TFT_WIDTH-padding.get(TOP)-padding.get(BOTTOM));
  properties.getLength().setReference(TFT_HEIGHT, false);
  properties.getHeight().setReference(TFT_WIDTH, false);
  properties.getPadding().setReference(properties.getLength(), properties.getHeight(), false);
  properties.getMargin().setReference(properties.getLength(), properties.getHeight(), false);
  properties.getBorderThickness().setReference(properties.getLength(), false);
  properties.getBorderRoundness().setReference(properties.getBorderThickness(), false);
  setProperties(properties);
  Container::init(properties.getX(), properties.getY());
}

void View::draw() {
  Container::draw();
}