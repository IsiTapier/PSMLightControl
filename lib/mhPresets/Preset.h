/*
  Preset.h - Preset-Library for Airduino.
*/

#ifndef Preset_h
#define Preset_h

#include "MovingHead.h"

class Preset {
  public:
    Preset();
    Preset(std::array<Position, MOVING_HEADS_AMOUNT> positions, Position positionAll);

    std::array<Position, MOVING_HEADS_AMOUNT> getPositions();
    Position getPosition(byte i);
    Position getPositionAll();

    void activate();

    static Preset getDefaultPositions();

  private:
    std::array<Position, MOVING_HEADS_AMOUNT> positions;
    Position positionAll;

};

struct PresetObj {
    byte id;
    Preset preset;
};

struct PresetData {
    byte currentPosition = 1;
    PresetObj presetObjs[20] = {{0, Preset::getDefaultPositions()}};
};


// #include "Arduino.h"
// #include "EEPROM.h"
// #include "Position.h"
// #include "functional"
// #include "vector"

// //temporary
// #define MOVING_HEADS_AMOUNT 6
// #define X_DEFAULT 0
// #define Y_DEFAULT 0

// class Presets {
//   public:
//     Presets();
//     static void setUpdate(std::function<void()> update);
    
//     static std::vector<std::array<Position, MOVING_HEADS_AMOUNT+1>> presetPositions;

//   private:
//     static void readEeprom();
//     static void storeEeprom();

//     static std::function<void()> _update;

// };

#endif