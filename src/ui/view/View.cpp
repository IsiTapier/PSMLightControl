/*
 View.cpp - View-Library for Librarys.
*/

#include "View.h"

byte View::currentId = 0;

View::View(ContainerProperties properties, ViewProperties viewProperties, std::vector<Container*> content) : Container(properties, content), _viewProperties(viewProperties), id(currentId) {
  currentId++;
  ViewManager::addView(this);
}

byte View::getId() {
  return id;
}

byte View::getCurrentId() {
  return currentId;
}

void View::init() {
  ContainerProperties properties = getPorperties();
  Spacing padding = properties.getPadding();
  properties.setDraw(true);
  properties.setXY(padding.get(LEFT), padding.get(TOP));
  properties.setLength(*Size(TFT_HEIGHT-padding.get(LEFT)-padding.get(RIGHT)).setReference(TFT_HEIGHT, false));
  properties.setHeight(*Size(TFT_WIDTH-padding.get(TOP)-padding.get(BOTTOM)).setReference(TFT_WIDTH, false));
  properties.setOrder(0);
  properties.setViewId(id);
  CONTAINER_SET_REFERENCES(properties)
  setProperties(properties);
  Container::init();
}

void View::draw() {
  Container::draw();
}