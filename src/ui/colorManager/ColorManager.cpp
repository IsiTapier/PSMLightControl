/*
 ColorManager.cpp - ColorManager-Library for Librarys.
*/

#include "ColorManager.h"

std::vector<ColorPalette> ColorManager::colorPalettes = {
  ColorPalette(TFT_WHITE, TFT_BLACK, {TFT_DARKGREY, TFT_BLACK}),
  ColorPalette(TFT_DARKGREY, TFT_BLACK, TFT_WHITE, {TFT_LIGHTGREY, TFT_WHITE})
};
byte ColorManager::currentColorPalette = colorModes::darkMode;

void ColorManager::addColorPalette(ColorPalette colorPalette) {
  colorPalettes.push_back(colorPalette);
}
void ColorManager::setColorPalette(ColorPalette colorPalette) {
  colorPalettes.push_back(colorPalette);
  setColorPalette(colorPalettes.size()-1);
}

void ColorManager::setColorPalette(byte colorPalette) {
  currentColorPalette = colorPalette%colorPalettes.size();
}

ColorPalette ColorManager::getColorPalette(byte colorPalette) {
  return colorPalettes[colorPalette%colorPalettes.size()];
}

ColorPalette ColorManager::getColorPalette() {
  return getColorPalette(currentColorPalette);
}

byte ColorManager::getCurrentColorPalette() {
  return currentColorPalette;
}

uint16_t ColorManager::getContrastColor() {
  return getColorPalette().getContrastColor();
}

uint16_t ColorManager::getBorderColor() {
  return getColorPalette().getBorderColor();
}

uint16_t ColorManager::getTextColor() {
  return getColorPalette().getTextColor();
}

uint16_t ColorManager::getBackgroundColor() {
  return getColorPalette().getBackgroundColor();
}

uint16_t ColorManager::getContainerColor(uint8_t order) {
  return order==0?getBackgroundColor():getColorPalette().getContainerColor(order-1);
}