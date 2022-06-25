/*
 CustomView.cpp - CustomView-Library for Librarys.
*/

#include "CustomView.h"

//temporary
CustomView::CustomView() {}

CustomView::CustomView(ContainerProperties properties, ViewProperties viewProperties, std::function<void()> init, std::function<void()> draw, std::function<uint16_t(TSPoint)> checkTouch, std::vector<Container*> content, std::vector<Container*> navBarContent) : View(properties, viewProperties, content, navBarContent), _init(init), _draw(draw), _checkTouch(checkTouch) {
}

void CustomView::init() {
  View::init();
  _init();
}

void CustomView::draw(short startX, short startY, short endX, short endY, bool fill) {
  CHECK_DRAW
  View::draw(startX, startY, endX, endY, fill);
  _draw();
}

uint16_t CustomView::checkTouch(TSPoint p) {
  return _checkTouch(p);
}