/*
 Button.cpp - Button-Library for Librarys.
*/

#include "Button.h"

Button::Button(ContainerProperties properties, ButtonProperties buttonProperties, std::function<void()> touchEvent) : Container(properties, {}), _buttonProperties(buttonProperties), _touchEvent(touchEvent) {
}

void Button::draw() {
  setProperties(*getPorperties().setBackgroundColor(triggered?_buttonProperties.getPressedColor():_buttonProperties.getColor()));
  Container::draw();
}

byte Button::checkTouch() {
}

void Button::trigger() {
  _touchEvent();
}