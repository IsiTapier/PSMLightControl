/*
 DMXDevice.cpp - DMXDevice-Library for Librarys.
*/

#include "DMXDevice.h"

std::vector<DMXDevice*> DMXDevice::devices = {};

DMXDevice::DMXDevice() {}

DMXDevice::DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> inputs, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), _inputs(inputs), writeUniverse(DMX::getUniverse(universe)) {
    setupOutput();
    setupInputs();
    
    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 2*1024, device, 7, NULL);
}

DMXDevice::DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> inputs, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), _inputs(inputs), writeUniverse(DMX::getUniverse(universe)) {
    setupOutput();
    setupInputs();

    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 2*1024, this, 9, NULL);
}

DMXDevice::DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, DMXUniverse inputUniverse, uint16_t inputAddress, uint64_t inputFormat, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), writeUniverse(DMX::getUniverse(universe)) {
    Input i; i.universe=inputUniverse; i.address=inputAddress; i.format=inputFormat; i.valueCalculation = {};
    _inputs.push_back(i);
    setupOutput();
    setupInputs();
    // _inputs = __inputs;
    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 2*1024, this, 9, NULL);
}

// DMXDevice::DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, byte repeat, Input input, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _inputs({input}), _devices(devices), _distance(distance), writeUniverse(DMX::getUniverse(universe)) {
//     formatSize = floor(logn((double)16, (double)_format)+1);
//     input.formatSize = floor(logn((double)16, (double)input.format)+1);
//     for(int i = 0; i < formatSize; i++)
//         if(FORMAT_EQUALS(M)) {
//             hasMaster = true;
//             break;
//         }
//     if(!hasMaster)
//         for(int i = 0; i < input.formatSize; i++)
//             if(INPUT_FORMAT_TYPE == M) {
//                 virtualMaster = input.address+input.formatSize-i-1;
//                 virtualMasterUniverse = READ_UNIVERSE;
//                 break;
//             }
//     if(_address > 513-(formatSize*_repeat+_distance)*_devices-_distance)
//         _address = 513-(formatSize*_repeat+_distance)*_devices-_distance;
//     if(_address < 1)
//         _address = 1;
//     if(input.address > 513-input.formatSize)
//         _inputs.at(0).address = 513-input.formatSize;
//     if(input.address < 1)
//         _inputs.at(0).address = 1;
//     // DMXDevice::devices.push_back(device);
//     xTaskCreate(startUpdateTask, "updateChannels", 1024, device, 9, NULL);
// }

// DMXDevice::DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, byte repeat, Input input, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _inputs({input}), _devices(devices), _distance(distance), writeUniverse(DMX::getUniverse(universe)) {
//     // DMXDevice(this, universe, address, format, repeat, inputUniverse, inputAddress, inputFormat, devices, distance);
//     formatSize = floor(logn((double)16, (double)_format)+1);
//     input.formatSize = floor(logn((double)16, (double)input.format)+1);
//     for(int i = 0; i < formatSize; i++)
//         if(FORMAT_EQUALS(M)) {
//             hasMaster = true;
//             break;
//         }
//     if(!hasMaster)
//         for(int i = 0; i < input.formatSize; i++)
//             if(INPUT_FORMAT_TYPE == M) {
//                 virtualMaster = input.address+input.formatSize-i-1;
//                 virtualMasterUniverse = READ_UNIVERSE;
//                 break;
//             }
//     if(_address > 513-(formatSize*_repeat+_distance)*_devices-_distance)
//         _address = 513-(formatSize*_repeat+_distance)*_devices-_distance;
//     if(_address < 1)
//         _address = 1;
//     if(input.address > 513-input.formatSize)
//         _inputs.at(0).address = 513-input.formatSize;
//     if(input.address < 1)
//         _inputs.at(0).address = 1;
//     // DMXDevice::devices.push_back(this);
//     xTaskCreate(startUpdateTask, "updateChannels", 1024, this, 9, NULL);
// }

void DMXDevice::setupOutput() {
    formatSize = floor(logn((double)16, (double)_format)+1);
    for(int i = 0; i < formatSize; i++)
        if(FORMAT_EQUALS(M)) {
            hasMaster = true;
            break;
        }
    if(_address > 513-(formatSize*_repeat+_distance)*_devices-_distance)
        _address = 513-(formatSize*_repeat+_distance)*_devices-_distance;
    if(_address < 1)
        _address = 1;
}

void DMXDevice::setupInputs() {
    for(auto input = _inputs.begin(); input != _inputs.end(); input++) {
        input->formatSize = floor(logn((double)16, (double)input->format)+1);
        if(!hasMaster)
            for(int i = 0; i < input->formatSize; i++)
                if(INPUT_FORMAT_TYPE == M) {
                    virtualMaster = input->address+input->formatSize-i-1;
                    virtualMasterUniverse = READ_UNIVERSE;
                    break;
                }
        if(input->address > 513-input->formatSize)
            input->address = 513-input->formatSize;
        if(input->address < 1)
            input->address = 1;
    }
}

void DMXDevice::init() {
    // xTaskCreate(startUpdateTask, "updateChannels", 1024, NULL, 9, NULL);
}

void DMXDevice::writeChannel(byte channel, byte value, byte device) {
    if(channel >= formatSize*_repeat)
        return;
    if(device != UINT8_MAX) return writeUniverse->write(_address+channel+(min(device, _devices)-1)*(_repeat*formatSize+_distance), value);
    for(byte i = 0; i < _devices; i++)
        // if(std::find(_overrideDevices.begin(), _overrideDevices.end(), i) == _overrideDevices.end())
            writeUniverse->write(_address+channel+i*(_repeat*formatSize+_distance), _outputCalculation(channel, i, value));
}

uint8_t DMXDevice::readChannel(Input input, byte channel) {
    if(channel >= input.formatSize*_repeat) return 0;
    return DMX::getUniverse(input.universe)->read(input.address+channel);
}

// void DMXDevice::writeChannels(int channel, byte value) {
//     if(channel >= (formatSize*_repeat+_distance)*_devices)
//         return;
//     writeUniverse->write(_address+channel, value);
// }

void DMXDevice::writeType(byte type, byte value, byte device) {
    if(type == X)
        return;
    if(virtualMaster >= 0) {
        if(type == M)
            vMasterValue = virtualMasterUniverse->read(virtualMaster);
        else if(type == R || type == G || type == B || type == W)
            value = value*vMasterValue/UINT8_MAX;
    }
    for(int i = 0; i < formatSize; i++)
        if(FORMAT_EQUALS(type))
            for(int j = 1; j <= _repeat; j++)
                writeChannel(j*formatSize-1-i, value, device);
}

uint8_t DMXDevice::readType(byte type) {
    if(type == X) return 0;
    for(Input input : _inputs)
        for(int i = 0; i < input.formatSize; i++)
            if((input.format>>(i*4))%16 == type) return readChannel(input, input.formatSize-1-i);
    return 0;
}

void DMXDevice::writeMaster(byte value, byte device) {
    writeType(M, value);
    if(virtualMaster < 0) return;
    virtualMasterUniverse->write(virtualMaster, value, device);
}

void DMXDevice::writeRed(byte value, byte device) {
    writeType(R, value, device);
}

void DMXDevice::writeGreen(byte value, byte device) {
    writeType(G, value, device);
}

void DMXDevice::writeBlue(byte value, byte device) {
    writeType(B, value, device);
}

void DMXDevice::writeWhite(byte value, byte device) {
    writeType(W, value, device);
}

void DMXDevice::writeStrobe(byte value, byte device) {
    writeType(S, value, device);
}

void DMXDevice::writeEffect(byte value, byte device) {
    writeType(E, value, device);
}

void DMXDevice::writeColor(Color color) {
    writeRed(color.r);
    writeGreen(color.g);
    writeBlue(color.b);
}

void DMXDevice::blackOut() {
    if(hasMaster) return writeMaster(0);
    writeRed(0);
    writeGreen(0);
    writeBlue(0);
    writeWhite(0);  
}

void DMXDevice::setOverrideDevices(std::vector<byte> overrideDevices) {
    _overrideDevices = overrideDevices;
}

void DMXDevice::setOutputCalculation(std::function<byte(byte, byte, byte)> outputCalculation) {
    _outputCalculation = outputCalculation;
}

void DMXDevice::setUpdate(bool update) {
    _update = update;
}

bool DMXDevice::getUpdate() {
    return _update;
}

byte DMXDevice::getChannels() {
    return formatSize;
}

byte DMXDevice::getDevices(bool includeRepeat) {
    if(includeRepeat) return _devices*_repeat;
    return _devices;
}

byte DMXDevice::getRepeat() {
    return _repeat;
}

uint64_t DMXDevice::getFormat() {
    return _format;
}

byte DMXDevice::getFormatSize(bool includeDistance) {
    return formatSize + (includeDistance ? _distance : 0);
}

byte DMXDevice::getDistance() {
    return _distance;
}

Color DMXDevice::getColor() {
    return {readType(R), readType(G), readType(B)};
}

void DMXDevice::setValueCalculation(std::vector<std::function<byte(byte)>> valueCalculation) {
    for(auto it = _inputs.begin(); it != _inputs.end(); it++)
        it->valueCalculation = valueCalculation;
}

void DMXDevice::updateChannels() {
    // vTaskDelay((DMX_CHECKCYCLE+random(DMX_READCYCLE))/portTICK_PERIOD_MS);
    for(;;) {
        vTaskDelay(DMX_READCYCLE / portTICK_PERIOD_MS /*-millis()+readcycle*/);
        /*if(millis() - readcycle < DMX_READCYCLE)
            continue;
        readcycle = millis();*/
        if(!_update) continue;
        for(auto input = _inputs.begin(); input != _inputs.end(); input++) {
            if(!READ_UNIVERSE->isHealthy()) continue;
            for(int i = 0; i < input->formatSize; i++) {
                if(INPUT_FORMAT_TYPE == X) continue;
                byte iterator = input->formatSize-1-i;
                byte value = READ_UNIVERSE->read(input->address+iterator);
                vTaskDelay(1/portTICK_PERIOD_MS);
                writeType(INPUT_FORMAT_TYPE, input->valueCalculation.size()<=iterator||input->valueCalculation[iterator]==NULL?value:(input->valueCalculation[iterator])(value));
            }
        }
    }
}

void DMXDevice::startUpdateTask(void* _this) {
    ((DMXDevice*)_this)->updateChannels();
}