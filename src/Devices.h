#ifndef DEVICES_H
#define DEVICES_H

#include "DMXDevice.h"

#if UNIVERSE_2_ACTIVE && UNIVERSE_1_ACTIVE
extern DMXDevice strahler;
// extern DMXDevice strahlerNeu;
// extern DMXDevice strahlerNeu2;
extern DMXDevice bars;
// extern DMXDevice bar;
// extern DMXDevice barsSide;
  extern DMXDevice blinder1;
  extern DMXDevice blinder2;
extern DMXDevice blinder[3];

#endif


#endif