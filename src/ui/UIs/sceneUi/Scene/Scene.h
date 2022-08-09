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
        Scene(Color barsColor, Color spotColor, Preset preset, bool includeMovings);
        void activate();
        static void setIncludeMHs(bool value = !includeMHs);
        static bool getIncludeMhs();
    
    private:
        Color barsColor;
        Color spotColor;
        Preset preset;
        // std::array<byte, MOVING_HEADS_AMOUNT> mhBrightnesses;
        // std::array<byte, MOVING_HEADS_AMOUNT> mhZooms;
        bool includeMovings;
        // std::array<bool, 12> effects;

        static bool includeMHs;   
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