/*
 DMXDevice.cpp - DMXDevice-Library for Librarys.
*/

#include "DMXDevice.h"

std::vector<DMXDevice*> DMXDevice::devices = {};

DMXDevice::DMXDevice() {}

DMXDevice::DMXDevice(DMXDevice *device, DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> inputs, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), _inputs(inputs), writeUniverse(DMX::getUniverse(universe)) {
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
    
    std::vector<Input> __inputs;
    for(Input input : _inputs) {
        input.formatSize = floor(logn((double)16, (double)input.format)+1);
        if(!hasMaster)
            for(int i = 0; i < input.formatSize; i++)
                if(INPUT_FORMAT_TYPE == M) {
                    virtualMaster = input.address+input.formatSize-i-1;
                    virtualMasterUniverse = READ_UNIVERSE;
                    break;
                }
        if(input.address > 513-input.formatSize)
            input.address = 513-input.formatSize;
        if(input.address < 1)
            input.address = 1;
        __inputs.push_back(input);
    }
    _inputs = __inputs;
    
    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 1024, device, 7, NULL);
}

DMXDevice::DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, std::vector<Input> inputs, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), _inputs(inputs), writeUniverse(DMX::getUniverse(universe)) {
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

    std::vector<Input> __inputs;
    for(Input input : _inputs) {
        input.formatSize = floor(logn((double)16, (double)input.format)+1);
        if(!hasMaster)
            for(int i = 0; i < input.formatSize; i++)
                if(INPUT_FORMAT_TYPE == M) {
                    virtualMaster = input.address+input.formatSize-i-1;
                    virtualMasterUniverse = READ_UNIVERSE;
                    break;
                }
        if(input.address > 513-input.formatSize)
            input.address = 513-input.formatSize;
        if(input.address < 1)
            input.address = 1;
        __inputs.push_back(input);
    }    
    _inputs = __inputs;

    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 1024, this, 9, NULL);
}

DMXDevice::DMXDevice(DMXUniverse universe, uint16_t address, uint64_t format, DMXUniverse inputUniverse, uint16_t inputAddress, uint64_t inputFormat, byte repeat, byte devices, byte distance) : _universe(universe), _address(address), _format(format), _repeat(repeat), _devices(devices), _distance(distance), writeUniverse(DMX::getUniverse(universe)) {
    Input i; i.universe=inputUniverse; i.address=inputAddress; i.format=inputFormat; i.valueCalculation = {};
    _inputs.push_back(i);
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

    std::vector<Input> __inputs;
    for(Input input : _inputs) {
        input.formatSize = floor(logn((double)16, (double)input.format)+1);
        if(!hasMaster)
            for(int i = 0; i < input.formatSize; i++)
                if(INPUT_FORMAT_TYPE == M) {
                    virtualMaster = input.address+input.formatSize-i-1;
                    virtualMasterUniverse = READ_UNIVERSE;
                    break;
                }
        if(input.address > 513-input.formatSize)
            input.address = 513-input.formatSize;
        if(input.address < 1)
            input.address = 1;
        __inputs.push_back(input);
    }
    _inputs = __inputs;
    // DMXDevice::devices.push_back(device);
    xTaskCreate(startUpdateTask, "updateChannels", 1024, this, 9, NULL);
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

void DMXDevice::init() {
    // xTaskCreate(startUpdateTask, "updateChannels", 1024, NULL, 9, NULL);
}

void DMXDevice::writeChannel(byte channel, byte value, byte device, bool update) {
    if(channel >= formatSize*_repeat)
        return;
    if(device != UINT8_MAX) {
        writeUniverse->write(_address+channel+(min(device, _devices)-1)*(_repeat*formatSize+_distance), value, update);
        return;
    }
    for(int i = 0; i < _devices; i++)
        writeUniverse->write(_address+channel+i*(_repeat*formatSize+_distance), value, update);
}

// void DMXDevice::writeChannels(int channel, byte value, bool update) {
//     if(channel >= (formatSize*_repeat+_distance)*_devices)
//         return;
//     writeUniverse->write(_address+channel, value, update);
// }

void DMXDevice::writeType(byte type, byte value, bool update) {
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
                writeChannel(j*formatSize-1-i, value, update);
}

void DMXDevice::writeMaster(byte value, bool update) {
    writeType(M, value, update);
    if(virtualMaster < 0) return;
    virtualMasterUniverse->write(virtualMaster, value, update);
}

void DMXDevice::writeRed(byte value, bool update) {
    writeType(R, value, update);
}

void DMXDevice::writeGreen(byte value, bool update) {
    writeType(G, value, update);
}

void DMXDevice::writeBlue(byte value, bool update) {
    writeType(B, value, update);
}

void DMXDevice::writeWhite(byte value, bool update) {
    writeType(W, value, update);
}

void DMXDevice::writeStrobe(byte value, bool update) {
    writeType(S, value, update);
}

void DMXDevice::writeEffect(byte value, bool update) {
    writeType(E, value, update);
}

void DMXDevice::blackOut() {
    if(hasMaster) return writeMaster(0);
    writeRed(0);
    writeGreen(0);
    writeBlue(0);
    writeWhite(0);  
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

void DMXDevice::updateChannels() {
    // vTaskDelay((DMX_CHECKCYCLE+random(DMX_READCYCLE))/portTICK_PERIOD_MS);
    for(;;) {
        vTaskDelay(DMX_READCYCLE / portTICK_PERIOD_MS /*-millis()+readcycle*/);
        /*if(millis() - readcycle < DMX_READCYCLE)
            continue;
        readcycle = millis();*/
        if(!_update)
            continue;
        for(Input input : _inputs) {
            if(!READ_UNIVERSE->isHealthy())
                continue;
            for(int i = 0; i < input.formatSize; i++) {
                if(INPUT_FORMAT_TYPE == X)
                    continue;
                byte iterator = input.formatSize-1-i;
                byte value = READ_UNIVERSE->read(input.address+iterator);
                vTaskDelay(1/portTICK_PERIOD_MS);
                writeType(INPUT_FORMAT_TYPE, input.valueCalculation.size()<=iterator||input.valueCalculation[iterator]==NULL?value:(input.valueCalculation[iterator])(value));
            }
        }
    }
}

void DMXDevice::startUpdateTask(void* _this) {
    ((DMXDevice*)_this)->updateChannels();
    // for(;;) {
    //     if(!devices[0]->readUniverse->isHealthy()) {
    //         vTaskDelay(100);
    //         continue;
    //     }
    //     if(devices.size()!=8) {
    //         vTaskDelay(100);
    //         continue;
    //     }
    //     for(DMXDevice* device : devices) {
    //         vTaskDelay(DMX_READCYCLE / portTICK_PERIOD_MS / devices.size());
    //         device->updateChannels();
    //     }
    // }
}