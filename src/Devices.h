#ifndef DEVICES_H
#define DEVICES_H

#include "DMXDevice.h"

#if UNIVERSE_2_ACTIVE && UNIVERSE_1_ACTIVE
DMXDevice strahler(UNIVERSE_2, 19, MRGBWSE, UNIVERSE_1, 19, MRGB, 1, 8);
DMXDevice strahlerNeu(UNIVERSE_2, 509, RGB, UNIVERSE_1, 19, MRGB, 1);
DMXDevice strahlerNeu2(UNIVERSE_2, 140, RGB, UNIVERSE_1, 19, MRGB, 1);
DMXDevice bars(UNIVERSE_2, 150, RGB, UNIVERSE_1, 150, RGB, 12, 9);
// DMXDevice bar(UNIVERSE_2, 78, RGB, UNIVERSE_1, 150, RGB, 12, 1);
// DMXDevice barsSide(UNIVERSE_2, 481, RGB, UNIVERSE_1, 150, RGB);
  DMXDevice blinder1(UNIVERSE_2, 76, M, UNIVERSE_1, 76, M, 10, 1);
  DMXDevice blinder2(UNIVERSE_2, 484, M, UNIVERSE_1, 76, M, 10, 1);
DMXDevice blinder[3] = {
  blinder1,
  blinder2,
  // DMXDevice(UNIVERSE_2, 139, M, UNIVERSE_1, 484, M, 10, 1),
};
#endif


#endif