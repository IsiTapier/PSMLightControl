/*
 MovingHead.cpp - MovingHead-Library for Librarys.
*/
#include "MovingHead.h"

byte MovingHead::activeMovingHead = 0;
bool MovingHead::togetherMode = TOGETHER_MODE;
bool MovingHead::_driveRandom = 0;
byte MovingHead::_speed = 0;
unsigned long MovingHead::lastClick = 0;
// MovingHead MovingHead::movingHead1(HEIGHT_MV1, X_OFFSET_MV1, Y_OFFSET, TILT_OFFSET_MV1, PAN_OFFSET_MV1, UNIVERSE_3, 1);
// MovingHead MovingHead::movingHead2(HEIGHT_MV2, X_OFFSET_MV2, Y_OFFSET, TILT_OFFSET_MV2, PAN_OFFSET_MV2, UNIVERSE_3, 14);
Joystick MovingHead::joystick(X_POS, Y_POS, BUTTON, joystickHandle, joystickButtonHandle);
std::function<void(float, float, bool)> MovingHead::_update;

float MovingHead::xAll = X_DEFAULT;
float MovingHead::yAll = Y_DEFAULT;

std::vector<MovingHead*> MovingHead::_movingHeads;

MovingHead::MovingHead(uint16_t height, int16_t xOffset, int16_t yOffset, uint8_t tiltOffset, uint8_t panOffset, DMXUniverse universe, uint16_t address, DMXUniverse inputUniverse, uint16_t inputAddress, uint16_t heightAddress, int16_t defaultX, int16_t defaultY) : x(defaultX), y(defaultY), _height(height), _xOffset(xOffset), _yOffset(yOffset), _tiltOffset(tiltOffset), _panOffset(panOffset), _defaultX(defaultX), _defaultY(defaultY), _heightAddress(heightAddress) { //ACHTUNG: QUICK AND DIRTY, fix start positions
    Input i; i.universe=INPUT_UNIVERSE_ALL; i.address=INPUT_ADDRESS_ALL; i.format=INPUT_FORMAT_ALL; i.valueCalculation={{[](byte value){if(value<10)return (byte)DEFAULT_COLOR; else return value;}}};
    Input i2; i2.universe=inputUniverse; i2.address=inputAddress; i2.format=INPUT_FORMAT; i2.valueCalculation={{[](byte value){if(value>=250)return (byte)UINT8_MAX; else return value;}}};
    _device = DMXDevice(&_device, universe, address, (uint64_t)OUTPUT_FORMAT, {i, i2});
    _movingHeads.push_back(this);
    goToHome();
}

MovingHead* MovingHead::setX(float x) {
    /*if(x < X_MIN)
        x = X_MIN;
    if(x > X_MAX)
        x = X_MAX;*/
    if(calculateTilt(x, getY()) != calculateTilt(getX(), getY()))
        _device.writeType(TILT, calculateTilt(x, getY()));
    if(calculatePan(x, getY()) != calculatePan(getX(), getY()))
        _device.writeType(PAN, calculatePan(x, getY()));
    // _device.update();
    if(togetherMode)
        xAll = x;
    else
        this->x = x;
    return this;
}

MovingHead* MovingHead::setY(float y) {
  /*  if(y < Y_MIN)
        y = Y_MIN;
    if(y > Y_MAX)
        y = Y_MAX;*/
    if(calculateTilt(getX(), y) != calculateTilt(getX(), getY()))
        _device.writeType(TILT, calculateTilt(getX(), y));
    if(calculatePan(getX(), y) != calculatePan(getX(), getY()))
        _device.writeType(PAN, calculatePan(getX(), y));
    // _device.update();
    if(togetherMode)
        yAll = y;
    else
        this->y = y;
    return this;
}

MovingHead* MovingHead::setXY(float x, float y, bool update, bool chain) {
    if(update || calculateTilt(x, y) != calculateTilt(getX(), getY()))
        _device.writeType(TILT, calculateTilt(x, y));
    if(update || calculatePan(x, y) != calculatePan(getX(), getY()))
        _device.writeType(PAN, calculatePan(x, y));
    // _device.update();
    if(togetherMode) {
        xAll = x;
        yAll = y;
        if(update && chain)
            for(int i = 0; i < _movingHeads.size(); i++) {
                getMovingHead(i)->addXY(0, 0, update, false);
            }
            //INACTIVE_MOVINGHEAD.addXY(0, 0, true, false);
    } else {
        this->x = x;
        this->y = y;
    }
    return this;
}

MovingHead* MovingHead::addX(float x) {
    setX((togetherMode?xAll:this->x)+x);
    return this;
}

MovingHead* MovingHead::addY(float y) {
    setY((togetherMode?yAll:this->y)+y);
    return this;
}

MovingHead* MovingHead::addXY(float x, float y, bool update, bool chain) {
    setXY((togetherMode?xAll:this->x)+x, (togetherMode?yAll:this->y)+y, update, chain);
    return this;
}

MovingHead* MovingHead::goToHome() {
    setXY(_defaultX, _defaultY, true);
    return this;
}

void MovingHead::resetPositions() {
    for(MovingHead* mv : _movingHeads)
        mv->goToHome();
    _update(0, 0, true);
}

float MovingHead::getX(bool trueX) {
    return togetherMode&&!trueX?xAll:x;
}

float MovingHead::getY(bool trueY) {
    return togetherMode&&!trueY?yAll:y;
}

Position MovingHead::getPosition(bool trueVal) {
    return Position(getX(trueVal), getY(trueVal));
}

void MovingHead::setPosition(Position position) {
    setXY(position.getX(), position.getY(), true);
}

Position MovingHead::getPositionAll() {
    return Position(getXAll(), getYAll());
}

void MovingHead::setPositionAll(Position position) {
    xAll = position.getX();
    yAll = position.getY();
}

byte MovingHead::getPan() {
    return calculatePan(getX(), getY());
}

byte MovingHead::getTilt() {
    return calculateTilt(getX(), getY());
}

float MovingHead::getXAll() {
    return xAll;
}

float MovingHead::getYAll() {
    return yAll;
}

byte MovingHead::getHeight() {
    return _height;
}

void MovingHead::setHeight(byte newHeight) {
    if(newHeight == _lastHeight)
        return;
    _lastHeight = newHeight;
    addXY(0, 0, true);
}

uint16_t MovingHead::getHeightAddress() {
    return _heightAddress;
}

MovingHead* MovingHead::getMovingHead(byte movingHead) {
   return _movingHeads.at(VALID_MOVINGHEAD(movingHead));//&(movingHead==0?movingHead1:movingHead2);
}

short MovingHead::getActiveMovingHead() {
    return togetherMode?-1:VALID_MOVINGHEAD(activeMovingHead);
}

void MovingHead::setActiveMovingHead(byte MovingHead) {
    float lastX = ACTIVE_MOVINGHEAD->getX();
    float lastY = ACTIVE_MOVINGHEAD->getY();
    activeMovingHead = VALID_MOVINGHEAD(MovingHead);
    _update(lastX, lastY, false);
}

void MovingHead::init() {
    _device.writeType(E, UINT8_MAX);
    // _device.writeChannel(2, 0);
    // _device.writeType(M, UINT8_MAX);
    // _device.writeType(Z, UINT8_MAX);
    // _device.writeType(C, DEFAULT_COLOR);
    // _device.writeChannel(9, 0);
    // _device.writeChannel(10, 0);
    // _device.writeChannel(11, 0);
    // _device.writeChannel(12, 0);
    // _device.writeType(PAN, calculatePan(x, y));
    // _device.writeType(TILT, calculateTilt(y, y));
}

void MovingHead::init(bool i) {
    for(int i = 0; i < _movingHeads.size(); i++) {
        getMovingHead(i)->init();
    }
    xTaskCreate(loop, "moving head loop", 1024, NULL, 7, NULL);
    //getMovingHead(1)->init();
}

void MovingHead::setUpdate(std::function<void(float, float, bool)> update) {
    _update = update;
}

byte MovingHead::calculatePan(float x, float y) {
    x-=_xOffset;
    y-=_yOffset;
    float yPan = y==0?90:abs(atan(x/y)*180/PI);
    uint8_t pan = round(170-170*(y<0?(x>0?(360-yPan):(yPan)):(x>0?(180+yPan):(180-yPan)))/360.-_panOffset);
    return pan;
}

#define alpha atan(sqrt(pow(y,2)+pow(x,2))/(double)(_height-_lastHeight*2-(y>STAGE_Y-_yOffset&&abs(x+_xOffset)<STAGE_X?STAGE_HIGHT:0)))*180/PI

byte MovingHead::calculateTilt(float x, float y) {
    x-=_xOffset;
    y-=_yOffset;
    uint8_t tilt = round(127.5+_tiltOffset-TILT_OFFSET-(127.5-TILT_OFFSET)*alpha/90.);
    return tilt;
}

#undef alpha

void MovingHead::driveToHome() {
}

void MovingHead::setDriveRandom(bool value) {
    driveRandom = value;
    if(driveRandom)
        driveTo(Position(_xOffset<0?random(_xOffset+1, 800):random(-700, _xOffset-1), random(-1500, 1000)), random(10, 20));
    else
        vTaskDelete(driveToHandle);
}

void MovingHead::setDriveRandomAll(bool value) {
    _driveRandom = value;
    for(MovingHead* mv : _movingHeads) {
        if(mv->driveRandom != value)
            mv->setDriveRandom(value);
    }
}

void MovingHead::driveTo(Position position, byte speed) {
    // Serial.print("drive from: ");
    // Serial.print(getX(true));
    // Serial.print("|");
    // Serial.print(getY(true));
    // Serial.print(" to: ");
    // Serial.print(position.getX());
    // Serial.print("|");
    // Serial.print(position.getY());
    // Serial.print(" speed: ");
    // Serial.print(speed);
    driveToPosition = position;
    driveToSpeed = speed;
    driveToHandle = NULL;
    xTaskCreate([](void* parm) {
        MovingHead* mv = (MovingHead*) parm;
        Position start = mv->getPosition(true);
        Position route = mv->driveToPosition-start;
        byte steps = round(max(abs(route.getX()), abs(route.getY()))/(double)mv->driveToSpeed);
        // Serial.print(" steps: ");
        // Serial.println(steps);
        byte currentStep = 0;
        for(;;) {
            currentStep++;
            if(currentStep<steps)
                mv->setXY(start.getX()+route.getX()*currentStep/steps, start.getY()+route.getY()*currentStep/steps, true);
            else {
                mv->setPosition(mv->driveToPosition);
                if(mv->driveRandom)
                    mv->setDriveRandom(true);
                vTaskDelete(NULL);     
            }
            vTaskDelay(23/portTICK_PERIOD_MS);
        }
    }, "DriveToLoop", 1*1024, this, 8, &driveToHandle);
}

void MovingHead::joystickHandle(float x, float y) {
    // ACTIVE_MOVINGHEAD.addX(x*(X_SPEED*(_speed==0?DEFAULT_X_SPEED:_speed)/255.))->addY(y*(Y_SPEED*(_speed==0?DEFAULT_Y_SPEED:_speed)/255.));
    // if(togetherMode)
    //     INACTIVE_MOVINGHEAD.addXY(0, 0, true);
    float lastX = ACTIVE_MOVINGHEAD->getX();
    float lastY = ACTIVE_MOVINGHEAD->getY();
    ACTIVE_MOVINGHEAD->addXY(x*(X_SPEED*(_speed==0?DEFAULT_X_SPEED:_speed)/255.), y*(Y_SPEED*(_speed==0?DEFAULT_Y_SPEED:_speed)/255.), true, togetherMode);
    _update(lastX, lastY, false);
    // Serial.print("x: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getX());
    // Serial.print("  y: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getY());
    //Serial.print("  pan: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getPan());
    //Serial.print("  tilt: "); Serial.println((activeMovingHead==0?movingHead1:movingHead2).getTilt());
}

void MovingHead::joystickButtonHandle() {
  float lastX = ACTIVE_MOVINGHEAD->getX();
  float lastY = ACTIVE_MOVINGHEAD->getY();
  activeMovingHead = VALID_MOVINGHEAD(activeMovingHead+1);
  if(millis() - lastClick < DOUBlE_CLICK_TIME) {
    togetherMode = !togetherMode;
    for(int i = 0; i < _movingHeads.size(); i++) {
        getMovingHead(i)->addXY(0, 0, true);
    }
    // ACTIVE_MOVINGHEAD.addXY(0, 0, true);
    // INACTIVE_MOVINGHEAD.addXY(0, 0, true);
    // Serial.println(F("Double click"));
  }
  _update(lastX, lastY, DRAW_ONLY_ACTIVE&&(millis() - lastClick < DOUBlE_CLICK_TIME));
  lastClick = millis();
//   Serial.println(F("click"));
}

void MovingHead::loop(void*) {
    for(;;) {
        vTaskDelay(MOVING_LOOP_CYCLE/portTICK_PERIOD_MS);
        for(MovingHead* mv : _movingHeads)
            mv->setHeight(READ_UNIVERSE_ALL->read(mv->getHeightAddress()));
        
        byte newSpeed = READ_UNIVERSE_ALL->read(SPEED_ADDRESS);
        if(_speed != newSpeed)
            _speed = newSpeed;
    }
}
