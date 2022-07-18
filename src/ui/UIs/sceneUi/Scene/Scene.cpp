#include "Scene.h"

Scene::Scene() : barsColor(bars.getColor()), spotColor(strahler.getColor()), preset(Preset()) {}

Scene::Scene(Color barsColor, Color spotColor, Preset preset) : barsColor(barsColor), spotColor(spotColor), preset(preset) {}

void Scene::activate() {
    // Moving Head positions
    for(int i = 0; i < 6; i++)
        MovingHead::setPosition(i, preset.getPosition(i));
    MovingHead::setPositionAll(preset.getPositionAll());

    // light colors
    Color currentBarColor = bars.getColor();
    Color currentSpotColor = strahler.getColor();

    bars.setValueCalculation({
        [currentBarColor, this](byte value){
            return value == currentBarColor.r ? barsColor.r : value;
        },
        [currentBarColor, this](byte value){
            return value == currentBarColor.g ? barsColor.g : value;
        },
        [currentBarColor, this](byte value){
            return value == currentBarColor.b ? barsColor.b : value;
        }
    });
    strahler.setValueCalculation({
        [](byte value){return value;},
        [currentSpotColor, this](byte value){
            return value == currentSpotColor.r ? spotColor.r : value;
        },
        [currentSpotColor, this](byte value){
            return value == currentSpotColor.g ? spotColor.g : value;
        },
        [currentSpotColor, this](byte value){
            return value == currentSpotColor.b ? spotColor.b : value;
        }
    });

    // effects

    // TODO
    
}