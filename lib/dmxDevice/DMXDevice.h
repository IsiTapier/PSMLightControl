/*
  DMXDevice.h - DMXDevice-Library for Airduino.
*/

#ifndef DMXDevice_h
#define DMXDevice_h

#include "Arduino.h"
#include "dmx.h"
#include "Util.h"

//FORMATS
//general
#define X 0x0 //nichts
#define M 0x1 //Master
#define R 0x2 //Rot
#define G 0x3 //Grün
#define B 0x4 //Blau
#define W 0x5 //Weiß
#define S 0x6 //Strobe
#define E 0x7 //Effekt

//Moving Head
#define PAN 0x8 //Pan
#define TILT 0x9 //Tilt
/*
#define s 0xA //Speed

#define w 0xC //Warm white
#define c 0xD //Cold white

*/
#define Z 0xB //Zoom
#define C 0xF //Color temperature

//Devices
#define RGB 0x234
#define MRGB 0x1234
#define RGBW 0x2345
#define MRGBW 0x12345
#define MRGBWSE 0x1234567
#define MXS 0x106
#define PTsZMEwcCXXXX 0x89AB17CDF0000
#define ZMwc 0xB1CD
#define ZMC 0xB1F

#define INPUT_FORMAT_TYPE ((_inputFormat>>(i*4))%16)
#define FORMAT_EQUALS(type) ((_format>>i*4)%16 == type)

class DMXDevice {
  public:
    DMXDevice();
    DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, byte repeat = 1, DMXUniverse inputUniverse = UNIVERSE_1, uint16_t inputAddress = 0, uint64_t inputFormat = 0x0, byte devices = 1, byte distance = 0, std::vector<std::function<byte(byte)>> valueCalculation = {});
    DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, byte repeat = 1, DMXUniverse inputUniverse = UNIVERSE_1, uint16_t inputAddress = 0, uint64_t inputFormat = 0x0, byte devices = 1, byte distance = 0, std::vector<std::function<byte(byte)>> valueCalculation = {});
    void writeChannel(byte channel, byte value, byte device = UINT8_MAX);
    void writeType(byte type, byte value);
    void writeMaster(byte value);
    void writeRed(byte value);
    void writeGreen(byte value);
    void writeBlue(byte value);
    void writeWhite(byte value);
    void writeStrobe(byte value);
    void writeEffect(byte value);
    void blackOut();

  private:
    DMXUniverse _universe;
    uint16_t _address;
    uint64_t _format;
    byte _repeat;
    DMXUniverse _inputUniverse;
    uint16_t _inputAddress;
    uint64_t _inputFormat;
    byte _devices;
    byte _distance;
    boolean hasMaster;
    int16_t virtualMaster = -1;
    DMX* writeUniverse;
    DMX* readUniverse;
    byte formatSize;
    byte inputFormatSize;
    unsigned long readcycle = millis();
    std::vector<std::function<byte(byte)>> _valueCalculation;
    
    void updateChannels();
    static void startUpdateTask(void* _this);

};

#endif
