/*
  AnimationUi.h - AnimationUi-Library for Airduino.
*/

#ifndef AnimationUi_h
#define AnimationUi_h

#include "../../view/View.h"
#include "Devices.h"
#include "Effect/Effect.h"
#include "MovingHead.h"

MultiEffect bubbles("bubbles", {&bars}, 250, {new MultiEffect::EffectPoint((byte)0, 108, (float).2, (byte)40, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float)-.4, (byte)100, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).1, (byte)80), new MultiEffect::EffectPoint((byte)0, 108, (float)-.7, (byte)10, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).1, (byte)40, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).5, (byte)120, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float)-.2, (byte)60, 5, 5)}, 2);
MultiEffect lauflicht("lauf", &strahler, 250, {new MultiEffect::EffectPoint(0, 56, 1., 0)});
MultiEffect waveOuts("out", &bars, 250, {new MultiEffect::EffectPoint(0, 108/2, -1., 0, 0, 108/4), new MultiEffect::EffectPoint(108/2, 108, 1., 108/2, 108/4, 0)});

unsigned long lastTab = 0;
unsigned long lastBlink = 0;

EffectButton* waveLeft = new EffectButton("wave L", {&bars}, 20, .5, 0, 54, Effect::LEFT);
EffectButton* waveRight = new EffectButton("wave R", {&bars}, 40, 1., 54, 0, Effect::RIGHT);
EffectButton* waveOut = new EffectButton("wave out", {&bars}, 30, 1., 0, 27, Effect::OUT);
EffectButton* waveIn = new EffectButton("wave in", {&bars}, 30, 1., 27, 0, Effect::IN);
EffectButton* schwabbel = new EffectButton("schwabbel", {&bars}, 20, 1., 36, EQUAL_SPREAD, Effect::OUT);
EffectButton* rainbow = new EffectButton("rainbow", {&bars}, 30, 1., 0, 30, Effect::OUT, 255, true, true);

EffectButton* lauf = new EffectButton("lauf", {&strahler}, 5);
EffectButton* dimm = new EffectButton("dimm", {&strahler}, 5, .1, 2);
EffectButton* wave = new EffectButton("random", {&strahler}, 5, 0, 0, 0, Effect::RIGHT, 255, false, false);

EffectButton* streifenDown = new EffectButton("str down", {&blinder1, &blinder2}, 10, .2, 0, 14, Effect::DOWN);
EffectButton* streifenUp = new EffectButton("str up", {&blinder1, &blinder2}, 10, .2, 14, 0, Effect::UP);
EffectButton* stars = new EffectButton("stars", {&blinder1, &blinder2}, 5, RANDOM, 0, 0, Effect::DOWN);

Button* addTabButton() {
    Button* tabButton = new Button(ContainerProperties(Size(70), Size(70), Spacing(6, 3, 0, 6), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            if(millis()-lastTab < 10*1000) Effect::setSpeed(millis()-lastTab);
            lastTab = millis();
            lastBlink = millis();   
            return 0;
        },
        {
            new Text(ContainerProperties(), TextProperties(), "Tab")
        }
    );

    xTaskCreate([](void* parm){
        Button* tabButton = (Button*) parm;
        for(;;) {
            vTaskDelay(10);
            if(tabButton->getProperties().getViewId()!=ViewManager::getCurrentView() || !tabButton->getProperties().getDraw()) continue;
            if(millis()-lastBlink < Effect::getSpeed()) continue;
            lastBlink = millis();
            tabButton->setProperties(*tabButton->getProperties().setBorderColor(TFT_WHITE));
            tabButton->drawBorder(false, false);
            vTaskDelay(30);
            tabButton->setProperties(*tabButton->getProperties().setBorderColor(TFT_BLACK));
            tabButton->drawBorder(false, false);
        }
    }, "tab animation", 2*1024, tabButton, 4, NULL);
    return tabButton;
}

View animationUi(ContainerProperties(-1, -1), ViewProperties("Animation"),
    // content
    {
        new EffectGroup("Bars", {0.5, 1., 2.}, {
            // waveLeft,
            waveRight,
            waveOut,
            waveIn,
            schwabbel,
            rainbow
        }),
        // new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
        // [](){
        //     bubbles.toggle();
        //     return 0;
        // },
        // {
        //     new Text(ContainerProperties(), TextProperties(), "bubbles")
        // }),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            MovingHead::setDriveRandomAll();
            return 0;
        },
        {
            new Text(ContainerProperties(), TextProperties(), "MH rand")
        }),
        new EffectGroup("Strahler", {0.5, 1., 2.}, {
            lauf,
            dimm,
            wave
        }),
        new EffectGroup("Blinder", {0.5, 1., 2.}, {
            streifenDown,
            streifenUp,
            stars
        }),
    },
    // navbar
    {
        new Button(ContainerProperties(Size(70), Size(70), Spacing(34, 6, 0, 6), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            for(Effect* effect : Effect::getEffects())
                if(effect->getActive())
                    effect->toggle(false);
            return 0;
        }, {
            new Text(ContainerProperties(), TextProperties(), "Off")
        }),
        addTabButton()
    }
);


#endif