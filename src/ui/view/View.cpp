/*
 View.cpp - View-Library for Librarys.
*/

#include "View.h"

byte View::currentId = 0;

//temporary
View::View() {}


View::View(ContainerProperties properties, ViewProperties viewProperties, std::vector<Container*> content, std::vector<Container*> navBarContent) : 
  Container(properties, {
    new NavBar(ContainerProperties(0, 0), navBarContent),
    new Container(*ContainerProperties(Size(1., 1), Size(.75, 1)).setInvisible(true), {content})}
  ), _viewProperties(viewProperties), id(currentId) {
  
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
  ContainerProperties properties = getProperties();
  Spacing margin = properties.getMargin();
  properties.setDraw(true);
  properties.setXY(margin.get(LEFT), margin.get(TOP));
  properties.setLength(*Size(TFT_HEIGHT-margin.get(LEFT)-margin.get(RIGHT)).setReference(TFT_HEIGHT, false));
  properties.setHeight(*Size(TFT_WIDTH-margin.get(TOP)-margin.get(BOTTOM)).setReference(TFT_WIDTH, false));
  properties.setOrder(0);
  properties.setViewId(id);
  CONTAINER_SET_REFERENCES(properties)
  setProperties(properties);
  Container::init();
}

void View::draw() {
  Container::draw();
}

uint16_t View::checkTouch(TSPoint p) {
  return 0;
}

ViewProperties View::getViewProperties() {
  return _viewProperties;
}

View* View::setViewProperties(ViewProperties properties) {
  _viewProperties = properties;
  return this;
}