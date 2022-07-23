/*
  AnimationUi.h - AnimationUi-Library for Airduino.
*/

#ifndef AnimationUi_h
#define AnimationUi_h

#include "../../view/View.h"
#include "Effect/Effect.h"
#include "Devices.h"
#include "MovingHead.h"

MultiEffect bubbles("bubbles", {&bars}, 250, {new MultiEffect::EffectPoint((byte)0, 108, (float).2, (byte)40, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float)-.4, (byte)100, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).1, (byte)80), new MultiEffect::EffectPoint((byte)0, 108, (float)-.7, (byte)10, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).1, (byte)40, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float).5, (byte)120, 5, 5), new MultiEffect::EffectPoint((byte)0, 108, (float)-.2, (byte)60, 5, 5)}, 2);
MultiEffect lauflicht("lauf", &strahler, 250, {new MultiEffect::EffectPoint(0, 56, 1., 0)});
MultiEffect waveOut("out", &bars, 250, {new MultiEffect::EffectPoint(0, 108/2, -1., 0, 0, 108/4), new MultiEffect::EffectPoint(108/2, 108, 1., 108/2, 108/4, 0)});

View animationUi(ContainerProperties(-1, -1), ViewProperties("Animation"),
    // content
    {
        new EffectButton("lauf", {&strahler}, 300),
        new EffectButton("dimm", {&strahler}, 50, .1, 2),
        new EffectButton("wave", {&strahler}, 30, .1, 5),

        new EffectButton("wave L", {&bars}, 25, .5, 0, 54, Effect::LEFT),
        new EffectButton("wave R", {&bars}, 25, 1., 54, 0, Effect::RIGHT),
        new EffectButton("wave out", {&bars}, 30, 1., 0, 27, Effect::OUT),
        new EffectButton("wave in", {&bars}, 30, 1., 27, 0, Effect::IN),
        new EffectButton("schwabbel", {&bars}, 50, 1., 36, EQUAL_SPREAD, Effect::OUT),

        new EffectButton("str down", {&blinder1, &blinder2}, 20, .2, 0, 10, Effect::DOWN, 70),
        new EffectButton("str up", {&blinder1, &blinder2}, 20, .2, 10, 0, Effect::UP, 70),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            bubbles.toggle();
            return 0;
        },
        {
            new Text(ContainerProperties(), TextProperties(), "bubbles")
        }),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            MovingHead::setDriveRandomAll();
            return 0;
        },
        {
            new Text(ContainerProperties(), TextProperties(), "MH rand")
        }),
    },
    // navbar
    {

    }
);


#endif