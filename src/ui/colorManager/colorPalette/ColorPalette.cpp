/*
 ColorPalette.cpp - ColorPalette-Library for Librarys.
*/

#include "ColorPalette.h"

ColorPalette::ColorPalette(uint16_t contrastColor, uint16_t backgroundColor, std::vector<uint16_t> containerColors) : _contrastColor(contrastColor), _backgroundColor(backgroundColor), _containerColors(containerColors), commonContrastColor(true) {
}

ColorPalette::ColorPalette(uint16_t borderColor, uint16_t textColor, uint16_t backgroundColor, std::vector<uint16_t> containerColors) : _borderColor(borderColor), _textColor(textColor), _backgroundColor(backgroundColor), _containerColors(containerColors), commonContrastColor(false) {
}

uint16_t ColorPalette::getContrastColor() {
  return commonContrastColor?_contrastColor:_borderColor;
}

uint16_t ColorPalette::getBorderColor() {
  return commonContrastColor?_contrastColor:_borderColor;
}

uint16_t ColorPalette::getTextColor() {
  return commonContrastColor?_contrastColor:_textColor;

}

uint16_t ColorPalette::getBackgroundColor() {
  return _backgroundColor;
}

uint16_t ColorPalette::getContainerColor(uint8_t order) {
  return _containerColors[order%_containerColors.size()];
}