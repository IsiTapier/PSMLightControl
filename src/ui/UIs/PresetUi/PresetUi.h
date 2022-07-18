/*
  PresetUi.h - PresetUi-Library for Airduino.
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
#include <algorithm>
#include <iostream>
#include "Preset.h"

Container presets(ContainerProperties(Size(480-24), Size(320-90-64), Spacing(Size(12), Size(12), Size(12), Size(0)), Spacing(5), 0, 0, true), {});

PresetData presetData;

bool deletePreset = false;

void storePresets() {
    EEPROM.put(0, presetData);
    EEPROM.commit();
}

void addPresetButton() {
    presets.addContent(
        new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), 
            // touch event
            std::bind([](byte id, short buttonId) {
                for(int i = 1; i < presetData.currentPosition; i++) {
                    if(presetData.presetObjs[i].id==id) {
                        if(deletePreset) {
                            deletePreset = false;
                            presets.removeContent(id-1);
                            ButtonManager::removeButton(buttonId);
                            if(presetData.currentPosition > 0) presetData.currentPosition--;
                            for(int j = i; j < presetData.currentPosition; j++) {
                                presetData.presetObjs[j] = presetData.presetObjs[j+1];
                            }
                            storePresets();
                            // delete newButton;
                        } else {
                            presetData.presetObjs[i].preset.activate();
                        }
                    }
                }
                return 0;
            }, (presets.getProperties().getCurrentId()+2), ButtonManager::getCurrentId()+1),
            // content
            {new Text(ContainerProperties(), TextProperties(), "preset "+String((presets.getProperties().getCurrentId()+2)))}
        )
    );
}

void readPresets() {
    // for (int i = 0; i < 512; i++) {
    //     EEPROM.write(i, 0);
    // }
    // EEPROM.commit();
    PresetData temp;
    if(EEPROM.get(0, temp).currentPosition == 0) storePresets();
    EEPROM.get(0, presetData);
    for(int i=0;i<MOVING_HEADS_AMOUNT;i++) MovingHead::getMovingHead(i)->setHome(presetData.presetObjs[0].preset.getPositions()[i]);
    MovingHead::setHomeAll(presetData.presetObjs[0].preset.getPositionAll());
    MovingHead::resetPositions();
    if(presetData.currentPosition == 1)
        return;
    if(presetData.currentPosition>=20)
        presetData.currentPosition = 19;
    for(int i = 1; i < presetData.currentPosition; i++) {
        presetData.presetObjs[i].id=(presets.getProperties().getCurrentId()+2);
        addPresetButton();
    }
    storePresets();
}

View presetView(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties("Presets"),
    // content
    {

    // new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(),
    //     [](){ViewManager::setCurrentView(0); deletePreset=false; return 0;},
    //     {new Text(ContainerProperties(), TextProperties(), "B"+ue+"hne")}),

    &presets
    },
    // navbar
    {
    new Button(ContainerProperties(Size(58), Size(60), Spacing(4,8), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_DARKGREEN), ButtonProperties(),
        [](){
            if(presetData.currentPosition<19)
                presetData.presetObjs[presetData.currentPosition] = {(byte)((presets.getProperties().getCurrentId()+2)), Preset()};
            presetData.currentPosition++;
            addPresetButton();
            storePresets();
            deletePreset = false;
            return 0;
        },
        {new Text(ContainerProperties(), TextProperties(NO_COLOR, 3), "add")}
    ),

    new Button(ContainerProperties(Size(58), Size(60), Spacing(4,8), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_RED), ButtonProperties(),
        [](){if(presets.getContentAmount()>0) deletePreset=true; return 0;},
        {new Text(ContainerProperties(), TextProperties(), "delete")}),

    new Button(ContainerProperties(Size(58), Size(60), Spacing(4,8), Spacing(2), Size(2), Size(4)), ButtonProperties(),
        [](){
            presetData.presetObjs[0].preset = Preset();
            for(int i=0;i<MOVING_HEADS_AMOUNT;i++)
                MovingHead::getMovingHead(i)->setHome(presetData.presetObjs[0].preset.getPositions()[i]);
            MovingHead::setHomeAll(presetData.presetObjs[0].preset.getPositionAll());
            storePresets();
            return 0;
        },
        {new Text(ContainerProperties(), TextProperties(), "set home")}),
    }
);

#endif