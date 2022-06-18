/*
  NavBar.h - NavBar-Library for Airduino.
*/

#ifndef NavBar_h
#define NavBar_h

#include "Arduino.h"
#include "../container/Container.h"

class NavBar : public Container {
    public:
        NavBar(ContainerProperties properties, std::vector<Container*> content);

    private:

};

#endif