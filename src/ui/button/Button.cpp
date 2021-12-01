/*
 Button.cpp - Button-Library for Librarys.
*/

#include "Button.h"

Button::Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<void()> touchEvent, std::vector<Container*> content) : Container(properties, content), _buttonProperties(buttonProperties), _touchEvent(touchEvent) {
}

void Button::init(short x, short y) {
  Container::init(x, y);
  _buttonProperties.setTouchExtension(*_buttonProperties.getTouchExtension().setReference(getPorperties().getLength(), getPorperties().getHeight(), false));
  ButtonManager::addButton(this);
}

void Button::draw() {
  setBackground(triggered?_buttonProperties.getPressedColor():_buttonProperties.getColor());
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

void Button::trigger() {
  if(triggered)
    return;
  triggered = true;
  draw();
  _touchEvent();
}

void Button::untrigger() {
  if(!triggered)
    return;
  triggered = false;
  draw();
}