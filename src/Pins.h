/*
  Pins.h - Pins-Library for Airduino.
*/

#ifndef Pins_h
#define Pins_h

#include "Arduino.h"

//Display
#define SCLK        GPIO_NUM_22
#define MISO        GPIO_NUM_15
#define MOSI        GPIO_NUM_23
#define CS          GPIO_NUM_2
#define BL          GPIO_NUM_4
#define RST         -1
#define DC          GPIO_NUM_16
#define T_CS        GPIO_NUM_17

//LED
#define LED_RED     GPIO_NUM_21
#define LED_GREEN   GPIO_NUM_19
#define LED_BLUE    GPIO_NUM_18

//Joystick
#define X_POS       GPIO_NUM_39
#define Y_POS       GPIO_NUM_36
#define BUTTON      GPIO_NUM_32

//DMX
#define UNUSED      GPIO_NUM_5
#define U1_IN       GPIO_NUM_13
#define U1_OUT      UNUSED
#define U1_EN       GPIO_NUM_14
#define U2_IN       UNUSED
#define U2_OUT      GPIO_NUM_26
#define U2_EN       GPIO_NUM_25
#define U3_IN       UNUSED
#define U3_OUT  	  GPIO_NUM_27
#define U3_EN       GPIO_NUM_33


#endif
