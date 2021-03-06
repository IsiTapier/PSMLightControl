#include <Arduino.h>
#include "dmx.h"
#include "DMXDevice.h"
#include "ui/Ui.h"

Ui ui;

#include "Pins.h"

unsigned long readcycle = 0;

#if UNIVERSE_1_ACTIVE
DMX* universe1 = DMX::initUniverse(UNIVERSE_1, input, U1_IN, U1_OUT, U1_EN);
#endif
#if UNIVERSE_2_ACTIVE
DMX* universe2 = DMX::initUniverse(UNIVERSE_2, output, U2_IN, U2_OUT, U2_EN);
#endif
#if UNIVERSE_3_ACTIVE
DMX* universe3 = DMX::initUniverse(UNIVERSE_3, output, U3_IN, U3_OUT, U3_EN);
#endif

#if UNIVERSE_2_ACTIVE && UNIVERSE_1_ACTIVE
DMXDevice strahler(UNIVERSE_2, 19, MRGBWSE, UNIVERSE_1, 19, MRGB, 1, 7);
// DMXDevice strahlerNeu(UNIVERSE_2, 50, RGBW, UNIVERSE_1, 150, RGB, 1, 2);
// DMXDevice bars(UNIVERSE_2, 258, RGB, UNIVERSE_1, 150, RGB, 12, 7);
// DMXDevice bar(UNIVERSE_2, 78, RGB, UNIVERSE_1, 150, RGB, 12, 1);
// DMXDevice barsSide(UNIVERSE_2, 481, RGB, UNIVERSE_1, 150, RGB);
// DMXDevice blinder[3] = {
//   DMXDevice(UNIVERSE_2, 76, M, UNIVERSE_1, 474, M, 10, 2),
//   DMXDevice(UNIVERSE_2, 139, M, UNIVERSE_1, 474, M, 10, 1),
//   DMXDevice(UNIVERSE_2, 484, M, UNIVERSE_1, 474, M, 10, 1)
// };
#endif

#if UNIVERSE_3_ACTIVE && UNIVERSE_1_ACTIVE
#include "MovingHead.h"
MovingHead movingHead1(HEIGHT_MV1, X_OFFSET_MV1, Y_OFFSET, TILT_OFFSET_MV1, PAN_OFFSET_MV1, UNIVERSE_3, 1,  INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV1, HEIGHT_ADDRESS_MV1, X_DEFAULT_MV1);
MovingHead movingHead2(HEIGHT_MV2, X_OFFSET_MV2, Y_OFFSET, TILT_OFFSET_MV2, PAN_OFFSET_MV2, UNIVERSE_3, 14, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV2, HEIGHT_ADDRESS_MV2, X_DEFAULT_MV2);
MovingHead movingHead3(HEIGHT_MV3, X_OFFSET_MV3, Y_OFFSET, TILT_OFFSET_MV3, PAN_OFFSET_MV3, UNIVERSE_3, 27, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV3, HEIGHT_ADDRESS_MV3, X_DEFAULT_MV3);
MovingHead movingHead4(HEIGHT_MV4, X_OFFSET_MV4, Y_OFFSET, TILT_OFFSET_MV4, PAN_OFFSET_MV4, UNIVERSE_3, 40, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV4, HEIGHT_ADDRESS_MV4, X_DEFAULT_MV4);
MovingHead movingHead5(HEIGHT_MV5, X_OFFSET_MV5, Y_OFFSET, TILT_OFFSET_MV5, PAN_OFFSET_MV5, UNIVERSE_3, 53, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV5, HEIGHT_ADDRESS_MV5, X_DEFAULT_MV5);
MovingHead movingHead6(HEIGHT_MV6, X_OFFSET_MV6, Y_OFFSET, TILT_OFFSET_MV6, PAN_OFFSET_MV6, UNIVERSE_3, 66, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV6, HEIGHT_ADDRESS_MV6, X_DEFAULT_MV6);
// DMXDevice strahlerNeu2(UNIVERSE_3, 68, RGBW, 1, UNIVERSE_1, 68, RGBW, 2);
#endif

void setup() {
  #if DEBUG
    Serial.begin(115200);
  #endif
  ui.init();
#if UNIVERSE_3_ACTIVE
  MovingHead::init(1);
#endif
// DMXDevice::init();
}

void loop() {
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
