/*
  Macros.h - Macros-Library for Airduino.
*/

#ifndef Macros_h
#define Macros_h

#include "Arduino.h"

//SONDER ZEICHEN
#define AE String(char(142))
#define ae String(char(132))
#define OE String(char(153))
#define oe String(char(148))
#define UE String(char(154))
#define ue String(char(129))
//#define ss String(char(225))

#define SETMAX(x, value)    if((x) < (value)) (x) = (value);
#define SETMIN(x, value)    if((x) > (value)) (x) = (value);
#define MIN(x, y)           min((int) (x), (int) (y))
#define MAX(x, y)           max((int) (x), (int) (y))
#define MIN4(a, b, c, d)    MIN(MIN(a, b), MIN(c, d))
#define MAX4(a, b, c, d)    MAX(MAX(a, b), MAX(c, d))
#define IFGREATER(x, y, value)  (((x)>(y))?(value):(x))
#define IFSMALLER(x, y, value)  (((x)<(y))?(value):(x))
#define ABSOLUTEGREATER(x, y)   (abs(x)>abs(y)?(x):(y))
#define ABSOLUTESMALLER(x, y)   (abs(x)<abs(y)?(x):(y))
#define SETABSOLUTEGREATER(x, y)   (x=ABSOLUTEGREATER(x,y))
#define SETABSOLUTESMALLER(x, y)   (x=ABSOLUTESMALLER(x,y))
#define IF(x, value, y)     (((x)==(value))?(x):(y))
#define IFNOT(x, value, y)  (((x)!=(value))?(x):(y))

//font
#define LETTER_LENGTH              6
#define LETTER_HEIGHT              8

#define SIZE(width, height, letters) (                                            \
  ((width <= 0 && height <= 0) || (height <= 0 && letters <= 0)) ? 1 :            \
  (width <= 0)  ? GETSIZE(TFT_HEIGHT, height, 1) :                            \
  (height <= 0) ? GETSIZE(width, TFT_WIDTH, letters) :                       \
                  GETSIZE(width, height, letters))

#define GETSIZE(width, height, letters) max((int) min(floor(height / LETTER_HEIGHT), floor(width / (LETTER_LENGTH*letters - 1))), 1)

#define GPIO_NUM(number) (              \
            number==0?GPIO_NUM_0:       \
            number==1?GPIO_NUM_1:       \
            number==2?GPIO_NUM_2:       \
            number==3?GPIO_NUM_3:       \
            number==4?GPIO_NUM_4:       \
            number==5?GPIO_NUM_5:       \
            number==6?GPIO_NUM_6:       \
            number==7?GPIO_NUM_7:       \
            number==8?GPIO_NUM_8:       \
            number==9?GPIO_NUM_9:       \
            number==10?GPIO_NUM_10:     \
            number==11?GPIO_NUM_11:     \
            number==12?GPIO_NUM_12:     \
            number==13?GPIO_NUM_13:     \
            number==14?GPIO_NUM_14:     \
            number==15?GPIO_NUM_15:     \
            number==16?GPIO_NUM_16:     \
            number==17?GPIO_NUM_17:     \
            number==18?GPIO_NUM_18:     \
            number==19?GPIO_NUM_19:     \
            number==20?GPIO_NUM_20:     \
            number==21?GPIO_NUM_21:     \
            number==22?GPIO_NUM_22:     \
            number==23?GPIO_NUM_23:     \
            number==24?GPIO_NUM_24:     \
            number==25?GPIO_NUM_25:     \
            number==26?GPIO_NUM_26:     \
            number==27?GPIO_NUM_27:     \
            number==28?GPIO_NUM_28:     \
            number==29?GPIO_NUM_29:     \
            number==30?GPIO_NUM_30:     \
            number==31?GPIO_NUM_31:     \
            number==32?GPIO_NUM_32:     \
            number==33?GPIO_NUM_33:     \
            number==34?GPIO_NUM_34:     \
            number==35?GPIO_NUM_35:     \
            number==36?GPIO_NUM_36:     \
            number==37?GPIO_NUM_37:     \
            number==38?GPIO_NUM_38:     \
            number==39?GPIO_NUM_39:GPIO_NUM_MAX )

#endif