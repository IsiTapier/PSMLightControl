#ifndef SCENEUI_H
#define SCENEUI_H

#include "Arduino.h"
#include "../../customView/CustomView.h"
#include "../../button/Button.h"
#include "../../textField/Text.h"
#include "vector"
#include "array"
#include "EEPROM.h"
#include "Scene/Scene.h"

Container scenes(ContainerProperties(Size(480-24), Size(320-90-64), Spacing(Size(12), Size(12), Size(12), Size(0)), Spacing(5), 0, 0, true), {});

bool deletescene = false;

SceneData sceneData;

void storeScenes() {
    EEPROM.put(sizeof(PresetData), sceneData);
    EEPROM.commit();
}

void addSceneButton() {
    scenes.addContent(
        new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), 
            // touch event
            std::bind([](byte id, short buttonId) {
                for(int i = 1; i < sceneData.currentPosition; i++) {
                    if(sceneData.scenes[i].id==id) {
                        if(deletescene) {
                            deletescene = false;
                            scenes.removeContent(id);
                            ButtonManager::removeButton(buttonId);
                            if(sceneData.currentPosition > 0) sceneData.currentPosition--;
                            for(int j = i; j < sceneData.currentPosition; j++) {
                                sceneData.scenes[j] = sceneData.scenes[j+1];
                            }
                            storeScenes();
                            // delete newButton;
                        } else {
                            sceneData.scenes[i].scene.activate();
                        }
                    }
                }
                return 0;
            }, (scenes.getProperties().getCurrentId()+1), ButtonManager::getCurrentId()+1),
            // content
            {new Text(ContainerProperties(), TextProperties(), "scene "+String((scenes.getProperties().getCurrentId()+2)))}
        )
    );
}

void readScenes() {
    // for (int i = 0; i < 512; i++) {
    //     EEPROM.write(i, 0);
    // }
    // EEPROM.commit();
    EEPROM.get(sizeof(PresetData), sceneData);
    if(sceneData.currentPosition>20)
        sceneData.currentPosition = 20;
    for(int i = 1; i < sceneData.currentPosition; i++) {
        sceneData.scenes[i].id=(scenes.getProperties().getCurrentId()+1);
        addSceneButton();
    }
    storeScenes();
}

View sceneView(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties("scenes"),
    // content
    {
    // new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(),
    //     [](){ViewManager::setCurrentView(0); deletescene=false; return 0;},
    //     {new Text(ContainerProperties(), TextProperties(), "B"+ue+"hne")}),

    &scenes
    },
    // navbar
    {
    new Button(ContainerProperties(Size(70), Size(60), Spacing(27, 8, 8, 8), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_DARKGREEN), ButtonProperties(),
        [](){
            if(sceneData.currentPosition<20)
                sceneData.scenes[sceneData.currentPosition] = {(byte)((scenes.getProperties().getCurrentId()+1)), Scene()};
            sceneData.currentPosition++;
            addSceneButton();
            storeScenes();
            deletescene = false;
            return 0;
        },
        {new Text(ContainerProperties(), TextProperties(NO_COLOR, 3), "add")}
    ),

    new Button(ContainerProperties(Size(70), Size(60), Spacing(8), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_RED), ButtonProperties(),
        [](){if(scenes.getContentAmount()>0) deletescene=true; return 0;},
        {new Text(ContainerProperties(), TextProperties(), "delete")}),
    }
);


#endif