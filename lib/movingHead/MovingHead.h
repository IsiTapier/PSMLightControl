/*
  MovingHead.h - MovingHead-Library for Airduino.
*/

#ifndef MovingHead_h
#define MovingHead_h

#include "Arduino.h"
#include "DMXDevice.h"
#include "Joystick.h"
#include "../../src/Pins.h"

#define DRAW_ONLY_ACTIVE    1
#define TOGETHER_MODE       0
#define COMMON_ZOOM         1

#define MOVING_HEADS_AMOUNT 6

#define DOUBlE_CLICK_TIME   300

#define SPEED               60
#define X_SPEED             60
#define Y_SPEED             40
#define DEFAULT_SPEED       70
#define DEFAULT_X_SPEED     DEFAULT_SPEED
#define DEFAULT_Y_SPEED     DEFAULT_SPEED

#define X_DEFAULT_MV1       0
#define X_DEFAULT_MV2       0
#define X_DEFAULT_MV3       0
#define X_DEFAULT_MV4       0
#define X_DEFAULT_MV5       0
#define X_DEFAULT_MV6       0
#define X_DEFAULT           0
#define Y_DEFAULT_MV1       Y_DEFAULT
#define Y_DEFAULT_MV2       Y_DEFAULT
#define Y_DEFAULT_MV3       Y_DEFAULT
#define Y_DEFAULT_MV4       Y_DEFAULT
#define Y_DEFAULT_MV5       Y_DEFAULT
#define Y_DEFAULT_MV6       Y_DEFAULT
#define Y_DEFAULT           200

#define X_MIN               0
#define X_MAX               170
#define Y_MIN               0
#define Y_MAX               255

#define TILT_OFFSET         20.5
#define TILT_OFFSET_MV1     21-2
#define TILT_OFFSET_MV2     23.5
#define TILT_OFFSET_MV3     20.5
#define TILT_OFFSET_MV4     21.2
#define TILT_OFFSET_MV5     19.9
#define TILT_OFFSET_MV6     23.5
#define PAN_OFFSET_MV1      0
#define PAN_OFFSET_MV2      0
#define PAN_OFFSET_MV3      0
#define PAN_OFFSET_MV4      0
#define PAN_OFFSET_MV5      0
#define PAN_OFFSET_MV6      0
#define HEIGHT_MV1          701.5
#define HEIGHT_MV2          685.5
#define HEIGHT_MV3          666.7
#define HEIGHT_MV4          624.1
#define HEIGHT_MV5          604.1
#define HEIGHT_MV6          581.6
#define X_OFFSET_MV1        X_OFFSET(true, 299.0)
#define X_OFFSET_MV2        X_OFFSET(true, 455.0)
#define X_OFFSET_MV3        X_OFFSET(true, 615.7)
#define X_OFFSET_MV4        X_OFFSET(false, 620.7)
#define X_OFFSET_MV5        X_OFFSET(false, 461.2)
#define X_OFFSET_MV6        X_OFFSET(false, 297.9)
#define Y_OFFSET            (-652.2+180.4+4)
#define SAAL_LENGTH         1587.2
#define X_OFFSET(left, distance) ((left?-1:1)*(SAAL_LENGTH/2-distance))
//mv1 pan -1 tilt 25
//mv2 tilt 20
//leichte neigung (hinten und seite anders)
#define STAGE_HIGHT         62
#define STAGE_Y             0
#define STAGE_X             700
#define MV_LENSE_LENGTH     20

#define DEFAULT_COLOR       50

//22 + 377 170 mv2 + 140
//mv1 5,7 mv3 7,1

#define INPUT_UNIVERSE_ALL  UNIVERSE_1
#define INPUT_FORMAT        MZ
#define OUTPUT_FORMAT       PTsZMEwcC
#define INPUT_FORMAT_ALL    C
#define INPUT_ADDRESS_ALL   508
#define SPEED_ADDRESS       509
#define READ_UNIVERSE_ALL   DMX::getUniverse(INPUT_UNIVERSE_ALL)

#define INPUT_ADDRESS_MV1   101
#define INPUT_ADDRESS_MV2   103
#define INPUT_ADDRESS_MV3   105
#define INPUT_ADDRESS_MV4   112
#define INPUT_ADDRESS_MV5   114
#define INPUT_ADDRESS_MV6   116
#define HEIGHT_ADDRESS_MV1  118
#define HEIGHT_ADDRESS_MV2  119
#define HEIGHT_ADDRESS_MV3  120
#define HEIGHT_ADDRESS_MV4  121
#define HEIGHT_ADDRESS_MV5  122
#define HEIGHT_ADDRESS_MV6  123

#define MOVING_LOOP_CYCLE   100

#define ACTIVE_MOVINGHEAD   (getMovingHead(activeMovingHead))//(activeMovingHead==0?movingHead1:movingHead2)
#define INACTIVE_MOVINGHEAD (activeMovingHead!=0?movingHead1:movingHead2)

#define VALID_MOVINGHEAD(mv) (mv<_movingHeads.size()?mv:mv%_movingHeads.size())

class Position {
  public:
    Position() : _x(-__FLT_MIN_EXP__), _y(__FLT_MIN_EXP__) {}
    Position(float x, float y) : _x(x), _y(y) {}
    void setX(float x) {_x = x;}
    void setY(float y) {_y = y;}
    float getX() {return _x;}
    float getY() {return _y;}
    bool isSet() {return _x == __FLT_MIN_EXP__ || _y == __FLT_MIN_EXP__;}
    Position operator+(Position p) const {Position result(_x+p.getX(), _y+p.getY());return result;}
    Position operator-(Position p) const {Position result(_x-p.getX(), _y-p.getY());return result;}
  private:
    float _x, _y;
};

class MovingHead {
  public:
    MovingHead(uint16_t height, int16_t xOffset, int16_t yOffset, uint8_t tiltOffset, uint8_t panOffset, DMXUniverse universe, uint16_t address, DMXUniverse inputUniverse, uint16_t inputAddress, uint16_t heightAddress, int16_t defaultX = X_DEFAULT, int16_t defaultY = Y_DEFAULT);
    MovingHead* setX(float x);
    MovingHead* setY(float y);
    MovingHead* setXY(float x, float y, bool update = false, bool chain = togetherMode);
    MovingHead* addX(float x);
    MovingHead* addY(float y);
    MovingHead* addXY(float x, float y, bool update = false, bool chain = togetherMode);
    MovingHead* goToHome();
    static void resetPositions();
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
    byte getHeight();
    void setHeight(byte newHeight);
    uint16_t getHeightAddress();
    void setDriveRandom(bool value);
    void driveTo(Position position, byte speed);
    
    static MovingHead* getMovingHead(byte movingHead = activeMovingHead);
    static short getActiveMovingHead();
    static void setActiveMovingHead(byte mvoingHead);
    static void init(bool i);
    void init();

    static void setUpdate(std::function<void(float, float, bool)> update);
    static void setDriveRandomAll(bool value = !_driveRandom);
    static void driveToHome();
    static void setRandomSpeed(byte speed);

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
    float _defaultX;
    float _defaultY;
    bool driveRandom;
    Position driveToPosition;
    byte driveToSpeed;
    xTaskHandle driveToHandle;

    static float xAll;
    static float yAll;
    static byte activeMovingHead;
    static bool togetherMode;
    static bool _driveRandom;
    static byte _speed;
    static unsigned long lastClick;
    // static MovingHead movingHead1;
    // static MovingHead movingHead2;
    static Joystick joystick;

    byte _lastHeight;
    uint16_t _heightAddress;
    static byte _randomSpeed;

    byte calculatePan(float x, float y);
    byte calculateTilt(float x, float y);

    static void joystickHandle(float x, float y);
    static void joystickButtonHandle(); 

    static void loop(void*);

    static std::function<void(float, float, bool)> _update;
    static std::vector<MovingHead*> _movingHeads;

};

#endif
