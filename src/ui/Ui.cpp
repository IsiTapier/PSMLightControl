/*
 Ui.cpp - Ui-Library for Librarys.
*/

#include "Ui.h"
View test(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {(new Container(ContainerProperties(Size(200), Size(150), Spacing(10), Spacing(0), Size(5), Size(5)), {(new Container(ContainerProperties(Size(75), Size(45), Spacing(5), Spacing(0), Size(3), Size(3)), {})), (new Container(ContainerProperties(Size(60), Size(45), Spacing(10), Spacing(0), Size(5), Size(5)), {})), (new Container(ContainerProperties(Size(45), Size(60), Spacing(0), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(102), Size(68), Spacing(3), Spacing(8), Size(5), Size(0)), {(new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {}))})), (new Container(ContainerProperties(Size(30), Size(70), Spacing(5), Spacing(0), Size(1), Size(1), false, TFT_WHITE, TFT_BLACK), {}))})), (new Button(ContainerProperties(Size(200), Size(100), Spacing(20, 10, 20, 10), Spacing(0), Size(1), Size(7)), ButtonProperties(), [](){Serial.println("Hello World!");}, {new Text(ContainerProperties(Size(198), Size(78), Spacing(0, 0, 10, 10), Spacing(0), Size(0), Size(0), true), TextProperties(TFT_GOLD, -1, CC_DATUM), "Hello World")})), (new Container(ContainerProperties(Size(500), Size(100), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), (new Container(ContainerProperties(Size(20), Size(170), Spacing(2), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(120), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(200), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), new ContainerGrid(ContainerProperties(Size(280), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ContainerProperties(Size(30), Size(30), Spacing(0), Spacing(0), Size(2), Size(2)), true, {new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {})/*, new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {})*/}), (new Button(ContainerProperties(Size(200), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ButtonProperties(), [](){Serial.println("Button");}, {new Text(ContainerProperties(Size(1., 1), Size(1., 1), Spacing(0), Spacing(0), Size(0), Size(0), true), TextProperties(), "Button")}))});
View test2(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {});
#define METER_TO_PIXEL(m) ((m)*TFT_HEIGHT/16.4)
#define P(m) round(METER_TO_PIXEL(m))
#define M(p) ((p)*16.4/TFT_HEIGHT)
#define STAGE_COLOR TFT_WHITE
#define MV_RADIUS   5
#define OFFSET  0
unsigned long lastRedraw = 0;
bool changes = false;
float lastX = 1000;
float lastY = 1000;
void updatetest(float lastX, float lastY) {
    if(!changes)
        lastRedraw = millis();
    changes = true;
    display.fillCircle(P(lastX/100.+16.4/2), OFFSET+P(lastY/-100.+6.6), MV_RADIUS, TFT_BLACK);
        switch(MovingHead::getActiveMovingHead()) {
            case -1: display.fillCircle(P(MovingHead::getXAll()/100.+16.4/2), OFFSET+P(MovingHead::getYAll()/-100.+6.6), MV_RADIUS, TFT_BLUE); break;
            case 0: display.fillCircle(P(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MV_RADIUS, TFT_GREEN); break;
            case 1: display.fillCircle(P(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MV_RADIUS, TFT_RED); break;
            default: break;
        }
}
void updateBuehne(float lastX, float lastY) {
    if(millis()-lastRedraw>10000 && changes) {
        changes = false;
        lastRedraw = millis();
        display.fillScreen(TFT_BLACK);
        //left wall
        display.drawLine(0, OFFSET+P(6.6-2.3), P(1.4), OFFSET+P(6.6-2.3), STAGE_COLOR);
        //right wall
        display.drawLine(P(16.4-1.4), OFFSET+P(6.6-2.3), P(16.4), OFFSET+P(6.6-2.3), STAGE_COLOR);
        //back wall
        display.drawLine(P((16.4-6.9)/2), OFFSET+0, P((16.4-6.9)/2+6.9), OFFSET+0, STAGE_COLOR);
        //back left wall
        display.drawLine(P((16.4-6.9)/2), OFFSET+0, P((16.4-6.9)/2), OFFSET+P(3), STAGE_COLOR);
        //back right wall
        display.drawLine(P((16.4-6.9)/2+6.9), OFFSET+0, P((16.4-6.9)/2+6.9), OFFSET+P(3), STAGE_COLOR);
        //left diagonal wall
        display.drawLine(P(1.4), OFFSET+P(6.6-2.3), P((16.4-6.9)/2), OFFSET+P(3), STAGE_COLOR);
        //right diagonal wall
        display.drawLine(P(16.4-1.4), OFFSET+P(6.6-2.3), P((16.4-6.9)/2+6.9), OFFSET+P(3), STAGE_COLOR);
        //front stair left
        display.drawLine(P(1.5), OFFSET+P(6.6-2.3), P(2), OFFSET+P(6.6-0.8), STAGE_COLOR);
        display.drawLine(P(2), OFFSET+P(6.6-0.8), P(3.2), OFFSET+P(6.6), STAGE_COLOR);
        //front
        display.drawLine(P(3.2), OFFSET+P(6.6), P(10+3.2), OFFSET+P(6.6), STAGE_COLOR);
        //fornt stair right
        display.drawLine(P(10+3.2), OFFSET+P(6.6), P(16.4-2), OFFSET+P(6.6-0.8), STAGE_COLOR);
        display.drawLine(P(16.4-2), OFFSET+P(6.6-0.8), P(16.4-1.5), OFFSET+P(6.6-2.3), STAGE_COLOR);
        //movingHeads
        display.fillCircle(P(MovingHead::getXAll()/100.+16.4/2), OFFSET+P(MovingHead::getYAll()/-100.+6.6), MV_RADIUS, TFT_BLUE);
        display.fillCircle(P(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MV_RADIUS, TFT_GREEN);
        display.fillCircle(P(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MV_RADIUS, TFT_RED);
    } else {
        display.fillCircle(P(lastX/100.+16.4/2), OFFSET+P(lastY/-100.+6.6), MV_RADIUS, TFT_BLACK);
        switch(MovingHead::getActiveMovingHead()) {
            case 2: display.fillCircle(P(MovingHead::getXAll()/100.+16.4/2), OFFSET+P(MovingHead::getYAll()/-100.+6.6), MV_RADIUS, TFT_BLUE); break;
            case 0: display.fillCircle(P(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MV_RADIUS, TFT_GREEN); break;
            case 1: display.fillCircle(P(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MV_RADIUS, TFT_RED); break;
            default: break;
        }
    }
}
CustomView buehne(ContainerProperties(0, 0), ViewProperties(), [](){MovingHead::setUpdate(&updatetest);}, [](){
    //left wall
    display.drawLine(0, OFFSET+P(6.6-2.3), P(1.4), OFFSET+P(6.6-2.3), STAGE_COLOR);
    //right wall
    display.drawLine(P(16.4-1.4), OFFSET+P(6.6-2.3), P(16.4), OFFSET+P(6.6-2.3), STAGE_COLOR);
    //back wall
    display.drawLine(P((16.4-6.9)/2), OFFSET+0, P((16.4-6.9)/2+6.9), OFFSET+0, STAGE_COLOR);
    //back left wall
    display.drawLine(P((16.4-6.9)/2), OFFSET+0, P((16.4-6.9)/2), OFFSET+P(3), STAGE_COLOR);
    //back right wall
    display.drawLine(P((16.4-6.9)/2+6.9), OFFSET+0, P((16.4-6.9)/2+6.9), OFFSET+P(3), STAGE_COLOR);
    //left diagonal wall
    display.drawLine(P(1.4), OFFSET+P(6.6-2.3), P((16.4-6.9)/2), OFFSET+P(3), STAGE_COLOR);
    //right diagonal wall
    display.drawLine(P(16.4-1.4), OFFSET+P(6.6-2.3), P((16.4-6.9)/2+6.9), OFFSET+P(3), STAGE_COLOR);
    //front stair left
    display.drawLine(P(1.5), OFFSET+P(6.6-2.3), P(2), OFFSET+P(6.6-0.8), STAGE_COLOR);
    display.drawLine(P(2), OFFSET+P(6.6-0.8), P(3.2), OFFSET+P(6.6), STAGE_COLOR);
    //front
    display.drawLine(P(3.2), OFFSET+P(6.6), P(10+3.2), OFFSET+P(6.6), STAGE_COLOR);
    //fornt stair right
    display.drawLine(P(10+3.2), OFFSET+P(6.6), P(16.4-2), OFFSET+P(6.6-0.8), STAGE_COLOR);
    display.drawLine(P(16.4-2), OFFSET+P(6.6-0.8), P(16.4-1.5), OFFSET+P(6.6-2.3), STAGE_COLOR);
    //movingHeads
    display.fillCircle(P(MovingHead::getXAll()/100.+16.4/2), OFFSET+P(MovingHead::getYAll()/-100.+6.6), MV_RADIUS, TFT_BLUE);
    display.fillCircle(P(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MV_RADIUS, TFT_GREEN);
    display.fillCircle(P(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MV_RADIUS, TFT_RED);
}, [](TSPoint p){
    updateBuehne(lastX, lastY);
    if(p.x == (uint16_t)-1 || p.y == (uint16_t)-1)
        return;
    if(!changes)
        lastRedraw = millis();
    changes = true;
    lastX = MovingHead::getMovingHead()->getX();
    lastY = MovingHead::getMovingHead()->getY();
    MovingHead::getMovingHead()->setXY((M(p.x)-16.4/2.)*100, (-M(p.y-OFFSET)+6.6)*100, true);
});

Ui::Ui() {
    
}

void Ui::init() {
    display.init();
    display.setRotation(ROTATION);
    ButtonManager::calibrateTouch();
    ViewManager::init();
    ViewManager::setCurrentView(2);
    ButtonManager::init();
}