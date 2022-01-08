/*
 Button.cpp - Button-Library for Librarys.
*/

#include "Button.h"

Button::Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<uint16_t()> touchEvent, std::vector<Container*> content) : Container(properties, content), _buttonProperties(buttonProperties), _touchEvent(touchEvent) {
}

void Button::init() {
  Container::init();
  if(_buttonProperties.getColor() == NO_COLOR)
    _buttonProperties.setColor(getColor());
  _buttonProperties.setTouchExtension(*_buttonProperties.getTouchExtension().setReference(getPorperties().getLength(), getPorperties().getHeight(), false));
  if(getPorperties().getDraw())
    if(_id==-1)
      ButtonManager::addButton(this);
}

void Button::draw() {
  setBackground(triggered?IFNOT(_buttonProperties.getPressedColor(), NO_COLOR, display.setBrightness(display.getBrightness(_buttonProperties.getColor())<128?-COLOR_SHIFT:1.5*COLOR_SHIFT, _buttonProperties.getColor())):_buttonProperties.getColor());
  Container::draw();
}

ButtonProperties Button::getProperties() {
  return _buttonProperties;
}

byte Button::checkTouch(TSPoint p) {
  ContainerProperties cp = getPorperties();
  byte distance = 0;
  SETMAX(distance, MAX(IFGREATER(max(cp.getX()-p.x,0),_buttonProperties.getTouchExtension().get(LEFT), UINT8_MAX), IFGREATER(max(p.x-cp.getX()-cp.getLength(),0),_buttonProperties.getTouchExtension().get(RIGHT), UINT8_MAX)))
  SETMAX(distance, MAX(IFGREATER(max(cp.getY()-p.y,0),_buttonProperties.getTouchExtension().get(TOP), UINT8_MAX), IFGREATER(max(p.y-cp.getY()-cp.getHeight(),0),_buttonProperties.getTouchExtension().get(BOTTOM), UINT8_MAX)))
  return distance;
}

uint16_t Button::trigger() {
  if(triggered)
    return 0;
  triggered = true;
  draw();
  return _touchEvent();
}

void Button::untrigger() {
  if(!triggered)
    return;
  triggered = false;
  draw();
}

void Button::setId(short id) {
  _id = id;
}

short Button::getId() {
  return _id;
}