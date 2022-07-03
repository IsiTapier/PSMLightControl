/*
  AnimationUi.h - AnimationUi-Library for Airduino.
*/

#ifndef Animation_h
#define Animation_h

#include "../../../Devices.h"
#include "./Effect/Effect.h"

Effect lauflicht(&strahler, 255, 500, 0, 1., Effect::RIGHT);

Effect dimm(&strahler, 255, 50, 2, .1, Effect::BOTH);

Effect wave(&strahler, 255, 50, 8, .1, Effect::RIGHT, false);

Effect waveLeft(&bars, 255, 20, bars.getDevices(true)/2, 1., Effect::LEFT);
Effect waveRight(&bars, 255, 20, bars.getDevices(true)/2, 1., Effect::RIGHT);

Effect streifen1(&blinder1, 70, 20, 12, .2, Effect::LEFT);
Effect streifen2(&blinder2, 70, 20, 12, .2, Effect::LEFT);
// Effect streifen3(&blinder[2], 255, 20, 5, .2, Effect::RIGHT);


#endif