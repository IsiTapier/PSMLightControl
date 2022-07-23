#include <Arduino.h>
#include "dmx.h"
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

#include "Devices.h"

#if UNIVERSE_3_ACTIVE && UNIVERSE_1_ACTIVE
#include "MovingHead.h"
MovingHead movingHead1(HEIGHT_MV1, X_OFFSET_MV1, Y_OFFSET, TILT_OFFSET_MV1, PAN_OFFSET_MV1, UNIVERSE_3, 1,  INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV1, HEIGHT_ADDRESS_MV1, Position(X_DEFAULT_MV1, Y_DEFAULT));
MovingHead movingHead2(HEIGHT_MV2, X_OFFSET_MV2, Y_OFFSET, TILT_OFFSET_MV2, PAN_OFFSET_MV2, UNIVERSE_3, 14, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV2, HEIGHT_ADDRESS_MV2, Position(X_DEFAULT_MV2, Y_DEFAULT));
MovingHead movingHead3(HEIGHT_MV3, X_OFFSET_MV3, Y_OFFSET, TILT_OFFSET_MV3, PAN_OFFSET_MV3, UNIVERSE_3, 27, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV3, HEIGHT_ADDRESS_MV3, Position(X_DEFAULT_MV3, Y_DEFAULT));
MovingHead movingHead4(HEIGHT_MV4, X_OFFSET_MV4, Y_OFFSET, TILT_OFFSET_MV4, PAN_OFFSET_MV4, UNIVERSE_3, 40, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV4, HEIGHT_ADDRESS_MV4, Position(X_DEFAULT_MV4, Y_DEFAULT));
MovingHead movingHead5(HEIGHT_MV5, X_OFFSET_MV5, Y_OFFSET, TILT_OFFSET_MV5, PAN_OFFSET_MV5, UNIVERSE_3, 53, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV5, HEIGHT_ADDRESS_MV5, Position(X_DEFAULT_MV5, Y_DEFAULT));
MovingHead movingHead6(HEIGHT_MV6, X_OFFSET_MV6, Y_OFFSET, TILT_OFFSET_MV6, PAN_OFFSET_MV6, UNIVERSE_3, 66, INPUT_UNIVERSE_ALL, INPUT_ADDRESS_MV6, HEIGHT_ADDRESS_MV6, Position(X_DEFAULT_MV6, Y_DEFAULT));
// DMXDevice strahlerNeu2(UNIVERSE_3, 68, RGBW, 1, UNIVERSE_1, 68, RGBW, 2);
#endif

#include "ui/Ui.h"

void setup() {
  #if DEBUG
    Serial.begin(115200);
    Serial.println(F("init"));
  #endif

#if UNIVERSE_3_ACTIVE
  MovingHead::init(1);

  Ui::init();
#endif
// DMXDevice::init();
#if DEBUG
  Serial.println(F("setup complete"));
#endif
}

void loop() {
  // Serial.print("Free Heap: ");Serial.println(esp_get_free_heap_size());
  // Serial.print("Biggest Heap Size: ");Serial.println(heap_caps_get_largest_free_block(8));
  // heap_caps_print_heap_info(8);
  // Serial.print("Size of Container: ");Serial.println(sizeof(Container));
  // Serial.print("Size of Button: ");Serial.println(sizeof(Button));
  
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
