/*
  Presets.h - Presets-Library for Airduino.
*/

#ifndef Presets_h
#define Presets_h

#include "Arduino.h"
#include "EEPROM.h"
#include "Position.h"
#include "functional"
#include "vector"

//temporary
#define MOVING_HEADS_AMOUNT 6
#define X_DEFAULT 0
#define Y_DEFAULT 0

class Presets {
  public:
    Presets();
    static void setUpdate(std::function<void()> update);
    
    static std::vector<std::array<Position, MOVING_HEADS_AMOUNT+1>> presetPositions;

  private:
    static void readEeprom();
    static void storeEeprom();

    static std::function<void()> _update;

};

#endif