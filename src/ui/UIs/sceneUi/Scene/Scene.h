#ifndef SCENE_H
#define SCENE_H

#include "Position.h"
#include "Arduino.h"
#include "Preset.h"
#include "Devices.h"
#include "EEPROM.h"

class Scene {
    public: 
        Scene();
        Scene(Color barsColor, Color spotColor, Preset preset);
        void activate();
    
    private:
        Color barsColor;
        Color spotColor;
        Preset preset;
    

    // Scene();
    // Scene(SceneData sceneData);

    // void getSceeneData();
};

struct sceneObj {
    byte id;
    Scene scene;
};

struct SceneData {
    byte currentPosition = 0;
    sceneObj scenes[20] = {};
};

#endif