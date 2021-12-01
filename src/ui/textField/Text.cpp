/*
 Text.cpp - Text-Library for Librarys.
*/

#include "Text.h"

Text::Text(ContainerProperties properties, TextProperties textProperties, String text) : Container(properties, {}), _textProperties(textProperties), _text(text) {
}

void Text::init(short x, short y) {
  ContainerProperties properties = getPorperties();
  short length = properties.getContentLength(true);
  short height = properties.getContentHeight(true);
  short size = MIN(_textProperties.getSize()==-1?MAX_TEXT_SIZE:(int)_textProperties.getSize(), SIZE(length, height, _text.length()));
  _textProperties.setSize(size);
  x+=properties.getBorderThickness()+properties.getMargin().get(LEFT);
  y+=properties.getBorderThickness()+properties.getMargin().get(TOP);
  switch(_textProperties.getDatum()) {
      case TL_DATUM: break;
      case TC_DATUM: x+=(size+length)/2; break;
      case TR_DATUM: x+=length; break;
      case CL_DATUM: y+=(size+height)/2; break;
      case CC_DATUM: y+=(size+height)/2; x+=(size+length)/2; break;
      case CR_DATUM: y+=(size+height)/2; x+=length; break;
      case BL_DATUM: y+=height; break;
      case BC_DATUM: y+=height; x+=(size+length)/2; break;
      case BR_DATUM: y+=height; x+=length; break;
  }
  if(size*_text.length()*LETTER_LENGTH > properties.getContentLength(true) || size*LETTER_HEIGHT > properties.getContentHeight(true)) {
    if(DEBUG) {
      if(size > 1)
        Serial.println("WARNING:\tText size miscalculated and Textfield supressed");
      else
        Serial.println("WARNING:\tTextfield supressed, because there wasn't enough space available");
    }
    properties.setDraw(false);
  } else
    properties.setDraw(true);
  _textProperties.setXY(x, y);
  setProperties(properties);
}

void Text::draw() {
    if(!getPorperties().getDraw())
      return;
    if(!_textProperties.getTransparent())
      drawBorder();
    if(_textProperties.getX() == -1 || _textProperties.getY() == -1)
      return;
    dPrint(_text, _textProperties.getX(), _textProperties.getY(), _textProperties.getSize(), _textProperties.getColor(), _textProperties.getDatum(), getPorperties().getBackgroundColor());
}

void Text::dPrint(String text, int x, int y, int size, int color, int datum, int backgroundColor, String oldText, int oldTextSize, boolean redraw, int padding) {
  display.setTextPadding(padding);
  display.setTextDatum(datum);
  if(backgroundColor == 0)
    backgroundColor = BACKGROUND_COLOR;
  if(oldText.length() != 0) {
    if(oldTextSize < 0)
      oldTextSize = size;
    int xold = x;
    if(datum % 3 == 1) {
      x -= size*LETTER_LENGTH*text.length()/2;
      xold -= oldTextSize*LETTER_LENGTH*oldText.length()/2;
      display.setTextDatum(datum-1);
    } else if(datum % 3 == 2) {
      x -= LETTER_LENGTH*size*text.length();
      xold -= LETTER_LENGTH*oldTextSize*oldText.length();
      display.setTextDatum(datum-2);
    }
    display.setTextColor(backgroundColor);
    display.setTextSize(oldTextSize);
    if(redraw) {
      display.drawString(oldText, x, y);
      display.setTextColor(color);
      display.setTextSize(size);
      display.drawString(text, x, y);
    } else {
      for(int i = 0; i < oldText.length(); i++) {
        if(text.charAt(i) != oldText.charAt(i) || text.length() != oldText.length()) {
          display.drawString((String) oldText.charAt(i), (xold+LETTER_LENGTH*oldTextSize*i), y);
        }
      }
      display.setTextColor(color);
      display.setTextSize(size);
      for(int i = 0; i < text.length(); i++) {
        if(text.charAt(i) != oldText.charAt(i) || text.length() != oldText.length()) {
          display.drawString((String) text.charAt(i), x+LETTER_LENGTH*size*i, y);
        }
      }
    }
  } else {
    display.setTextSize(size);
    display.setCursor(x, y);
    if(backgroundColor > 0)
      display.setTextColor(color, backgroundColor);
    else
      display.setTextColor(color);
    display.drawString(text);
  }
}

//Verkürzung: Writing mit Integern
void Text::dPrint(int text, int x, int y, int size, int color, int datum, int backgroundColor, int oldText, int oldTextSize, boolean redraw, int padding) {
  dPrint(String(text), x, y, size, color, datum, backgroundColor, (oldText == -1) ? "" : String(oldText), oldTextSize, redraw, padding);
}