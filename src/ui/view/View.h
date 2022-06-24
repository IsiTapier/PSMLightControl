/*
  View.h - View-Library for Airduino.
*/

#ifndef View_h
#define View_h

#include "Arduino.h"
#include "../container/Container.h"
#include "viewProperties/ViewProperties.h"
#include "../navBar/NavBar.h"
class View;
#include "../viewManager/ViewManager.h"

class View : public Container {
  public:
    //temporary
    View();
    
    View(ContainerProperties properties, ViewProperties viewProperties, std::vector<Container*> content, std::vector<Container*> navBarContent = {});
    
    byte getId();
    void init() override;
    void draw() override;
    virtual uint16_t checkTouch(TSPoint p);

    ViewProperties getViewProperties();
    View* setViewProperties(ViewProperties properties);

    static byte getCurrentId();

  private:
    ViewProperties _viewProperties;
    byte id;
    
    static byte currentId;

};

#endif
