#include "Scene.h"
#include "../../AnimationUi/AnimationUi.h"

std::function<short(byte)> noValueCalculation = [](byte value){return value;};

bool Scene::includeMHs = true;

// std::array<byte, MOVING_HEADS_AMOUNT> getMhBrightnesses() {
//     std::array<byte, MOVING_HEADS_AMOUNT> mhBrightnesses;
//     for(int i = 0; i < MOVING_HEADS_AMOUNT; i++)
//         if(MovingHead::getMovingHead(i) != NULL)
//         mhBrightnesses[i] = MovingHead::getMovingHead(i)->getBrightness();
//     return mhBrightnesses;
// }

// std::array<byte, MOVING_HEADS_AMOUNT> getMhZooms() {
//     std::array<byte, MOVING_HEADS_AMOUNT> mhZooms;
//     for(int i = 0; i < MOVING_HEADS_AMOUNT; i++)
//         if(MovingHead::getMovingHead(i) != NULL)
//         mhZooms[i] = MovingHead::getMovingHead(i)->getZoom();
//     return mhZooms;
// }

// std::array<bool, 12> getEffects() {
//     std::array<bool, 12> effects;
//     // effects[0] = waveLeft->getActive();
//     // effects[1] = waveRight->getActive();
//     // effects[2] = waveOut->getActive();
//     // effects[3] = waveIn->getActive();
//     // effects[4] = schwabbel->getActive();
//     // effects[5] = rainbow->getActive();
//     // effects[5] = lauf->getActive();
//     // effects[6] = dimm->getActive();
//     // effects[7] = wave->getActive();
//     // effects[8] = streifenDown->getActive();
//     // effects[9] = streifenUp->getActive();
//     // effects[10] = stars->getActive();
//     // effects[11] = MovingHead::getDriveRandomAll();
//     return effects;
// }

Scene::Scene() : barsColor(bars.getColor()), spotColor(strahler.getColor()), preset(Preset()), includeMovings(includeMHs) {
    // mhBrightnesses = getMhBrightnesses();
}

Scene::Scene(Color barsColor, Color spotColor, Preset preset, bool includeMovings) : barsColor(barsColor), spotColor(spotColor), preset(preset), includeMovings(includeMovings) {}

void Scene::setIncludeMHs(bool value) {
    includeMHs = value;
}

bool Scene::getIncludeMhs() {
    return includeMHs;
}

void Scene::activate() {
    if(includeMovings) {
        // Moving Head positions
        for(int i = 0; i < 6; i++) {
            MovingHead::setPosition(i, preset.getPosition(i));
            // byte currentBrightness = MovingHead::getMovingHead(i)->getBrightness();
            // byte currentZoom = MovingHead::getMovingHead(i)->getZoom();
            // MovingHead::getMovingHead(i)->getDevice()->setValueCalculation({
            //     noValueCalculation,
            //     noValueCalculation,
            //     noValueCalculation,
            //     [currentZoom, this, i](byte value){
            //         if(abs(value-currentZoom) > 10) return (short) -1;
            //         return (short) (value == currentZoom ? mhZooms[i] : value);
            //     },
            //     [currentBrightness, this, i](byte value){
            //         if(abs(value-currentBrightness) > 10) return (short) -1;
            //         return (short) (value == currentBrightness ? mhBrightnesses[i] : value);
            //     },
            // });
        }
        MovingHead::setPositionAll(preset.getPositionAll());
    }

    

    // light colors
    Color currentBarColor = bars.getColor();
    Color currentSpotColor = strahler.getColor();

    bars.setValueCalculation({
        [currentBarColor, this](byte value){
            if(abs(value-currentBarColor.r) > 10) return (short) -1;
            return (short) (value == currentBarColor.r ? barsColor.r : value);
        },
        [currentBarColor, this](byte value){
            if(abs(value-currentBarColor.g) > 10) return (short) -1;
            return (short) (value == currentBarColor.g ? barsColor.g : value);
        },
        [currentBarColor, this](byte value){
            if(abs(value-currentBarColor.b) > 10) return (short) -1;
            return (short) (value == currentBarColor.b ? barsColor.b : value);
        }
    });
    strahler.setValueCalculation({
        noValueCalculation,
        [currentSpotColor, this](byte value){
            if(abs(value-currentSpotColor.r) > 10) return (short) -1;
            return (short) (value == currentSpotColor.r ? spotColor.r : value);
        },
        [currentSpotColor, this](byte value){
            if(abs(value-currentSpotColor.g) > 10) return (short) -1;
            return (short) (value == currentSpotColor.g ? spotColor.g : value);
        },
        [currentSpotColor, this](byte value){
            if(abs(value-currentSpotColor.b) > 10) return (short) -1;
            return (short) (value == currentSpotColor.b ? spotColor.b : value);
        }
    });

    // effects

    // TODO
    
}