/*
 ButtonManager.cpp - ButtonManager-Library for Librarys.
*/

#include "ButtonManager.h"

std::vector<Button> ButtonManager::buttons;

void ButtonManager::init() {
  xTaskCreate(checkTouch, "check touch", 1024, NULL, 8, NULL);
}

void ButtonManager::addButton(Button button) {
  buttons.push_back(button);
}

void ButtonManager::checkTouch(void*) {
  for(Button button : buttons) {
    
  }
}