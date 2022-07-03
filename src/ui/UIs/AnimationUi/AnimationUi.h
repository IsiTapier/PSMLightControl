/*
  AnimationUi.h - AnimationUi-Library for Airduino.
*/

#ifndef AnimationUi_h
#define AnimationUi_h

#include "../../view/View.h"
#include "../../button/Button.h"
#include "Animations.h"

View animationUi(ContainerProperties(-1, -1), ViewProperties("Animation"),
    // content
    {
        // strahler
        // lauflicht
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                lauflicht.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Lauf")
            }
        ),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                dimm.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Dimm")
            }
        ),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                wave.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Wave")
            }
        ),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                waveLeft.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Wave L")
            }
        ),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                waveRight.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Wave R")
            }
        ),
        new Button(ContainerProperties(Size(60), Size(60), Spacing(15, 7), Spacing(0), Spacing(2)), ButtonProperties(), 
            // start animation
            [](){
                streifen1.toggle();
                streifen2.toggle();
                // streifen3.toggle();
                return 0;
            },
            {
                new Text(ContainerProperties(), TextProperties(), "Streifen")
            }
        ),
    },
    // navbar
    {

    }
);


#endif