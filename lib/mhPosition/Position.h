/*
  Position.h - Position-Library for Airduino.
*/

#ifndef Position_h
#define Position_h

#include "Arduino.h"

class Position {
  public:
    Position() : _x(-__FLT_MIN_EXP__), _y(__FLT_MIN_EXP__) {}
    Position(float x, float y) : _x(x), _y(y) {}
    void setX(float x) {_x = x;}
    void setY(float y) {_y = y;}
    float getX() {return _x;}
    float getY() {return _y;}
    bool isSet() {return _x == __FLT_MIN_EXP__ || _y == __FLT_MIN_EXP__;}
    Position operator+(Position p) const {Position result(_x+p.getX(), _y+p.getY());return result;}
    Position operator-(Position p) const {Position result(_x-p.getX(), _y-p.getY());return result;}
  private:
    float _x, _y;
};

#endif