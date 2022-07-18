/*
  AnimationUi.h - AnimationUi-Library for Airduino.
*/

#ifndef AnimationUi_h
#define AnimationUi_h

#include "../../view/View.h"
#include "Effect/Effect.h"
#include "Devices.h"

MultiEffect bubbles("bubbles", {&bars}, 250, {new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float).2, (byte)40, 3, 3), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float)-.4, (byte)100, 3, 3), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float).1, (byte)80), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float)-.7, (byte)10, 3, 3), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float).1, (byte)40, 3, 3), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float).3, (byte)120, 3, 3), new MultiEffect::EffectPoint((byte)0, bars.getDevices(true), (float)-.2, (byte)60, 3, 3)}, 2);
MultiEffect lauflicht("lauf", &strahler, 250, {new MultiEffect::EffectPoint(0, strahler.getDevices(true), 1., 0)});
MultiEffect waveOut("out", &bars, 250, {new MultiEffect::EffectPoint(0, bars.getDevices(true)/2, -1., 0, 0, bars.getDevices(true)/4), new MultiEffect::EffectPoint(bars.getDevices(true)/2, bars.getDevices(true), 1., bars.getDevices(true)/2, bars.getDevices(true)/4, 0)});

View animationUi(ContainerProperties(-1, -1), ViewProperties("Animation"),
    // content
    {
        new EffectButton("lauf", {&strahler}, 300),
        new EffectButton("dimm", {&strahler}, 50, .1, 2),
        new EffectButton("wave", {&strahler}, 30, .1, 5),

        new EffectButton("wave L", {&bars}, 25, 1., bars.getDevices(true)/2, 0, Effect::LEFT),
        new EffectButton("wave R", {&bars}, 25, 1., 0, bars.getDevices(true)/2, Effect::RIGHT),
        new EffectButton("wave out", {&bars}, 30, 1., 0, bars.getDevices(true)/4, Effect::OUT),
        new EffectButton("wave in", {&bars}, 30, 1., bars.getDevices(true)/4, 0, Effect::IN),
        new EffectButton("schwabbel", {&bars}, 50, 1., bars.getDevices(true)/2, EQUAL_SPREAD, Effect::OUT),

        new EffectButton("str down", {&blinder1, &blinder2}, 20, .2, 0, 10, Effect::RIGHT, 70),
        new EffectButton("str up", {&blinder1, &blinder2}, 20, .2, 10, 0, Effect::LEFT, 70),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(),
        [](){
            bubbles.toggle();
            return 0;
        },
        {
            new Text(ContainerProperties(), TextProperties(), "bubbles")
        }),
    },
    // navbar
    {

    }
);


#endif