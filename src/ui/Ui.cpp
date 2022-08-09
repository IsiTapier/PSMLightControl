/*
 Ui.cpp - Ui-Library for Librarys.
*/

#include "Ui.h"
#include "UIs/MovingHeadUi/MovingHeadUi.h"
#include "UIs/PresetUi/PresetUi.h"
// #include "UIs/AnimationUi/AnimationUi.h"
#include "UIs/sceneUi/SceneUi.h"


// View test(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {(new Container(ContainerProperties(Size(200), Size(150), Spacing(10), Spacing(0), Size(5), Size(5)), {(new Container(ContainerProperties(Size(75), Size(45), Spacing(5), Spacing(0), Size(3), Size(3)), {})), (new Container(ContainerProperties(Size(60), Size(45), Spacing(10), Spacing(0), Size(5), Size(5)), {})), (new Container(ContainerProperties(Size(45), Size(60), Spacing(0), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(102), Size(68), Spacing(3), Spacing(8), Size(5), Size(0)), {(new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3)), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {})), (new Container(ContainerProperties(Size(32), Size(20), Spacing(2), Spacing(0), Size(2), Size(3), false, TFT_DARKGREY, TFT_WHITE), {}))})), (new Container(ContainerProperties(Size(30), Size(70), Spacing(5), Spacing(0), Size(1), Size(1), false, TFT_WHITE, TFT_BLACK), {}))})), (new Button(ContainerProperties(Size(200), Size(100), Spacing(20, 10, 20, 10), Spacing(0), Size(1), Size(7)), ButtonProperties(), [](){Serial.println("Hello World!");return 0;}, {new Text(ContainerProperties(Size(198), Size(78), Spacing(0, 0, 10, 10), Spacing(0), Size(0), Size(0), true), TextProperties(TFT_GOLD, -1, CC_DATUM), "Hello World")})), (new Container(ContainerProperties(Size(500), Size(100), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), (new Container(ContainerProperties(Size(20), Size(170), Spacing(2), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(120), Size(120), Spacing(10), Spacing(0), Size(5), Size(7)), {})), (new Container(ContainerProperties(Size(200), Size(200), Spacing(10), Spacing(0), Size(5), Size(0)), {})), new ContainerGrid(ContainerProperties(Size(280), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ContainerProperties(Size(30), Size(30), Spacing(0), Spacing(0), Size(2), Size(2)), true, {new Button(ContainerProperties(0, 0), ButtonProperties(), [](){return 0;}, {})/*, new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {}), new Button(ContainerProperties(0, 0), ButtonProperties(), [](){}, {})*/}), (new Button(ContainerProperties(Size(200), Size(100), Spacing(10), Spacing(0), Size(2), Size(3)), ButtonProperties(), [](){Serial.println("Button");return 0;}, {new Text(ContainerProperties(Size(1., 1), Size(1., 1), Spacing(0), Spacing(0), Size(0), Size(0), true), TextProperties(), "Button")}))});
// View test2(ContainerProperties(Size(TFT_HEIGHT), Size(TFT_WIDTH), Spacing(0), 0, 0, 0), ViewProperties(), {});

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

/*Container speedButtons(ContainerProperties(Size(4*78-8), Size(86), Spacing(0), Spacing(0), Size(0), Size(0), true), {
    new Button(ContainerProperties(Size(70), Size(70), Spacing(0, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 1; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 1")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 2; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 2")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 8, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 3; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 3")}),
    new Button(ContainerProperties(Size(70), Size(70), Spacing(8, 0, 4, 0), Spacing(0), Size(2), Size(4)), ButtonProperties(), [](){speed = 4; MovingHead::setRandomSpeed(speed); return 0;}, {new Text(ContainerProperties(), TextProperties(), "Speed 4")})
});*/

void Ui::init() {
    EEPROM.begin(sizeof(PresetData)+sizeof(SceneData));
    xSemaphoreTake(sync_display, portMAX_DELAY);
    display.init();
    display.setRotation(ROTATION);
    xSemaphoreGive(sync_display);
    ViewManager::init();
    ViewManager::setCurrentView(0);
    readPresets();
    readScenes();  
    ButtonManager::init();
}