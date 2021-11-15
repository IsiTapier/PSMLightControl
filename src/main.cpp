#include <Arduino.h>
#include "dmx.h"
#include "DMXDevice.h"
#include "ui/Ui.h"

Ui ui;

/*
  The TFT_eSPI library incorporates an Adafruit_GFX compatible
  button handling class, this sketch is based on the Arduin-o-phone
  example.

  This example diplays a keypad where numbers can be entered and
  send to the Serial Monitor window.

  The sketch has been tested on the ESP8266 (which supports SPIFFS)

  The minimum screen size is 320 x 240 as that is the keypad size.

  TOUCH_CS and SPI_TOUCH_FREQUENCY must be defined in the User_Setup.h file
  for the touch functions to do anything.
*/

// The SPIFFS (FLASH filing system) is used to hold touch screen
// calibration data

//#include "FS.h"
#include "Pins.h"

//#include <SPI.h>
//#include <TFT_eSPI.h>      // Hardware-specific library
/*
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// This is the file name used to store the calibration data
// You can change this to create new calibration files.
// The SPIFFS file name must start with "/".
#define CALIBRATION_FILE "/TouchCalData2"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

// Keypad start position, key sizes and spacing
#define KEY_X 40 // Centre of key
#define KEY_Y 96
#define KEY_W 62 // Width and height
#define KEY_H 30
#define KEY_SPACING_X 18 // X and Y gap
#define KEY_SPACING_Y 20
#define KEY_TEXTSIZE 1   // Font size multiplier

// Using two fonts since numbers are nice when bold
#define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
#define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2

// Numeric display box size and location
#define DISP_X 1
#define DISP_Y 10
#define DISP_W 238
#define DISP_H 50
#define DISP_TSIZE 3
#define DISP_TCOLOR TFT_CYAN

// Number length, buffer for storing it and character index
#define NUM_LEN 12
char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

// We have a status line for messages
#define STATUS_X 120 // Centred on this
#define STATUS_Y 65

// Create 15 keys for the keypad
char keyLabel[15][5] = {"New", "Del", "Send", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "#" };
uint16_t keyColor[15] = {TFT_RED, TFT_DARKGREY, TFT_DARKGREEN,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE
                        };

// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key[15];*/

unsigned long readcycle = 0;

#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 1
DMX* universe1 = DMX::initUniverse(UNIVERSE_1, input, U1_IN, U1_OUT, U1_EN);
#endif
#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 2
 DMX* universe2 = DMX::initUniverse(UNIVERSE_2, output, U2_IN, U2_OUT, U2_EN);
#endif
#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 3
DMX* universe3 = DMX::initUniverse(UNIVERSE_3, output, U3_IN, U3_OUT, U3_EN);
#endif

#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 2 && false
DMXDevice strahler(UNIVERSE_2, 20, MRGBWSE, 1, UNIVERSE_1, 20, MRGBW, 8);
DMXDevice bars(UNIVERSE_2, 150, RGB, 12, UNIVERSE_1, 149, MRGB, 9);
DMXDevice barsSide(UNIVERSE_2, 481, RGB, 1, UNIVERSE_1, 101, MRGB);
DMXDevice blinder[3] = {
  DMXDevice(UNIVERSE_2, 76, M, 10, UNIVERSE_1, 474, M, 2),
  DMXDevice(UNIVERSE_2, 139, M, 10, UNIVERSE_1, 474, M, 1),
  DMXDevice(UNIVERSE_2, 484, M, 10, UNIVERSE_1, 474, M, 1)
};
#endif
//DMXDevice movingHeads(UNIVERSE_3, 1, PTsZMEwcCXXXX, 1, UNIVERSE_1, 508, ZMC, 2);

#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 3
#include "MovingHead.h"
#endif

/*bool activeMovingHead = 0;
float movingHead1X;
float movingHead1Y; 
float movingHead2X;
float movingHead2Y;

void joystickHandle(float x, float y) {
  Serial.print(F("x: ")); Serial.print(x);
  Serial.print(F(" y: ")); Serial.println(y);
}

void joystickButtonHandle() {
  activeMovingHead = !activeMovingHead;
  Serial.println(F("click"));
}

Joystick joystick(X_POS, Y_POS, BUTTON, joystickHandle, joystickButtonHandle);*/
/*
void drawKeypad()
{
  // Draw the keys
  for (uint8_t row = 0; row < 5; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      uint8_t b = col + row * 3;

      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      key[b].initButton(&tft, KEY_X + col * (KEY_W + KEY_SPACING_X),
                        KEY_Y + row * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
                        KEY_W, KEY_H, TFT_WHITE, keyColor[b], TFT_WHITE,
                        keyLabel[b], KEY_TEXTSIZE);
      key[b].drawButton();
    }
  }
}

//------------------------------------------------------------------------------------------

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

//------------------------------------------------------------------------------------------

// Print something in the mini status bar
void status(const char *msg) {
  tft.setTextPadding(240);
  //tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  tft.setTextFont(0);
  tft.setTextDatum(TC_DATUM);
  tft.setTextSize(1);
  tft.drawString(msg, STATUS_X, STATUS_Y);
}*/

//------------------------------------------------------------------------------------------


void setup() {
  #if SERIAL_ACTIVE
    Serial.begin(115200);
  #endif
  ui.init();
  // Use serial port
  //Serial.begin(9600);

  // Initialise the TFT screen
  /*tft.init();

  // Set the rotation before we calibrate
  tft.setRotation(3);

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate();

  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Draw keypad background
  tft.fillRect(0, 0, 240, 320, TFT_DARKGREY);

  // Draw number display area and frame
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  // Draw keypad
  drawKeypad();*/
  //  universe1 = DMX::initUniverse(UNIVERSE_1, input, U1_IN, U1_OUT, U1_EN);
  // universe2 = DMX::initUniverse(UNIVERSE_2, output, U2_IN, U2_OUT, U2_EN);
 // universe3 = DMX::initUniverse(UNIVERSE_3, output, U3_IN, U3_OUT, U3_EN);

  //universe2->write(21, 255);
  //universe2->write(27, 255);
//  universe1->write(0, 255);
#if !SERIAL_ACTIVE || INACTIVE_UNIVERSE != 3
  MovingHead::getMovingHead(0)->init();
  MovingHead::getMovingHead(1)->init();
#endif
}

void loop() {
  //digitalWrite(U1_EN, LOW);
  //Serial.print(universe1->isHealthy());
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
#if SERIAL_ACTIVE && INACTIVE_UNIVERSE != 2
            Serial.print(universe2->read(20)); Serial.print(" ");
            Serial.print(universe2->read(21)); Serial.print(" ");
            Serial.print(universe2->read(22)); Serial.print(" ");
            Serial.print(universe2->read(23)); Serial.print(" ");
            Serial.print(universe2->read(24)); Serial.print(" ");
            Serial.print(universe2->read(25)); Serial.print(" ");
            Serial.print(universe2->read(26)); Serial.print(" ");
            Serial.print(universe2->read(27)); Serial.println(" ");
#endif
#if SERIAL_ACTIVE && INACTIVE_UNIVERSE != 3
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
  }/*
    /*
    Serial.print(analogRead(36));Serial.print("\t");
    Serial.print(analogRead(39));Serial.print("\t");
    Serial.print(analogRead(35));Serial.print("\t");
    Serial.println();*/
/*
    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = tft.getTouch(&t_x, &t_y);

  // / Check if any key coordinate boxes contain the touch coordinates
  for (uint8_t b = 0; b < 15; b++) {
    if (pressed && key[b].contains(t_x, t_y)) {
      key[b].press(true);  // tell the button it is pressed
    } else {
      key[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // Check if any key has changed state
  for (uint8_t b = 0; b < 15; b++) {

    if (b < 3) tft.setFreeFont(LABEL1_FONT);
    else tft.setFreeFont(LABEL2_FONT);

    if (key[b].justReleased()) key[b].drawButton();     // draw normal

    if (key[b].justPressed()) {
      key[b].drawButton(true);  // draw invert

      // if a numberpad button, append the relevant # to the numberBuffer
      if (b >= 3) {
        if (numberIndex < NUM_LEN) {
          numberBuffer[numberIndex] = keyLabel[b][0];
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
        status(""); // Clear the old status
      }

      // Del button, so delete last char
      if (b == 1) {
        numberBuffer[numberIndex] = 0;
        if (numberIndex > 0) {
          numberIndex--;
          numberBuffer[numberIndex] = 0;//' ';
        }
        status(""); // Clear the old status
      }

      if (b == 2) {
        status("Sent value to serial port");
        Serial.println(numberBuffer);
      }
      // we dont really check that the text field makes sense
      // just try to call
      if (b == 0) {
        status("Value cleared");
        numberIndex = 0; // Reset index to 0
        numberBuffer[numberIndex] = 0; // Place null in buffer
      }

      // Update the number display field
      tft.setTextDatum(TL_DATUM);        // Use top left corner as text coord datum
      tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
      tft.setTextColor(DISP_TCOLOR);     // Set the font colour

      // Draw the string, the value returned is the width in pixels
      int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

      // Now cover up the rest of the line up by drawing a black rectangle.  No flicker this way
      // but it will not work witeh italic or oblique fonts due to character overlap.
      tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

      delay(10); // UI debouncing
    }d
  }*/
 
}

#define MIN_VALUE 50
#define PIN 0
#define LED 5
#define DUNKEL if(analogRead(PIN) < MIN_VALUE)
#define AN digitalWrite(LED, 1);
#define AUS digitalWrite(LED, 0);
#define SONST elseS

void loop() {
  DUNKEL
  AN
  SONST
  AUS
}












#define MACH void mach() {\
                DUNKEL\
                  AN\
                SONST\
                  AUS\
              }
#define MACHMACH mach();

void loop() {
  MACHMACH
}

MACH