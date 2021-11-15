/*
  ViewManager.h - ViewManager-Library for Airduino.
*/

#ifndef ViewManager_h
#define ViewManager_h

#include "Arduino.h"
#include "../view/View.h"

#define VALID_VIEW(view) (view >= 0 || view < views.size())

class ViewManager {
  public:
    static void addView(View* view);
    static void setCurrentView(short view);
    static short getCurrentView();
    static View* getView(short view);
    
  private:
    static std::vector<View*> views;
    static short currentView;

};

#endif