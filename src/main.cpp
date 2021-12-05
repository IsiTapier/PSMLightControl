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
DMXDevice strahler(UNIVERSE_2, 19, MRGBWSE, 1, UNIVERSE_1, 19, MRGB, 7);
DMXDevice strahlerNeu(UNIVERSE_2, 68, RGBW, 1, UNIVERSE_1, 68, RGBW, 2);
DMXDevice bars(UNIVERSE_2, 150, RGB, 12, UNIVERSE_1, 149, MRGB, 9);
DMXDevice barsSide(UNIVERSE_2, 481, RGB, 1, UNIVERSE_1, 101, MRGB);
DMXDevice blinder[3] = {
  DMXDevice(UNIVERSE_2, 76, M, 10, UNIVERSE_1, 474, M, 2),
  DMXDevice(UNIVERSE_2, 139, M, 10, UNIVERSE_1, 474, M, 1),
  DMXDevice(UNIVERSE_2, 484, M, 10, UNIVERSE_1, 474, M, 1)
};
#endif
// DMXDevice movingHeads(UNIVERSE_3, 1, PTsZMEwcCXXXX, 1, UNIVERSE_1, 508, ZMC, 2);

#if UNIVERSE_3_ACTIVE && UNIVERSE_1_ACTIVE
#include "MovingHead.h"
DMXDevice strahlerNeu2(UNIVERSE_3, 68, RGBW, 1, UNIVERSE_1, 68, RGBW, 2);
#endif

void setup() {
  #if DEBUG
    Serial.begin(115200);
  #endif
  ui.init();
  //  universe1 = DMX::initUniverse(UNIVERSE_1, input, U1_IN, U1_OUT, U1_EN);
  // universe2 = DMX::initUniverse(UNIVERSE_2, output, U2_IN, U2_OUT, U2_EN);
 // universe3 = DMX::initUniverse(UNIVERSE_3, output, U3_IN, U3_OUT, U3_EN);

  //universe2->write(21, 255);
  //universe2->write(27, 255);
//  universe1->write(0, 255);
#if UNIVERSE_3_ACTIVE
  MovingHead::init(1);
#endif
// DMXDevice::init();
}

void loop() {
  //digitalWrite(U1_EN, LOW);
  //Serial.print(universe1->isHealthy());
  vTaskDelay(1000/portTICK_PERIOD_MS);
  #if UNIVERSE_1_ACTIVE
   if (millis() - readcycle > 500) {
        readcycle = millis();
        //.writeBlue(255);
      //  Serial.print(readcycle);
  //  Serial.print(MovingHead::getMovingHead(0)->getX()); Serial.print(" ");
  //  Serial.print(MovingHead::getMovingHead(0)->getY()); Serial.print(" ");
  //  Serial.print(MovingHead::getMovingHead(1)->getX()); Serial.print(" ");
  //  Serial.print(MovingHead::getMovingHead(1)->getY()); Serial.println(" ");
        if(universe1->isHealthy()) {
            /*for(int i = 0; i < 513; i++) {
               // universe3->write(i, universe1->read(i));
            }*/
#if DEBUG && UNIVERSE_2_ACTIVE
            // Serial.print(universe2->read(20)); Serial.print(" ");
            // Serial.print(universe2->read(21)); Serial.print(" ");
            // Serial.print(universe2->read(22)); Serial.print(" ");
            // Serial.print(universe2->read(23)); Serial.print(" ");
            // Serial.print(universe2->read(24)); Serial.print(" ");
            // Serial.print(universe2->read(25)); Serial.print(" ");
            // Serial.print(universe2->read(26)); Serial.print(" ");
            // Serial.print(universe2->read(27)); Serial.println(" ");
#endif
#if DEBUG && UNIVERSE_3_ACTIVE
            /*Serial.print(universe3->read(1)); Serial.print(" ");
            Serial.print(universe3->read(2)); Serial.print(" ");
           /* Serial.print(universe3->read(4)); Serial.print(" ");
            Serial.print(universe3->read(5)); Serial.print(" ");
            Serial.print(universe3->read(6)); Serial.print(" ");
            Serial.print(universe3->read(7)); Serial.print(" ");
            Serial.print(universe3->read(8)); Serial.print(" ");
            Serial.print(universe3->read(9)); Serial.print("\t\t");*/
         /*   Serial.print(universe3->read(14)); Serial.print(" ");
            Serial.print(universe3->read(15)); Serial.println(" ");
           /* Serial.print(universe3->read(17)); Serial.print(" ");
            Serial.print(universe3->read(18)); Serial.print(" ");
            Serial.print(universe3->read(19)); Serial.print(" ");
            Serial.print(universe3->read(20)); Serial.print(" ");
            Serial.print(universe3->read(21)); Serial.print(" ");
            Serial.print(universe3->read(22)); Serial.println(" ");*/
#endif
            
        //  Serial.print(": ok - ");
        // Serial.print(universe3->read(1)); Serial.print(" ");
        // Serial.print(universe3->read(2)); Serial.print(" ");
        // Serial.print(universe3->read(3)); Serial.print(" ");
        // Serial.print(universe3->read(4)); Serial.print(" ");
        // Serial.print(universe3->read(5)); Serial.print(" ");
        // Serial.print(universe3->read(6)); Serial.print(" ");
        // Serial.print(universe3->read(7)); Serial.print(" ");
        // Serial.print(universe3->read(8)); Serial.print(" ");
        // Serial.print(universe3->read(9)); Serial.print(" ");
        // Serial.print(universe3->read(10)); Serial.print(" ");
        // Serial.print(universe3->read(11)); Serial.print(" ");
        // Serial.print(universe3->read(12)); Serial.print(" ");
        // Serial.print(universe3->read(13)); Serial.print(" ");
        // Serial.print(universe3->read(14)); Serial.print(" ");
        // Serial.print(universe3->read(15)); Serial.println(" ");
        } else {
        //  Serial.print(": fail - ");
        }

        /*Serial.print(universe1.read(1));
        Serial.print(" - ");
        Serial.print(universe1.read(110));
        Serial.print(" - ");
        Serial.println(universe1.read(256));*/
        /*for(int i = 1; i<=512; i++) {
        DMX::read(21
        }*/
        //universe2->write(21, 255);
      //  universe2->write(27, 255);
  }
  #endif
    /*
    Serial.print(analogRead(36));Serial.print("\t");
    Serial.print(analogRead(39));Serial.print("\t");
    Serial.print(analogRead(35));Serial.print("\t");
    Serial.println();*/
}
