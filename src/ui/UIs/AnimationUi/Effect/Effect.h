/*
  Effect.h - Effect-Library for Airduino.
*/

#ifndef Effect_h
#define Effect_h

#include "../../dmxDevice/DMXDevice.h"



class Effect {
    public:
        enum Direction {
            LEFT,
            RIGHT,
            BOTH
        };
        Effect(DMXDevice* device, byte overrideValue, short speed, byte spread = 0, float increase = 1, Direction direction = LEFT, bool doOverlap = true);
        void toggle();

    private:
        bool active;
        TaskHandle_t handle;

        struct Parameter {
            DMXDevice* _device;
            byte _overrideValue;
            short _speed;
            byte _spread;
            float _increase;
            Direction _direction;
            bool _doOverlap;
        } _parameter;
};

#endif