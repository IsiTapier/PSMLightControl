/*
 ColorPalette.cpp - ColorPalette-Library for Librarys.
*/

#include "ColorPalette.h"

ColorPalette::ColorPalette(uint32_t contrastColor, uint32_t backgroundColor, std::vector<uint32_t> containerColors) : _contrastColor(contrastColor), _backgroundColor(backgroundColor), _containerColors(containerColors), commonContrastColor(true) {
}

ColorPalette::ColorPalette(uint32_t borderColor, uint32_t textColor, uint32_t backgroundColor, std::vector<uint32_t> containerColors) : _borderColor(borderColor), _textColor(textColor), _backgroundColor(backgroundColor), _containerColors(containerColors), commonContrastColor(false) {
}

uint32_t ColorPalette::getContrastColor() {
  return commonContrastColor?_contrastColor:_borderColor;
}

uint32_t ColorPalette::getBorderColor() {
  return commonContrastColor?_contrastColor:_borderColor;
}

uint32_t ColorPalette::getTextColor() {
  return commonContrastColor?_contrastColor:_textColor;

}

uint32_t ColorPalette::getBackgroundColor() {
  return _backgroundColor;
}

uint32_t ColorPalette::getContainerColor(uint8_t order) {
  return _containerColors[order%_containerColors.size()];
}