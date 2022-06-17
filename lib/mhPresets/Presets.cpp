/*
 Presets.cpp - Presets-Library for Librarys.
*/

#include "Presets.h"

std::function<void()> Presets::_update;
std::vector<std::array<Position, MOVING_HEADS_AMOUNT+1>> Presets::presetPositions = {{Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT)}};


Presets::Presets() {

}

void Presets::setUpdate(std::function<void()> update) {
    _update = update;
}

struct EepromPosition {
    byte id;
    std::array<Position, MOVING_HEADS_AMOUNT+1> positions;
};

struct EepromData {
    byte currentPosition = 1;
    EepromPosition eepromPositions[20];
} eepromData;

void Presets::storeEeprom() {
    EEPROM.put(0, eepromData);
    EEPROM.commit();
}

void Presets::readEeprom() {
    // for (int i = 0; i < 512; i++) {
    //     EEPROM.write(i, 0);
    // }
    // EEPROM.commit();   
    eepromData = EEPROM.get(0, eepromData);
    //TODO empty check
    for(Position p:eepromData.eepromPositions[0].positions)
        if(p.getX()!=0||p.getY()!=0) {
            presetPositions.at(0) = eepromData.eepromPositions[0].positions;
            break;
        }
    // for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[0][i]);MovingHead::setPositionAll(presetPositions[0][MOVING_HEADS_AMOUNT]);updateBuehne(0, 0, true);
    // if(eepromData.currentPosition == 1)
    //     return;
    // if(eepromData.currentPosition>=20)
    //     eepromData.currentPosition = 19;
    // for(int i = 1; i < eepromData.currentPosition; i++) {
    //     presetPositions.push_back(eepromData.eepromPositions[i].positions);
    //     presets.addContent(new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), std::bind([](byte id, short buttonId){if(deletePreset){deletePreset=false;presets.removeContent(id-1);ButtonManager::removeButton(buttonId);for(int i = 0; i < eepromData.currentPosition; i++){if(eepromData.eepromPositions[i].id==id){if(eepromData.currentPosition>0)eepromData.currentPosition--;for(int j = i; j < eepromData.currentPosition; j++){eepromData.eepromPositions[j]=eepromData.eepromPositions[j+1];Serial.print("move");Serial.println(j);};storeEeprom();}}}else{for(int i = 0; i < MOVING_HEADS_AMOUNT; i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[id][i]);MovingHead::setPositionAll(presetPositions[id][MOVING_HEADS_AMOUNT]);}return 0;}, presets.getPorperties().getCurrentId()+2, ButtonManager::getCurrentId()+1), {new Text(ContainerProperties(), TextProperties(), "preset "+String((presets.getPorperties().getCurrentId()+2)%256))}));
    //     eepromData.eepromPositions[i].id=presets.getPorperties().getCurrentId()+1;
    // }
    // storeEeprom();
}