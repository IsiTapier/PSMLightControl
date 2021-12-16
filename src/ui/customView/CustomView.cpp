/*
 CustomView.cpp - CustomView-Library for Librarys.
*/

#include "CustomView.h"

CustomView::CustomView(ContainerProperties properties, ViewProperties viewProperties, std::function<void()> init, std::function<void()> draw, std::function<void(TSPoint)> checkTouch) : View(properties, viewProperties, {}), _init(init), _draw(draw), _checkTouch(checkTouch) {
}

void CustomView::init() {
  View::init();
  _init();
}

void CustomView::draw() {
  View::draw();
  _draw();
}

void CustomView::checkTouch(TSPoint p) {
  _checkTouch(p);
}