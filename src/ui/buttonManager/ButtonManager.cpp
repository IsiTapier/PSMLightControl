/*
 ButtonManager.cpp - ButtonManager-Library for Librarys.
*/

#include "ButtonManager.h"

std::vector<Button*> ButtonManager::buttons;

void ButtonManager::init() {
  calibrateTouch();
  xTaskCreate(checkTouch, "check touch", 2048, NULL, 6, NULL);
}

void ButtonManager::addButton(Button* button) {
  buttons.push_back(button);
}

void ButtonManager::checkTouch(void*) {
  TSPoint p;
  byte nearestDistance;
  std::vector<Button*> nearestButton;
  for(;;) {
    vTaskDelay(TOUCH_CYCLE/portTICK_PERIOD_MS);
    p = display.getTouch();
    nearestDistance = UINT8_MAX;
    nearestButton.clear();
    for(Button* button : buttons) {
      if(button->getPorperties().getViewId()!=ViewManager::getCurrentView())
        continue;
      if(p.x == UINT16_MAX || p.y == UINT16_MAX) {
        button->untrigger();
        continue;
      }
      byte distance = button->checkTouch(p);

      if(distance == UINT8_MAX)
        continue;
      if(nearestDistance > distance) {
        nearestDistance = distance;
        nearestButton.clear();
        nearestButton.push_back(button);
      } else if(nearestDistance == distance)
        nearestButton.push_back(button);
    }
    for(Button* button : buttons) {
      if(button->getPorperties().getViewId()!=ViewManager::getCurrentView())
        continue;
      if(std::find(nearestButton.begin(), nearestButton.end(), button) != nearestButton.end())
        button->trigger();
      else
        button->untrigger();
    }
  }
}

void ButtonManager::calibrateTouch() {
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
    if (REPEAT_CAL) {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    } else {
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
    display.setTouch(calData);
  } else {
    // data not valid so recalibrate
    display.fillScreen(TFT_BLACK);
    display.setCursor(20, 0);
    display.setTextFont(2);
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE, TFT_BLACK);

    display.println("Touch corners as indicated");

    display.setTextFont(1);
    display.println();

    if (REPEAT_CAL) {
      display.setTextColor(TFT_RED, TFT_BLACK);
      display.println("Set REPEAT_CAL to false to stop this running again!");
    }

    display.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    display.setTextColor(TFT_GREEN, TFT_BLACK);
    display.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}