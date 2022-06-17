/*
  MovingHeadUi.h - MovingHeadUi-Library for Airduino.
*/

#ifndef MovingHeadUi_h
#define MovingHeadUi_h

#include "Arduino.h"
#include "../../customView/CustomView.h"
#include "../../button/Button.h"
#include "../../textField/Text.h"
#include "MovingHead.h"

#define METER_TO_PIXEL(m) ((m)*TFT_HEIGHT/16.4)
#define PIXEL(m) round(METER_TO_PIXEL(m))
#define METER(p) ((p)*16.4/TFT_HEIGHT)
#define STAGE_COLOR TFT_WHITE
#define MV_RADIUS   5
#define OFFSET  0


float lastX = 1000;
float lastY = 1000;

void updateBuehne(float lastX, float lastY, bool redraw = false) {
    if(ViewManager::getCurrentView() != 0)
        return;
    if(redraw)
        ViewManager::setCurrentView(ViewManager::getCurrentView());
    else {
        xSemaphoreTake(sync_display, portMAX_DELAY);
        display.fillCircle(PIXEL(lastX/100.+16.4/2), OFFSET+PIXEL(lastY/-100.+6.6), MV_RADIUS+4, TFT_BLACK);
        xSemaphoreGive(sync_display);
    }
    xSemaphoreTake(sync_display, portMAX_DELAY);
    //left wall
    display.drawLine(0, OFFSET+PIXEL(6.6-2.3), PIXEL(1.4), OFFSET+PIXEL(6.6-2.3), STAGE_COLOR);
    //right wall
    display.drawLine(PIXEL(16.4-1.4), OFFSET+PIXEL(6.6-2.3), PIXEL(16.4), OFFSET+PIXEL(6.6-2.3), STAGE_COLOR);
    //back wall
    display.drawLine(PIXEL((16.4-6.9)/2), OFFSET+0, PIXEL((16.4-6.9)/2+6.9), OFFSET+0, STAGE_COLOR);
    //back left wall
    display.drawLine(PIXEL((16.4-6.9)/2), OFFSET+0, PIXEL((16.4-6.9)/2), OFFSET+PIXEL(3), STAGE_COLOR);
    //back right wall
    display.drawLine(PIXEL((16.4-6.9)/2+6.9), OFFSET+0, PIXEL((16.4-6.9)/2+6.9), OFFSET+PIXEL(3), STAGE_COLOR);
    //left diagonal wall
    display.drawLine(PIXEL(1.4), OFFSET+PIXEL(6.6-2.3), PIXEL((16.4-6.9)/2), OFFSET+PIXEL(3), STAGE_COLOR);
    //right diagonal wall
    display.drawLine(PIXEL(16.4-1.4), OFFSET+PIXEL(6.6-2.3), PIXEL((16.4-6.9)/2+6.9), OFFSET+PIXEL(3), STAGE_COLOR);
    //front stair left
    display.drawLine(PIXEL(1.5), OFFSET+PIXEL(6.6-2.3), PIXEL(2), OFFSET+PIXEL(6.6-0.8), STAGE_COLOR);
    display.drawLine(PIXEL(2), OFFSET+PIXEL(6.6-0.8), PIXEL(3.2), OFFSET+PIXEL(6.6), STAGE_COLOR);
    //front
    display.drawLine(PIXEL(3.2), OFFSET+PIXEL(6.6), PIXEL(10+3.2), OFFSET+PIXEL(6.6), STAGE_COLOR);
    //fornt stair right
    display.drawLine(PIXEL(10+3.2), OFFSET+PIXEL(6.6), PIXEL(16.4-2), OFFSET+PIXEL(6.6-0.8), STAGE_COLOR);
    display.drawLine(PIXEL(16.4-2), OFFSET+PIXEL(6.6-0.8), PIXEL(16.4-1.5), OFFSET+PIXEL(6.6-2.3), STAGE_COLOR);
    //movingHeads
#if DRAW_ONLY_ACTIVE
    if(MovingHead::getActiveMovingHead()==-1)
#endif
    display.fillCircle(PIXEL(MovingHead::getXAll()/100.+16.4/2), OFFSET+PIXEL(MovingHead::getYAll()/-100.+6.6), MovingHead::getActiveMovingHead()==-1?MV_RADIUS+3:MV_RADIUS, TFT_BLUE);
#if DRAW_ONLY_ACTIVE
    else {
#endif 
    display.fillCircle(PIXEL(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==0?MV_RADIUS+3:MV_RADIUS, TFT_GREEN);
    display.fillCircle(PIXEL(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==1?MV_RADIUS+3:MV_RADIUS, TFT_RED);
    display.fillCircle(PIXEL(MovingHead::getMovingHead(2)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(2)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==2?MV_RADIUS+3:MV_RADIUS, TFT_YELLOW);
    display.fillCircle(PIXEL(MovingHead::getMovingHead(3)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(3)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==3?MV_RADIUS+3:MV_RADIUS, TFT_PURPLE);
    display.fillCircle(PIXEL(MovingHead::getMovingHead(4)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(4)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==4?MV_RADIUS+3:MV_RADIUS, TFT_ORANGE);
    display.fillCircle(PIXEL(MovingHead::getMovingHead(5)->getX(true)/100.+16.4/2), OFFSET+PIXEL(MovingHead::getMovingHead(5)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==5?MV_RADIUS+3:MV_RADIUS, TFT_DARKCYAN);
#if DRAW_ONLY_ACTIVE
    }
#endif 
    xSemaphoreGive(sync_display);
}

Container movingHeadButtons(ContainerProperties(Size(480), Size(70), Spacing(0, 0, 320-70-8-60-15, 0), Spacing(0), Size(0), Size(0), true), {
        new Button(ContainerProperties(Size(70), Size(70), Spacing(10, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(0);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_GREEN), "MV 1")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(1);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_RED), "MV 2")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(2);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_YELLOW), "MV 3")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(3);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_PURPLE), "MV 4")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(4);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_ORANGE), "MV 5")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 10, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(5);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_DARKCYAN), "MV 6")})
    });

CustomView mhUi(ContainerProperties(0, 0), ViewProperties(),
    // setup
    [](){ MovingHead::setUpdate(&updateBuehne); },
    // draw
    [](){ updateBuehne(0, 0); },
    // touch event
    [](TSPoint p){
        if(p.x == (uint16_t)-1 || p.y == (uint16_t)-1)
            return 0;
        lastX = MovingHead::getMovingHead()->getX();
        lastY = MovingHead::getMovingHead()->getY();
        MovingHead::getMovingHead()->setXY((METER(p.x)-16.4/2.)*100, (-METER(p.y-OFFSET)+6.6)*100, true);
        updateBuehne(lastX, lastY);
        return 0;
    },
    // content
    {   
        // mode button
        new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(), 
            // touch event
            [](){
                ViewManager::setCurrentView(1);
                return 0;
            },
            // content 
            {
                new Text(ContainerProperties(), TextProperties(), "Presets")
            }
        ),

        // home button
        new Button(ContainerProperties(Size(100), Size(60), Spacing(480-2*100-2*17, 15, 15, 15), Spacing(4), Size(2), Size(4)), ButtonProperties(),
            // touch event
            [](){
                MovingHead::resetPositions();
                return 0;
            },
            // content
            {
            new Text(ContainerProperties(), TextProperties(), "Home")
            }
        ),

        // new Button(ContainerProperties(Size(70), Size(70), Spacing(480-70-10, 10, 10, 4), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){if(waterAnimationActive){waterAnimationActive=false;vTaskDelete(waterAnimationHandle);barsShip.setUpdate(true);}else{if(waveAnimationActive){vTaskDelete(waveAnimationHandle);waveAnimationActive=false;}waterAnimationActive=true;barsShip.setUpdate(false);xTaskCreate(waterAnimation, "Water Animation", 1*1024, &barsShip, 6, &waterAnimationHandle);}return 0;}, {new Text(ContainerProperties(), TextProperties(), "Water")}),
        // new Button(ContainerProperties(Size(70), Size(70), Spacing(10, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setDriveRandomAll();for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[0][i]);MovingHead::setPositionAll(presetPositions[0][MOVING_HEADS_AMOUNT]);return 0;}, {new Text(ContainerProperties(), TextProperties(), "Wirbel")}),
        // &speedButtons,
        // new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 10, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){if(waveAnimationActive){waveAnimationActive=false;vTaskDelete(waveAnimationHandle);barsShip.setUpdate(true);}else{if(waterAnimationActive){vTaskDelete(waterAnimationHandle);waterAnimationActive=false;}waveAnimationActive=true;barsShip.setUpdate(false);xTaskCreate(waveAnimation, "Wave Animation", 1*1024, &barsShip, 6, &waveAnimationHandle);}return 0;}, {new Text(ContainerProperties(), TextProperties(), "Wave")}),
        &movingHeadButtons
    }
);



#endif