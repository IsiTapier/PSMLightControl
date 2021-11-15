/* 
 * This file is part of the ESP32-DMX distribution (https://github.com/luksal/ESP32-DMX).
 * Copyright (c) 2021 Lukas Salomon.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>
#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"

#include "rgbLED.h"
#include "../../src/Pins.h"
#include "../../src/Settings.h"

#ifndef DMX_h
#define DMX_h

enum DMXDirection { input, output };
enum DMXState { DMX_IDLE, DMX_BREAK, DMX_DATA, DMX_OUTPUT };
enum DMXUniverse { UNIVERSE_1 = 1, UNIVERSE_2 = 2, UNIVERSE_3 = 3, UNIVERSE_4 = 4 };

#define SERIAL_ACTIVE           DEBUG       // use serial connection
#define INACTIVE_UNIVERSE       2           // chose inactive universe while serial on

#define HEALTHY_TIME            500         // timeout in ms
#define HEALTHY_CHANNEL         -1          // needs to be none zero
#define BUF_SIZE                1024        // buffer size for rx events
#define DMX_CORE                1           // select the core the rx/tx thread should run on
#define DMX_IGNORE_THREADSAFETY 0           // set to 1 to disable all threadsafe mechanisms
#define DMX_READCYCLE           100
#define DMX_CHECKCYCLE          1*1000

class DMX {
    public:

        static DMX* initUniverse(DMXUniverse universe, DMXDirection direction, gpio_num_t inputPin, gpio_num_t outputPin, gpio_num_t enablePin);

        static DMX* getUniverse(DMXUniverse universe);
        
        uint8_t read(uint16_t channel);              // returns the dmx value for the givven address (values from 1 to 512)

        void readAll(uint8_t * data, uint16_t start = 1, size_t size = 512);   // copies the defined channels from the read buffer

        void write(uint16_t channel, uint8_t value = 255); // writes the dmx value to the buffer
        
        void writeAll(uint8_t * data, uint16_t start = 1, size_t size = 512);  // copies the defined channels into the write buffer

        void writeOff();

        uint8_t isHealthy();                            // returns true, when a valid DMX signal was received within the last 500ms
              
    private:

        static uart_port_t currentUart;

        gpio_num_t _inputPin;

        gpio_num_t _outputPin;

        gpio_num_t _enablePin;

        uart_port_t uart;

        QueueHandle_t dmx_rx_queue;                  // queue for uart rx events
            
        SemaphoreHandle_t sync_dmx;                  // semaphore for syncronising access to dmx array

        DMXState dmx_state = DMX_IDLE;               // status, in which recevied state we are

        uint16_t current_rx_addr = 0;                // last received dmx channel

        long last_dmx_packet = 0;                    // timestamp for the last received packet
            
        uint8_t dmx_data[513];                       // stores the received dmx data

        static DMX universe1;

        static DMX universe2;

        static DMX universe3;

        static DMX universe4;

        static RGBLed stateLed;

        DMX();

        DMX(DMXUniverse universe, DMXDirection direction, gpio_num_t inputPin, gpio_num_t outputPin, gpio_num_t enablePin);

        void initialize(DMXUniverse universe, DMXDirection direction);     // initialize library

        void uart_event_task();     // event task

        void uart_send_task();      // transmit task

        void uart_check_task();     // checks uart connection

        static void startEventTask(void *_this);

        static void startSendTask(void *_this);

        static void startCheckTask(void *_this);

};

#endif