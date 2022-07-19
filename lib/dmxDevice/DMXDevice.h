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
#define PTsZMEwcC 0x89AB17CDF
#define ZMwc 0xB1CD
#define ZMC 0xB1F
#define MZ 0x1B

#define ALL_DEVICES UINT8_MAX

#define INPUT_FORMAT_TYPE ((input->format>>(i*4))%16)
#define FORMAT_EQUALS(type) ((_format>>i*4)%16 == type)
#define READ_UNIVERSE (DMX::getUniverse(input->universe))

struct Color {
  uint8_t r, g, b;
};

struct Input {
  DMXUniverse universe = UNIVERSE_1;
  uint16_t address = 0;
  uint64_t format = 0x0;
  std::vector<std::function<short(byte)>> valueCalculation = {};
  byte formatSize = 0;
};

class DMXDevice {
  public:
    DMXDevice();
    DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> = {}, byte repeat = 1, byte devices = 1, byte distance = 0);
    DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> = {}, byte repeat = 1, byte devices = 1, byte distance = 0);
    DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, DMXUniverse inputUniverse, uint16_t inputAddress, uint64_t inputFormat, byte repeat = 1, byte devices = 1, byte distance = 0);
    // DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, Input input = none, byte repeat = 1, byte devices = 1, byte distance = 0);
    // DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, byte repeat = 1, Input input = none, byte devices = 1, byte distance = 0);
    void writeChannel(byte channel, byte value, byte device = ALL_DEVICES);
    uint8_t readChannel(Input input, byte channel);
    // void writeChannels(int channel, byte value);
    void writeType(byte type, byte value, byte device = ALL_DEVICES);
    uint8_t readType(byte type);
    void writeMaster(byte value, byte device = ALL_DEVICES);
    void writeRed(byte value, byte device = ALL_DEVICES);
    void writeGreen(byte value, byte device = ALL_DEVICES);
    void writeBlue(byte value, byte device = ALL_DEVICES);
    void writeWhite(byte value, byte device = ALL_DEVICES);
    void writeStrobe(byte value, byte device = ALL_DEVICES);
    void writeEffect(byte value, byte device = ALL_DEVICES);
    void writeColor(Color color);
    void blackOut();
    static void init();
    void setOverrideDevices(std::vector<byte> overrideDevices);
    void setUpdate(bool update);
    void setOutputCalculation(std::function<byte(byte, byte, byte)>);
    bool getUpdate();
    byte getChannels();
    byte getDevices(bool includeRepeat = false);
    byte getRepeat();
    uint64_t getFormat();
    byte getFormatSize(bool includeDistance = false);
    byte getDistance();
    Color getColor();
    //temp
    void setValueCalculation(std::vector<std::function<short(byte)>> valueCalculation);

  private:
    DMXUniverse _universe;
    uint16_t _address;
    uint64_t _format;
    byte _repeat;
    byte _devices;
    byte _distance;
    std::vector<Input> _inputs;

    boolean hasMaster;
    int16_t virtualMaster = -1;
    DMX* virtualMasterUniverse;
    DMX* writeUniverse;
    byte formatSize;
    byte vMasterValue;
    boolean _update = true;
    std::vector<byte> _overrideDevices;
    std::function<byte(byte, byte, byte)> _outputCalculation = [](byte channel, byte device, byte value){return value;};
    unsigned long readcycle = millis();

    static std::vector<DMXDevice*> devices;
    
    void updateChannels();
    static void startUpdateTask(void* _this);
    void setupOutput();
    void setupInputs();

};

#endif
