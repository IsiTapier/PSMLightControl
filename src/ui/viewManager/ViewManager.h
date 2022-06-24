/*
  ViewManager.h - ViewManager-Library for Airduino.
*/

#ifndef ViewManager_h
#define ViewManager_h

#include "Arduino.h"
#include "../view/View.h"

#define VALID_VIEW(view) (view >= 0 || view < views.size())

#define DEFAULT_VIEW 0

class ViewManager {
  public:
    static void addView(View* view);
    static void init();
    static void setCurrentView(short view);
    static short getCurrentView();
    static View* getView(short view);
    static std::vector<View*> getViews();
    
  private:
    static std::vector<View*> views;
    static short currentView;

};

#endif