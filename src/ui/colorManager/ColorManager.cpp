/*
 ColorManager.cpp - ColorManager-Library for Librarys.
*/

#include "ColorManager.h"

std::vector<ColorPalette> ColorManager::colorPalettes = {
  ColorPalette(TFT_WHITE, TFT_BLACK, {TFT_DARKGREY, TFT_LIGHTGREY}),
  ColorPalette(TFT_BLACK, TFT_WHITE, {TFT_LIGHTGREY, TFT_DARKGREY})
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

uint32_t ColorManager::getContrastColor() {
  return getColorPalette().getContrastColor();
}

uint32_t ColorManager::getBorderColor() {
  return getColorPalette().getBorderColor();
}

uint32_t ColorManager::getTextColor() {
  return getColorPalette().getTextColor();
}

uint32_t ColorManager::getBackgroundColor() {
  return getColorPalette().getBackgroundColor();
}

uint32_t ColorManager::getContainerColor(uint8_t order) {
  return getColorPalette().getContainerColor(order);
}