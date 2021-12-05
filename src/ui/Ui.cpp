/*
 Ui.cpp - Ui-Library for Librarys.
*/

#include "Ui.h"

View test(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {(new Container(ContainerProperties(Size(200), Size(150), Spacing(10), Spacing(0), Size(5), Size(5)), {(new Container(ContainerProperties(Size(75), Size(45), Spacing(5), Spacing(0), Size(3), Size(3)), {})), (new Container(ContainerProperties(Size(60), Size(45), Spacing(10), Spacing(0), Size(5), Size(5)), {})), (new Container(ContainerProperties(Size(45), Size(60), Spacing(0), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(102), Size(68), Spacing(3), Spacing(8), Size(5), Size(0)), {(new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {}))})), (new Container(ContainerProperties(Size(30), Size(70), Spacing(5), Spacing(0), Size(1), Size(1), false, TFT_WHITE, TFT_BLACK), {}))})), (new Button(ContainerProperties(Size(200), Size(100), Spacing(20, 10, 20, 10), Spacing(0), Size(1), Size(7)), ButtonProperties(), [](){Serial.println("Hello World!");}, {new Text(ContainerProperties(Size(198), Size(78), Spacing(0, 0, 10, 10), Spacing(0), Size(0), Size(0), true), TextProperties(TFT_GOLD, -1, CC_DATUM), "Hello World")})), (new Container(ContainerProperties(Size(500), Size(100), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), (new Container(ContainerProperties(Size(20), Size(170), Spacing(2), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(120), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(200), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), (new Button(ContainerProperties(Size(200), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ButtonProperties(), [](){Serial.println("Button");}, {new Text(ContainerProperties(Size(1., 1), Size(1., 1), Spacing(0), Spacing(0), Size(0), Size(0), true), TextProperties(), "Button")}))});
View test2(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {});
Ui::Ui() {
    
}

void Ui::init() {
    display.init();
    display.setRotation(ROTATION);
    ButtonManager::calibrateTouch();
    ViewManager::init();
    // ViewManager::setCurrentView(0);
    ButtonManager::init();
}