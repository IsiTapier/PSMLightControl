/*
 MovingHead.cpp - MovingHead-Library for Librarys.
*/

#include "MovingHead.h"
bool MovingHead::activeMovingHead = 0;
bool MovingHead::togetherMode = TOGETHER_MODE;
unsigned long MovingHead::lastClick = 0;
MovingHead MovingHead::movingHead1(HEIGHT_MV1, X_OFFSET_MV1, Y_OFFSET, TILT_OFFSET_MV1, PAN_OFFSET_MV1, UNIVERSE_3, 1);
MovingHead MovingHead::movingHead2(HEIGHT_MV2, X_OFFSET_MV2, Y_OFFSET, TILT_OFFSET_MV2, PAN_OFFSET_MV2, UNIVERSE_3, 14);
Joystick MovingHead::joystick(X_POS, Y_POS, BUTTON, joystickHandle, joystickButtonHandle);

float MovingHead::xAll = X_DEFAULT;
float MovingHead::yAll = Y_DEFAULT;

MovingHead::MovingHead(uint16_t height, int16_t xOffset, int16_t yOffset, uint8_t tiltOffset, uint8_t panOffset, DMXUniverse universe, uint16_t address, DMXUniverse inputUniverse, uint16_t inputAddress) : x(address==1?X_DEFAULT_MV1:X_DEFAULT_MV2), y(Y_DEFAULT), _height(height), _xOffset(xOffset), _yOffset(yOffset), _tiltOffset(tiltOffset), _panOffset(panOffset) { //ACHTUNG: QUICK AND DIRTY, fix start positions
    _device = DMXDevice(&_device, universe, address, OUTPUT_FORMAT, 1, inputUniverse, inputAddress, INPUT_FORMAT, 1, 0, {NULL, NULL, [](byte value){if(value<10)return (byte)DEFAULT_COLOR; else return value;}});
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
    if(togetherMode)
        yAll = y;
    else
        this->y = y;
    return this;
}

MovingHead* MovingHead::setXY(float x, float y, bool update) {
    if(update || calculateTilt(x, y) != calculateTilt(getX(), getY()))
        _device.writeType(TILT, calculateTilt(x, y));
    if(update || calculatePan(x, y) != calculatePan(getX(), getY()))
        _device.writeType(PAN, calculatePan(x, y));
    if(togetherMode) {
        xAll = x;
        yAll = y;
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

MovingHead* MovingHead::addXY(float x, float y, bool update) {
    setXY((togetherMode?xAll:this->x)+x, (togetherMode?yAll:this->y)+y, update);
    return this;
}

float MovingHead::getX() {
    return togetherMode?xAll:x;
}

float MovingHead::getY() {
    return togetherMode?yAll:y;
}

byte MovingHead::getPan() {
    return calculatePan(getX(), getY());
}

byte MovingHead::getTilt() {
    return calculateTilt(getX(), getY());
}

MovingHead* MovingHead::getMovingHead(bool movingHead) {
   return &(movingHead==0?movingHead1:movingHead2);
}

void MovingHead::init() {
    _device.writeType(E, UINT8_MAX);
    _device.writeChannel(2, 0);
    _device.writeType(M, UINT8_MAX);
    _device.writeType(Z, UINT8_MAX);
    _device.writeType(C, DEFAULT_COLOR);
    _device.writeChannel(9, 0);
    _device.writeChannel(10, 0);
    _device.writeChannel(11, 0);
    _device.writeChannel(12, 0);
    _device.writeType(PAN, calculatePan(x, y));
    _device.writeType(TILT, calculateTilt(y, y));
}

byte MovingHead::calculatePan(float x, float y) {
    x-=_xOffset;
    y-=_yOffset;
    float yPan = y==0?90:abs(atan(x/y)*180/PI);
    uint8_t pan = round(170-170*(y<0?x>0?360-yPan:180-yPan:x>0?180+yPan:180-yPan)/360.-_panOffset);
    return pan;
}

#define alpha atan(sqrt(pow(y,2)+pow(x,2))/(double)(_height-(y>STAGE_Y-_yOffset&&abs(x+_xOffset)<STAGE_X?STAGE_HIGHT:0)))*180/PI

byte MovingHead::calculateTilt(float x, float y) {
    x-=_xOffset;
    y-=_yOffset;
    uint8_t tilt = round(127.5-(127.5-_tiltOffset)*alpha/90.);
    return tilt;
}

#undef alpha

void MovingHead::joystickHandle(float x, float y) {
    ACTIVE_MOVINGHEAD.addX(x*(X_SPEED*(DMX::getUniverse(UNIVERSE_1)->read(SPEED_ADDRESS)==0?DEFAULT_X_SPEED:DMX::getUniverse(UNIVERSE_1)->read(SPEED_ADDRESS))/255.))->addY(y*(Y_SPEED*(DMX::getUniverse(UNIVERSE_1)->read(SPEED_ADDRESS)==0?DEFAULT_Y_SPEED:DMX::getUniverse(UNIVERSE_1)->read(SPEED_ADDRESS))/255.));
    if(togetherMode)
        INACTIVE_MOVINGHEAD.addXY(0, 0, true);
    // Serial.print("x: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getX());
    // Serial.print("  y: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getY());
    //Serial.print("  pan: "); Serial.print((activeMovingHead==0?movingHead1:movingHead2).getPan());
    //Serial.print("  tilt: "); Serial.println((activeMovingHead==0?movingHead1:movingHead2).getTilt());
}

void MovingHead::joystickButtonHandle() {
  activeMovingHead = !activeMovingHead;
  if(millis() - lastClick < DOUBlE_CLICK_TIME) {
    togetherMode = !togetherMode;
    ACTIVE_MOVINGHEAD.addXY(0, 0, true);
    INACTIVE_MOVINGHEAD.addXY(0, 0, true);
  }
  lastClick = millis();
  //Serial.println(F("click"));
}