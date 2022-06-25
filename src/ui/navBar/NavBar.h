/*
  NavBar.h - NavBar-Library for Airduino.
*/

#ifndef NavBar_h
#define NavBar_h

#include "Arduino.h"
#include "../container/Container.h"
#include "../textField/Text.h"

#define NAVBAR_HEIGHT 0.25

class NavBar : public Container {
    public:
        NavBar(ContainerProperties properties, std::vector<Container*> content);
        void init() override;

    private:

};

#endif