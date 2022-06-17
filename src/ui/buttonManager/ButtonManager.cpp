/*
 ButtonManager.cpp - ButtonManager-Library for Librarys.
*/

#include "ButtonManager.h"

std::vector<Button*> ButtonManager::buttons = {};
short ButtonManager::currentId = -1;

void ButtonManager::init() {
  calibrateTouch();
  xTaskCreate(checkTouch, "check touch", 1024*8, NULL, 6, NULL);
}

void ButtonManager::addButton(Button* button) {
  currentId++;
  button->setId(currentId);
  buttons.push_back(button);
}

void ButtonManager::removeButton(short id) {
  for(auto it = buttons.begin(); it != buttons.end(); ++it) {
    if((*it)->getId()==id) {
      buttons.erase(it);
      return;
    }
  }
}

void ButtonManager::checkTouch(void*) {
  TSPoint p;
  byte nearestDistance = 0;
  std::vector<Button*> nearestButton;
  for(;;) {
    vTaskDelay(TOUCH_CYCLE/portTICK_PERIOD_MS);
    xSemaphoreTake(sync_display, portMAX_DELAY);
    p = display.getTouch();
    xSemaphoreGive(sync_display);
    bool isTouching = (p.x != (uint16_t)-1 && p.y != (uint16_t)-1);
    for(Button* button : buttons) {
      if(button->getPorperties().getViewId()!=ViewManager::getCurrentView() || !button->getPorperties().getDraw())
        continue;
      if(!isTouching) {
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
    uint16_t delay = 0;
    if(nearestDistance != UINT8_MAX) {
      for(Button* button : buttons) {
        if(button->getPorperties().getViewId()!=ViewManager::getCurrentView() || !button->getPorperties().getDraw())
          continue;
        if(std::find(nearestButton.begin(), nearestButton.end(), button) != nearestButton.end())
          delay = max(delay, button->trigger());
        else
          button->untrigger();
      }
    }
    if(nearestDistance > 5)
      delay = max(delay, ViewManager::getView(ViewManager::getCurrentView())->checkTouch(p));
    if(isTouching) {
      nearestDistance = UINT8_MAX;
      nearestButton.clear();
    }
    vTaskDelay(delay/portTICK_PERIOD_MS);
  }
}

void ButtonManager::calibrateTouch() {
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    if(DEBUG)
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

short ButtonManager::getCurrentId() {
  return currentId;
}