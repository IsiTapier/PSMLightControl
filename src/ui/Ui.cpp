/*
 Ui.cpp - Ui-Library for Librarys.
*/

#include "Ui.h"
// View test(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {(new Container(ContainerProperties(Size(200), Size(150), Spacing(10), Spacing(0), Size(5), Size(5)), {(new Container(ContainerProperties(Size(75), Size(45), Spacing(5), Spacing(0), Size(3), Size(3)), {})), (new Container(ContainerProperties(Size(60), Size(45), Spacing(10), Spacing(0), Size(5), Size(5)), {})), (new Container(ContainerProperties(Size(45), Size(60), Spacing(0), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(102), Size(68), Spacing(3), Spacing(8), Size(5), Size(0)), {(new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {}))})), (new Container(ContainerProperties(Size(30), Size(70), Spacing(5), Spacing(0), Size(1), Size(1), false, TFT_WHITE, TFT_BLACK), {}))})), (new Button(ContainerProperties(Size(200), Size(100), Spacing(20, 10, 20, 10), Spacing(0), Size(1), Size(7)), ButtonProperties(), [](){Serial.println("Hello World!");return 0;}, {new Text(ContainerProperties(Size(198), Size(78), Spacing(0, 0, 10, 10), Spacing(0), Size(0), Size(0), true), TextProperties(TFT_GOLD, -1, CC_DATUM), "Hello World")})), (new Container(ContainerProperties(Size(500), Size(100), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), (new Container(ContainerProperties(Size(20), Size(170), Spacing(2), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(120), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(200), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), new ContainerGrid(ContainerProperties(Size(280), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ContainerProperties(Size(30), Size(30), Spacing(0), Spacing(0), Size(2), Size(2)), true, {new Button(ContainerProperties(0, 0), ButtonProperties(), [](){return 0;}, {})/*, new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {})*/}), (new Button(ContainerProperties(Size(200), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ButtonProperties(), [](){Serial.println("Button");return 0;}, {new Text(ContainerProperties(Size(1., 1), Size(1., 1), Spacing(0), Spacing(0), Size(0), Size(0), true), TextProperties(), "Button")}))});
// View test2(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {});
#define METER_TO_PIXEL(m) ((m)*TFT_HEIGHT/16.4)
#define P(m) round(METER_TO_PIXEL(m))
#define M(p) ((p)*16.4/TFT_HEIGHT)
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
        display.fillCircle(P(lastX/100.+16.4/2), OFFSET+P(lastY/-100.+6.6), MV_RADIUS+4, TFT_BLACK);
        xSemaphoreGive(sync_display);
    }
    xSemaphoreTake(sync_display, portMAX_DELAY);
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
#if DRAW_ONLY_ACTIVE
    if(MovingHead::getActiveMovingHead()==-1)
#endif
    display.fillCircle(P(MovingHead::getXAll()/100.+16.4/2), OFFSET+P(MovingHead::getYAll()/-100.+6.6), MovingHead::getActiveMovingHead()==-1?MV_RADIUS+3:MV_RADIUS, TFT_BLUE);
#if DRAW_ONLY_ACTIVE
    else {
#endif 
    display.fillCircle(P(MovingHead::getMovingHead(0)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(0)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==0?MV_RADIUS+3:MV_RADIUS, TFT_GREEN);
    display.fillCircle(P(MovingHead::getMovingHead(1)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(1)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==1?MV_RADIUS+3:MV_RADIUS, TFT_RED);
    display.fillCircle(P(MovingHead::getMovingHead(2)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(2)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==2?MV_RADIUS+3:MV_RADIUS, TFT_YELLOW);
    display.fillCircle(P(MovingHead::getMovingHead(3)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(3)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==3?MV_RADIUS+3:MV_RADIUS, TFT_PURPLE);
    display.fillCircle(P(MovingHead::getMovingHead(4)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(4)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==4?MV_RADIUS+3:MV_RADIUS, TFT_ORANGE);
    display.fillCircle(P(MovingHead::getMovingHead(5)->getX(true)/100.+16.4/2), OFFSET+P(MovingHead::getMovingHead(5)->getY(true)/-100.+6.6), MovingHead::getActiveMovingHead()==5?MV_RADIUS+3:MV_RADIUS, TFT_DARKCYAN);
#if DRAW_ONLY_ACTIVE
    }
#endif 
    xSemaphoreGive(sync_display);
}
/*Übyte speed = 2;
DMXDevice barsShip(UNIVERSE_2, 114, RGB, UNIVERSE_1, 20, RGB, 12, 4);
#define WRITE_WHITE(c, m)   bars->writeChannels((((c)%(4*12))*3), 150*m); \
                            bars->writeChannels((((c)%(4*12))*3)+1, 255*m); \
                            bars->writeChannels((((c)%(4*12))*3)+2, 130*m);
#define WRITE_BLUE(c, m)    bars->writeChannels(((c)%(4*12))*3, 0*m); \
                            bars->writeChannels(((c)%(4*12))*3+1, 40*m); \
                            bars->writeChannels(((c)%(4*12))*3+2, 255*m);
bool waveAnimationActive = false;
TaskHandle_t waveAnimationHandle;
void waveAnimation(void* parm) {
    DMXDevice* bars = (DMXDevice*) parm;
    bool state = 0;
    for(;;) {
        for(int i=0; i<12; i++) {
            for(int j=0; j<12; j++) {
                WRITE_BLUE(j, 1.);
                WRITE_BLUE(1*(12)+j, 1.);
                WRITE_BLUE(2*(12)+j, 1.);
                WRITE_BLUE(3*(12)+j, 1.);
            }
            for(int a=0; a<4; a++) {
                WRITE_WHITE((a*(12)+i), .25)
                WRITE_WHITE((a*(12)+i+1), .5)
                WRITE_WHITE((a*(12)+i+2), .8)
                WRITE_WHITE((a*(12)+i+3), 1.)
                WRITE_WHITE((a*(12)+i+4), .8)
                WRITE_WHITE((a*(12)+i+5), .5)
                WRITE_WHITE((a*(12)+i+6), .25)
            }
            vTaskDelay((5-speed)*50);
        }
    }
}
bool waterAnimationActive = false;
TaskHandle_t waterAnimationHandle;
void waterAnimation(void* parm) {
    DMXDevice* bars = (DMXDevice*) parm;
    bool state = 0;
    for(;;) {
        for(int i = state?2:0; i < 4*12; i+=4) {
            WRITE_WHITE(i, 1.)
            WRITE_WHITE(i+1, 1.)
            WRITE_BLUE(i+2, 1.)
            WRITE_BLUE(i+3, 1.)
        }
        state=!state;
        vTaskDelay((5-speed)*300);
    }
}*/
std::vector<std::array<Position, MOVING_HEADS_AMOUNT+1>> presetPositions = {{Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT),Position(X_DEFAULT,Y_DEFAULT)}};
Container movingHeadButtons(ContainerProperties(Size(480), Size(70), Spacing(0, 0, 320-70-8-60-15, 0), Spacing(0), Size(0), Size(0), true), {
        new Button(ContainerProperties(Size(70), Size(70), Spacing(10, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(0);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_GREEN), "MV 1")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(1);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_RED), "MV 2")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(2);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_YELLOW), "MV 3")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(3);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_PURPLE), "MV 4")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(4);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_ORANGE), "MV 5")}),
        new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 10, 0, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setActiveMovingHead(5);return 0;}, {new Text(ContainerProperties(), TextProperties(TFT_DARKCYAN), "MV 6")})
    });
/*Container speedButtons(ContainerProperties(Size(4*78-8), Size(86), Spacing(0), Spacing(0), Size(0), Size(0), true), {
    new Button(ContainerProperties(Size(70), Size(70), Spacing(0, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 1; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 1")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 2; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 2")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 3; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 3")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 0, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 4; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 4")})
});*/
CustomView Ui::buehne(ContainerProperties(0, 0), ViewProperties(), [](){MovingHead::setUpdate(&updateBuehne);}, [](){
    updateBuehne(0, 0);
}, [](TSPoint p){
    if(p.x == (uint16_t)-1 || p.y == (uint16_t)-1)
        return 0;
    lastX = MovingHead::getMovingHead()->getX();
    lastY = MovingHead::getMovingHead()->getY();
    MovingHead::getMovingHead()->setXY((M(p.x)-16.4/2.)*100, (-M(p.y-OFFSET)+6.6)*100, true);
    updateBuehne(lastX, lastY);
    return 0;
}, {new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(), [](){ViewManager::setCurrentView(1);return 0;}, {new Text(ContainerProperties(), TextProperties(), "Presets")}),
    new Button(ContainerProperties(Size(100), Size(60), Spacing(480-2*100-2*17, 15, 15, 15), Spacing(4), Size(2), Size(4)), ButtonProperties(), [](){for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[0][i]);MovingHead::setPositionAll(presetPositions[0][MOVING_HEADS_AMOUNT]);updateBuehne(0, 0, true);/*MovingHead::resetPositions();*/return 0;}, {new Text(ContainerProperties(), TextProperties(), "Home")}),
    // new Button(ContainerProperties(Size(70), Size(70), Spacing(480-70-10, 10, 10, 4), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){if(waterAnimationActive){waterAnimationActive=false;vTaskDelete(waterAnimationHandle);barsShip.setUpdate(true);}else{if(waveAnimationActive){vTaskDelete(waveAnimationHandle);waveAnimationActive=false;}waterAnimationActive=true;barsShip.setUpdate(false);xTaskCreate(waterAnimation, "Water Animation", 1*1024, &barsShip, 6, &waterAnimationHandle);}return 0;}, {new Text(ContainerProperties(), TextProperties(), "Water")}),
    // new Button(ContainerProperties(Size(70), Size(70), Spacing(10, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){MovingHead::setDriveRandomAll();for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[0][i]);MovingHead::setPositionAll(presetPositions[0][MOVING_HEADS_AMOUNT]);return 0;}, {new Text(ContainerProperties(), TextProperties(), "Wirbel")}),
    // &speedButtons,
    // new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 10, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){if(waveAnimationActive){waveAnimationActive=false;vTaskDelete(waveAnimationHandle);barsShip.setUpdate(true);}else{if(waterAnimationActive){vTaskDelete(waterAnimationHandle);waterAnimationActive=false;}waveAnimationActive=true;barsShip.setUpdate(false);xTaskCreate(waveAnimation, "Wave Animation", 1*1024, &barsShip, 6, &waveAnimationHandle);}return 0;}, {new Text(ContainerProperties(), TextProperties(), "Wave")}),
    &movingHeadButtons
});
Container presets(ContainerProperties(Size(480-24), Size(320-90), Spacing(Size(12), Size(12), Size(0), Size(0)), Spacing(5), 0, 0, true), {});
struct EepromPosition {
    byte id;
    std::array<Position, MOVING_HEADS_AMOUNT+1> positions;
};
struct EepromData {
    byte currentPosition = 1;
    EepromPosition eepromPositions[20];
} eepromData;
bool deletePreset = false;
void storeEeprom() {
    EEPROM.put(0, eepromData);
    EEPROM.commit();
}
void readEeprom() {
    // for (int i = 0; i < 512; i++) {
    //     EEPROM.write(i, 0);
    // }
    // EEPROM.commit();   
    eepromData = EEPROM.get(0, eepromData);
    for(Position p:eepromData.eepromPositions[0].positions)
        if(p.getX()!=0||p.getY()!=0) {
            presetPositions.at(0) = eepromData.eepromPositions[0].positions;
            break;
        }
    for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[0][i]);MovingHead::setPositionAll(presetPositions[0][MOVING_HEADS_AMOUNT]);updateBuehne(0, 0, true);
    if(eepromData.currentPosition == 1)
        return;
    if(eepromData.currentPosition>=20)
        eepromData.currentPosition = 19;
    for(int i = 1; i < eepromData.currentPosition; i++) {
        presetPositions.push_back(eepromData.eepromPositions[i].positions);
        presets.addContent(new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), std::bind([](byte id, short buttonId){if(deletePreset){deletePreset=false;presets.removeContent(id-1);ButtonManager::removeButton(buttonId);for(int i = 0; i < eepromData.currentPosition; i++){if(eepromData.eepromPositions[i].id==id){if(eepromData.currentPosition>0)eepromData.currentPosition--;for(int j = i; j < eepromData.currentPosition; j++){eepromData.eepromPositions[j]=eepromData.eepromPositions[j+1];Serial.print("move");Serial.println(j);};storeEeprom();}}}else{for(int i = 0; i < MOVING_HEADS_AMOUNT; i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[id][i]);MovingHead::setPositionAll(presetPositions[id][MOVING_HEADS_AMOUNT]);}return 0;}, presets.getPorperties().getCurrentId()+2, ButtonManager::getCurrentId()+1), {new Text(ContainerProperties(), TextProperties(), "preset "+String((presets.getPorperties().getCurrentId()+2)%256))}));
        eepromData.eepromPositions[i].id=presets.getPorperties().getCurrentId()+1;
    }
    storeEeprom();
}
#include <algorithm>
#include <iostream>
View presetView(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {
    new Button(ContainerProperties(Size(100), Size(60), Spacing(17, 15, 15, 15), Spacing(2), Size(2), Size(4)), ButtonProperties(), [](){ViewManager::setCurrentView(0); deletePreset=false;return 0;}, {new Text(ContainerProperties(), TextProperties(), "B"+ue+"hne")}),
    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_DARKGREEN), ButtonProperties(), [](){std::array<Position, MOVING_HEADS_AMOUNT+1>p;std::for_each(p.begin(),std::prev(p.end()),[i=0](Position& n)mutable{n=MovingHead::getMovingHead(i++)->getPosition();});p.at(MOVING_HEADS_AMOUNT)=MovingHead::getPositionAll();presetPositions.push_back(p);if(eepromData.currentPosition<19)eepromData.eepromPositions[eepromData.currentPosition]={(byte)((presets.getPorperties().getCurrentId()+1)%256), p};eepromData.currentPosition++;Serial.println(eepromData.currentPosition);storeEeprom();presets.addContent(new Button(ContainerProperties(Size(70), Size(70), Spacing(5), 0, 2, 3), ButtonProperties(), std::bind([](byte id, short buttonId){if(deletePreset){deletePreset=false;presets.removeContent(id-1);ButtonManager::removeButton(buttonId);for(int i = 0; i < eepromData.currentPosition; i++){if(eepromData.eepromPositions[i].id==id){if(eepromData.currentPosition>0)eepromData.currentPosition--;for(int j = i; j < eepromData.currentPosition-1; j++)eepromData.eepromPositions[j]=eepromData.eepromPositions[j+1];storeEeprom();return 0;}}}else{for(int i=0;i<MOVING_HEADS_AMOUNT;i++)MovingHead::getMovingHead(i)->setPosition(presetPositions[id][i]);MovingHead::setPositionAll(presetPositions[id][MOVING_HEADS_AMOUNT]);}return 0;}, (presets.getPorperties().getCurrentId()+2)%256, (ButtonManager::getCurrentId()+1)%256), {new Text(ContainerProperties(), TextProperties(), "preset "+String((presets.getPorperties().getCurrentId()+2)%256))}));deletePreset=false;return 0;}, {new Text(ContainerProperties(), TextProperties(NO_COLOR, 3), "add")}),
    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4), false, NO_COLOR, TFT_RED), ButtonProperties(), [](){if(presets.getContentAmount()>0)deletePreset=true;return 0;}, {new Text(ContainerProperties(), TextProperties(), "delete")}),
    new Button(ContainerProperties(Size(100), Size(60), Spacing(15), Spacing(2), Size(2), Size(4)), ButtonProperties(), [](){for(int i=0;i<MOVING_HEADS_AMOUNT;i++)presetPositions[0][i]=MovingHead::getMovingHead(i)->getPosition();presetPositions[0][MOVING_HEADS_AMOUNT]=MovingHead::getPositionAll();eepromData.eepromPositions[0]={0,presetPositions[0]};storeEeprom();return 0;},{new Text(ContainerProperties(), TextProperties(), "set home")}),
    &presets});
Ui::Ui() {
    
}

void Ui::init() {
    EEPROM.begin(sizeof(EepromData));
    xSemaphoreTake(sync_display, portMAX_DELAY);
    display.init();
    display.setRotation(ROTATION);
    xSemaphoreGive(sync_display);
    ButtonManager::calibrateTouch();
    ViewManager::init();
    ViewManager::setCurrentView(0);
    ButtonManager::init();
    readEeprom();   
}