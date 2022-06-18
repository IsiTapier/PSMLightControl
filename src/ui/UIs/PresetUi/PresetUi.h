/*
  MovingHeadUi.h - MovingHeadUi-Library for Airduino.
*/

#ifndef PrestUi_h
#define PresetUi_h

#include "Arduino.h"
#include "../../customView/CustomView.h"
#include "../../button/Button.h"
#include "../../textField/Text.h"
#include "Position.h"
#include "MovingHead.h"
#include "vector"
#include "array"
#include "functional"
#include "EEPROM.h"

std::array<Position, MOVING_HEADS_AMOUNT+1> getDefaultPositions() {
    std::array<Position, MOVING_HEADS_AMOUNT+1> defaultPositions;
    std::fill(defaultPositions.begin(), std::prev(defaultPositions.end()), Position(X_DEFAULT, Y_DEFAULT));
    return defaultPositions;
}
std::vector<std::array<Position, MOVING_HEADS_AMOUNT+1>> presetPositions = {getDefaultPositions()};

Container presets(ContainerProperties(Size(480-24), Size(320-90), Spacing(Size(12), Size(12), Size(0), Size(0)), Spacing(5), 0, 0, true), {});

struct EepromPosition {
    byte id;
    std::array<Position, MOVING_HEADS_AMOUNT+1> positions;
};

struct EepromData {
    byte currentPosition = 1;
    EepromPosition eepromPositions[20] = {{0, getDefaultPositions()}};
} eepromData;

bool deletePreset = false;

void storeEeprom() {
    EEPROM.put(0, eepromData);
    EEPROM.commit();
}

void addPresetButton() {
    presets.addContent(
        new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), 
            // touch event
            std::bind([](byte id, short buttonId) {
                if(deletePreset) {
                    deletePreset = false;
                    presets.removeContent(id-1);
                    ButtonManager::removeButton(buttonId);
                    for(int i = 1; i < eepromData.currentPosition; i++) {
                        if(eepromData.eepromPositions[i].id==id) {
                            if(eepromData.currentPosition > 0) eepromData.currentPosition--;
                            for(int j = i; j < eepromData.currentPosition; j++) {
                                eepromData.eepromPositions[j] = eepromData.eepromPositions[j+1];
                            }
                        }
                    }
                    storeEeprom();
                } else {
                    for(int i = 0; i < MOVING_HEADS_AMOUNT; i++) 
                        MovingHead::getMovingHead(i)->setPosition(presetPositions[id][i]);
                    MovingHead::setPositionAll(presetPositions[id][MOVING_HEADS_AMOUNT]);
                }
                return 0;
            }, (presets.getPorperties().getCurrentId()+2)%256, ButtonManager::getCurrentId()+1),
            // content
            {new Text(ContainerProperties(), TextProperties(), "preset "+String((presets.getPorperties().getCurrentId()+2)%256))}
        )
    );
}

void readEeprom() {
    // for (int i = 0; i < 512; i++) {
    //     EEPROM.write(i, 0);
    // }
    // EEPROM.commit();
    EepromData temp;
    if(EEPROM.get(0, temp).currentPosition == 0) storeEeprom();
    EEPROM.get(0, eepromData);
    for(Position p : eepromData.eepromPositions[0].positions)
        if(p.getX()!=0||p.getY()!=0) {
            presetPositions.at(0) = eepromData.eepromPositions[0].positions;
            break;
        }
    for(int i=0;i<MOVING_HEADS_AMOUNT;i++) MovingHead::getMovingHead(i)->setHome(presetPositions[0][i]);
    MovingHead::setHomeAll(presetPositions[0][MOVING_HEADS_AMOUNT]);
    MovingHead::resetPositions();
    if(eepromData.currentPosition == 1)
        return;
    if(eepromData.currentPosition>=20)
        eepromData.currentPosition = 19;
    for(int i = 1; i < eepromData.currentPosition; i++) {
        presetPositions.push_back(eepromData.eepromPositions[i].positions);
        eepromData.eepromPositions[i].id=(presets.getPorperties().getCurrentId()+2)%256;
        addPresetButton();
    }
    storeEeprom();
}
#include <algorithm>
#include <iostream>

View presetView(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {
    new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(),
        [](){ViewManager::setCurrentView(0); deletePreset=false; return 0;},
        {new Text(ContainerProperties(), TextProperties(), "B"+ue+"hne")}),

    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_DARKGREEN), ButtonProperties(),
        [](){
            std::array<Position, MOVING_HEADS_AMOUNT+1> p;
            // std::for_each(p.begin(), std::prev(p.end()), [i=0](Position& n)mutable{
            //     n = MovingHead::getMovingHead(i++)->getPosition();
            // });
            int i = 0;
            for(Position position : p) {
                position = MovingHead::getMovingHead(i++)->getPosition();
            }
            p.at(MOVING_HEADS_AMOUNT) = MovingHead::getPositionAll();
            presetPositions.push_back(p);
            if(eepromData.currentPosition<19)
                eepromData.eepromPositions[eepromData.currentPosition] = {(byte)((presets.getPorperties().getCurrentId()+2)%256), p};
            eepromData.currentPosition++;
            addPresetButton();
            storeEeprom();
            deletePreset = false;
            return 0;
        },
        {new Text(ContainerProperties(), TextProperties(NO_COLOR, 3), "add")}
    ),

    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_RED), ButtonProperties(),
        [](){if(presets.getContentAmount()>0) deletePreset=true; return 0;},
        {new Text(ContainerProperties(), TextProperties(), "delete")}),

    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4)), ButtonProperties(),
        [](){
            for(int i=0;i<MOVING_HEADS_AMOUNT;i++) {
                presetPositions[0][i] = MovingHead::getMovingHead(i)->getPosition();
                MovingHead::getMovingHead(i)->setHome(presetPositions[0][i]);
            }
            presetPositions[0][MOVING_HEADS_AMOUNT] = MovingHead::getPositionAll();
            MovingHead::setHomeAll(presetPositions[0][MOVING_HEADS_AMOUNT]);
            eepromData.eepromPositions[0] = { 0, presetPositions[0]};
            storeEeprom();
            return 0;
        },
        {new Text(ContainerProperties(), TextProperties(), "set home")}),

    &presets}
);

#endif