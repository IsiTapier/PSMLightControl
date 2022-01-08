/*
  MovingHead.h - MovingHead-Library for Airduino.
*/

#ifndef MovingHead_h
#define MovingHead_h

#include "Arduino.h"
#include "DMXDevice.h"
#include "Joystick.h"
#include "../../src/Pins.h"


#define TOGETHER_MODE       0
#define COMMON_ZOOM         1

#define DOUBlE_CLICK_TIME   1000

#define SPEED               60
#define X_SPEED             60
#define Y_SPEED             40
#define DEFAULT_SPEED       70
#define DEFAULT_X_SPEED     DEFAULT_SPEED
#define DEFAULT_Y_SPEED     DEFAULT_SPEED

#define X_DEFAULT_MV1       0
#define X_DEFAULT_MV2       0
#define X_DEFAULT           0
#define Y_DEFAULT           200

#define X_MIN               0
#define X_MAX               170
#define Y_MIN               0
#define Y_MAX               255

#define TILT_OFFSET         20
#define TILT_OFFSET_MV1     22
#define TILT_OFFSET_MV2     19
#define PAN_OFFSET_MV1      0.5
#define PAN_OFFSET_MV2      0
#define HEIGHT_MV1          574//570 //guess 5,7 + 4
#define HEIGHT_MV2          694 //710 //guess  6,9 + 4
#define X_OFFSET_MV1        484 //guess (279 rechts) (293)  310 total = 15,875
#define X_OFFSET_MV2        -504 //guess (323 links) (282)  2,9
#define Y_OFFSET            -474 //guess (680) (481) (473)  //mv2, 4,743 (6,557 - 1,792 = 4,765) mv1 4,625 (6,58 - 1,87 = 4,71)
//mv1 pan -1 tilt 25
//mv2 tilt 20
//leichte neigung (hinten und seite anders)
#define STAGE_HIGHT         62
#define STAGE_Y             0
#define STAGE_X             700
#define MV_LENSE_LENGTH     25 //guess

#define DEFAULT_COLOR       50

//22 + 377 170 mv2 + 140
//mv1 5,7 mv3 7,1

#define INPUT_UNIVERSE      UNIVERSE_1
#define INPUT_ADDRESS       508
#define INPUT_FORMAT        ZMC
#define OUTPUT_FORMAT       PTsZMEwcC
#define SPEED_ADDRESS       512
#define HEIGHT_ADDRESS      96

#define MOVING_LOOP_CYCLE   100

#define ACTIVE_MOVINGHEAD   (getMovingHead(activeMovingHead))//(activeMovingHead==0?movingHead1:movingHead2)
#define INACTIVE_MOVINGHEAD (activeMovingHead!=0?movingHead1:movingHead2)

#define VALID_MOVINGHEAD(mv) (mv<_movingHeads.size()?mv:mv%_movingHeads.size())

class Position {
  public:
    Position() : _x(-340282346638528859811704183484516925440), _y(-340282346638528859811704183484516925440) {}
    Position(float x, float y) : _x(x), _y(y) {}
    void setX(float x) {_x = x;}
    void setY(float y) {_y = y;}
    float getX() {return _x;}
    float getY() {return _y;}
    bool isSet() {return _x == -340282346638528859811704183484516925440 || _y == -340282346638528859811704183484516925440;}
  private:
    float _x, _y;
};

class MovingHead {
  public:
    MovingHead(uint16_t height, int16_t xOffset, int16_t yOffset, uint8_t tiltOffset, uint8_t panOffset, DMXUniverse universe, uint16_t address, DMXUniverse inputUniverse = INPUT_UNIVERSE, uint16_t inputAddress = INPUT_ADDRESS);
    MovingHead* setX(float x);
    MovingHead* setY(float y);
    MovingHead* setXY(float x, float y, bool update = false, bool chain = togetherMode);
    MovingHead* addX(float x);
    MovingHead* addY(float y);
    MovingHead* addXY(float x, float y, bool update = false, bool chain = togetherMode);
    float getX(bool trueX = false);
    float getY(bool trueY = false);
    Position getPosition(bool trueVal = false);
    void setPosition(Position position);
    static Position getPositionAll();
    static void setPositionAll(Position position);
    byte getPan();
    byte getTilt();
    static float getXAll();
    static float getYAll();
    
    static MovingHead* getMovingHead(byte movingHead = activeMovingHead);
    static short getActiveMovingHead();
    static void init(bool i);
    void init();

    static void setUpdate(std::function<void(float, float)> update);

    //pan bugs
    //right moving head x > seitlich links y < mv seitlich
    //left moving head > seitlich links < mv seitlich

  private:
    DMXDevice _device;
    float x;
    float y;
    uint16_t _height;
    int16_t _xOffset;
  	int16_t _yOffset;
    uint8_t _tiltOffset;
    uint8_t _panOffset;

    static float xAll;
    static float yAll;
    static byte activeMovingHead;
    static bool togetherMode;
    static unsigned long lastClick;
    static MovingHead movingHead1;
    static MovingHead movingHead2;
    static Joystick joystick;

    static byte _lastHeight;
    static byte _speed;

    byte calculatePan(float x, float y);
    byte calculateTilt(float x, float y);

    static void joystickHandle(float x, float y);
    static void joystickButtonHandle(); 

    static void loop(void*);

    static std::function<void(float, float)> _update;
    static std::vector<MovingHead*> _movingHeads;

};

#endif
