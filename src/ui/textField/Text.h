/*
  Text.h - Text-Library for Airduino.
*/

#ifndef Text_h
#define Text_h

#include "Arduino.h"
#include "../container/Container.h"
#include "textProperties/TextProperties.h"
#include "Util.h"

//TEMP!!
#define BACKGROUND_COLOR TFT_BLACK

class Text : public Container {
  public:
    Text(ContainerProperties properties, TextProperties textProperties, String text);

    void init(short x, short y) override;
    void draw() override;

    static void dPrint(String text, int x, int y, int size, int color, int datum = 0, int backgroundColor = -1, String oldText = "", int oldTextSize = -1, boolean redraw = false, int padding = 0);
    
    static void dPrint(int text, int x, int y, int size, int color, int datum = 0, int backgroundColor = -1, int oldText = -1, int oldTextSize = -1, boolean redraw = false, int padding = 0);

  private:
    TextProperties _textProperties;
    String _text;

};

#endif
