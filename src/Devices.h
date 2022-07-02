#ifndef DEVICES_H
#define DEVICES_H

#include "DMXDevice.h"

#if UNIVERSE_2_ACTIVE && UNIVERSE_1_ACTIVE
DMXDevice strahler(UNIVERSE_2, 19, MRGBWSE, UNIVERSE_1, 19, MRGB, 1, 7);
DMXDevice strahlerNeu(UNIVERSE_2, 68, RGBW, UNIVERSE_1, 20, RGB, 1, 2);
DMXDevice bars(UNIVERSE_2, 150, RGB, UNIVERSE_1, 150, RGB, 12, 7);
// DMXDevice bar(UNIVERSE_2, 78, RGB, UNIVERSE_1, 150, RGB, 12, 1);
// DMXDevice barsSide(UNIVERSE_2, 481, RGB, UNIVERSE_1, 150, RGB);
DMXDevice blinder[3] = {
  DMXDevice(UNIVERSE_2, 76, M, UNIVERSE_1, 474, M, 10, 2),
  DMXDevice(UNIVERSE_2, 139, M, UNIVERSE_1, 474, M, 10, 1),
  DMXDevice(UNIVERSE_2, 484, M, UNIVERSE_1, 474, M, 10, 1)
};
#endif


#endif