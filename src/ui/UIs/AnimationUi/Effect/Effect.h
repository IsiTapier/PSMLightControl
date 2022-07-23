/*
  Effect.h - Effect-Library for Airduino.
*/

#ifndef Effecth
#define Effecth

#include "../../dmxDevice/DMXDevice.h"
#include "../../../button/Button.h"
#include "../../../textField/Text.h"

#define EQUAL_SPREAD UINT8_MAX

class Effect {
    public:
        enum Direction {
            LEFT = 0,
            RIGHT = 1,
            OUT = 2,
            IN = 3,
            UP = 1,
            DOWN = 0, 
        };
        Effect(const char* name, DMXDevice* device, short speed, float increase = 1, byte spreadLeft = 0, byte spreadRight = EQUAL_SPREAD, Direction direction = RIGHT, byte overrideValue = 255, bool doOverlap = true);
        void toggle();
        bool getActive();
        DMXDevice* getDevice();
        static void addEffect(Effect* effect);
        static std::vector<Effect*> getEffects();

    private:
        static std::vector<Effect*> effects;
        bool active = false;
        TaskHandle_t handle = NULL;
        const char* name;

        struct Parameter {
            Parameter(DMXDevice* device, short speed, float increase, byte spreadLeft, byte spreadRight, Direction direction, byte overrideValue, bool doOverlap) : device(device), speed(speed), increase(increase), spreadLeft(spreadLeft), spreadRight(spreadRight==EQUAL_SPREAD?spreadLeft:spreadRight), direction(direction), overrideValue(overrideValue), doOverlap(doOverlap) {}
            DMXDevice* device;
            short speed;
            float increase;
            byte spreadLeft;
            byte spreadRight;
            Direction direction;
            byte overrideValue;
            bool doOverlap;
        } parameter;
};

class MultiEffect {
    public:
        struct EffectPoint {
            EffectPoint(byte startX, byte endX, float increase, byte currentX, byte spreadLeft = 0, byte spreadRight = EQUAL_SPREAD) : startX(startX), endX(endX), increase(increase), currentX(currentX), spreadLeft(spreadLeft), spreadRight(spreadRight==EQUAL_SPREAD?spreadLeft:spreadRight) {}
            byte startX;
            byte endX;
            float increase;
            byte currentX;
            byte spreadLeft;
            byte spreadRight;

            void next() {
                currentX += increase;
                if(currentX > endX) currentX = startX;
            }

            float getPercentage(bool doOverlap, byte x) {
                float distance = x-currentX;

                if(distance == 0) return 1;
                    
                // check overlap
                if(doOverlap) {
                    if(distance <= -endX+spreadRight) SETABSOLUTESMALLER(distance, distance+endX);
                    if(distance >=  endX-spreadLeft)  SETABSOLUTESMALLER(distance, distance-endX);
                    // if(distance <= -endX+spreadRight) distance = ABSOLUTESMALLER(distance, distance+(direction==OUT || direction==IN ? endX/2 : endX));
                    // if(distance >=  endX-spreadLeft)  distance = ABSOLUTESMALLER(distance, distance-(direction==OUT || direction==IN ? endX/2 : endX));
                }

                // prevent false spread
                if(distance < -spreadLeft) return 0;
                if(distance > spreadRight) return 0;
                // if(x>devices && ((direction == IN && distance < 0) || (direction == OUT && distance > 0))) return value;
                // if(abs(distance) > spread) return value;

                // calculate new brightness
                float percentage = 1-(distance<0 ? abs(distance/spreadLeft) : distance/spreadRight);
                return percentage;
            }
        };
        MultiEffect(const char* name, DMXDevice* device, short speed, std::vector<EffectPoint*> effectPoints, byte overrideValue = 255, bool doOverlap = true);
        void toggle();
        bool getActive();
        DMXDevice* getDevice();
        static std::vector<MultiEffect*> getEffects();

    private:
        static std::vector<MultiEffect*> meffects;
        bool active = false;
        TaskHandle_t handle;
        const char* name;

        struct MParameter {
            MParameter(DMXDevice* device, short speed, std::vector<EffectPoint*> effectPoints, byte overrideValue, bool doOverlap) : device(device), speed(speed), effectPoints(effectPoints), overrideValue(overrideValue), doOverlap(doOverlap) {}
            DMXDevice* device;
            short speed;
            std::vector<EffectPoint*> effectPoints;
            byte overrideValue;
            bool doOverlap;
        } mparameter;
};

class EffectButton: public Button {
    public:
        EffectButton(const char* name, std::vector<DMXDevice*> devices, short speed, float increase = 1, byte spreadLeft = 0, byte spreadRight = EQUAL_SPREAD, Effect::Direction direction = Effect::RIGHT, byte overrideValue = 255, bool doOverlap = true);
        void toggle();

    private:
        const char* name;
        std::vector<Effect*> effects;
};

#endif