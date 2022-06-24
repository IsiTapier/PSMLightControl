/*
  ViewProperties.h - ViewProperties-Library for Airduino.
*/

#ifndef ViewProperties_h
#define ViewProperties_h

#include "Arduino.h"
#include "TFT_eSPI.h"

class ViewProperties {
  public:
    ViewProperties(String name = "");

    String getName();

  private:
    String _name;
    

};

#endif
