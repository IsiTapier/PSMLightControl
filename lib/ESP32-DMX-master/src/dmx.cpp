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

#include "dmx.h"

uart_port_t DMX::currentUart = DEBUG?UART_NUM_1:UART_NUM_0;
DMX DMX::universe1;
DMX DMX::universe2;
DMX DMX::universe3;
DMX DMX::universe4;
RGBLed DMX::stateLed(LED_RED, LED_GREEN, LED_BLUE);

DMX::DMX() {}

DMX::DMX(DMXUniverse universe, DMXDirection direction, gpio_num_t inputPin, gpio_num_t outputPin, gpio_num_t enablePin) : _inputPin(inputPin), _outputPin(outputPin), _enablePin(enablePin) {
    if(currentUart == UART_NUM_MAX)
        return;
    uart = currentUart;
    currentUart = currentUart==UART_NUM_0?UART_NUM_1:currentUart==UART_NUM_2?UART_NUM_MAX:UART_NUM_2;
    _universe = universe;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 513; j++) {
            dmx_data[i][j] = 0;
        }
    }
    for(int j = 0; j < 513; j++) {
        // dmx_data2[j] = 0;
        dmx_temp_data[j] = 0;
    }
    initialize(direction);
}

DMX* DMX::initUniverse(DMXUniverse universe, DMXDirection direction, gpio_num_t inputPin, gpio_num_t outputPin, gpio_num_t enablePin) {
    DMX tempUniverse = DMX(universe, direction, inputPin, outputPin, enablePin);
    switch(universe) {
        case 1: universe1 = tempUniverse; return &universe1; break;
        case 2: universe2 = tempUniverse; return &universe2; break;
        case 3: universe3 = tempUniverse; return &universe3; break;
        case 4: universe4 = tempUniverse; return &universe4; break;
    }
    return NULL;
}

DMX* DMX::getUniverse(DMXUniverse universe) {
    return universe==UNIVERSE_1?&universe1:universe==UNIVERSE_2?&universe2:universe==UNIVERSE_3?&universe3:&universe4;
}

void DMX::initialize(DMXDirection direction) {
    // configure UART for DMX
    uart_config_t uart_config = {
        .baud_rate = 250000,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_2,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(uart, &uart_config);

    // Set pins for UART
    uart_set_pin(uart, _outputPin, _inputPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // install queue
    uart_driver_install(uart, BUF_SIZE * 2, BUF_SIZE * 2, 20, &dmx_rx_queue, 0);

    // create mutex for syncronisation
    sync_dmx = xSemaphoreCreateMutex();
    sync_health = xSemaphoreCreateMutex();

    // set gpio for direction
    gpio_pad_select_gpio(_enablePin);
    gpio_set_direction(_enablePin, GPIO_MODE_OUTPUT);

            // if(_universe == UNIVERSE_2) {
            // //for(int x = 0; x < 3; x++) {
            //     for(int i = 0; i < 7; i++) {
            //         dmx_data2[19+i*7] = 255;
            //         dmx_data2[20+i*7] = 255;
            //         dmx_data2[21+i*7] = 20;
            //     }
            //     for(int i = 0; i < 9; i++) {
            //         for(int j = 0; j < 36; j+=3) {
            //             dmx_data2[150+i*36+j] = 255;
            //             dmx_data2[150+i*36+j+1] = 30;
            //         }
            //     }
            //}
        // }

    // depending on parameter set gpio for direction change and start rx or tx thread
    if(direction == output) {
        gpio_set_level(_enablePin, 1);
        dmx_state = DMX_OUTPUT;

        //clear data
        // writeOff();
    
        // create send task
        xTaskCreatePinnedToCore(startSendTask, "uart_send_task", 1024, getUniverse(_universe), 12, NULL, DMX_CORE);
        // create update task
        xTaskCreatePinnedToCore(startUpdateTask, "dmx_update_task", 1024, getUniverse(_universe), 10, NULL, DMX_CORE);
    } else {
        gpio_set_level(_enablePin, 0);
        dmx_state = DMX_IDLE;

        // create receive task
        xTaskCreatePinnedToCore(startEventTask, "uart_event_task", 2048, getUniverse(_universe), 11, NULL, DMX_CORE);
        // create check task
        xTaskCreatePinnedToCore(startCheckTask, "uart_check_task", 1024, getUniverse(_universe), 1, NULL, DMX_CORE);
    }
}

uint8_t DMX::read(uint16_t channel) {
    // restrict acces to dmx array to valid values
    if(channel < 1 || channel > 512) {
        return 0;
    }

    // take data threadsafe from array and return
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    uint8_t tmp_dmx = dmx_data[2][channel];
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
    return tmp_dmx;
}

void DMX::readAll(uint8_t * data, uint16_t start, size_t size) {
    // restrict acces to dmx array to valid values
    if(start < 1 || start > 512 || start + size > 513) {
        return;
    }
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    memcpy(data, (uint8_t *)dmx_data[0] + start, size);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
}

void DMX::write(uint16_t channel, uint8_t value, bool update) {
    // restrict acces to dmx array to valid values
    if(channel < 1 || channel > 512) {
        return;
    }
    if(update) {
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    dmx_data[0][channel] = value;
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
    } else {
        xSemaphoreTake(sync_health, portMAX_DELAY);
        dmx_temp_data[channel-1] = value;
        xSemaphoreGive(sync_health);
    }
}

void DMX::writeAll(uint8_t * data, uint16_t start, size_t size) {
    // restrict acces to dmx array to valid values
    if(start < 1 || start > 512 || start + size > 513) {
        return;
    }
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    memcpy((uint8_t *)dmx_data[0] + start, data, size);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
}

void DMX::writeAll(std::vector<uint8_t> data, uint16_t start, size_t size) {
    // restrict acces to dmx array to valid values
    if(start < 1 || start > 512 || start + size > 513) {
        return;
    }
    std::vector<uint8_t>::iterator i = data.begin();
    std::vector<uint8_t>::iterator j = data.begin();
    std::advance(i, start);
    std::advance(j, start+size);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    std::copy(data.begin(), data.end(), dmx_data[0]);
   // memcpy((uint8_t *)dmx_data[(currentDmx+2)%3] + start, data, size);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
}

void DMX::writeOff() {
    for(int i = 1; i < 513; i++)
        write(i, 0);
}

uint8_t DMX::isHealthy() {
    // get timestamp of last received packet
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_health, portMAX_DELAY);
#endif
    long dmx_timeout = last_dmx_packet;
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_health);
#endif
    bool check_channel = HEALTHY_CHANNEL == -1 || read(HEALTHY_CHANNEL) != 0;
    // check if elapsed time < defined timeout
    if(xTaskGetTickCount() - dmx_timeout < HEALTHY_TIME && check_channel)
        return 1;
    return 0;
}

void DMX::uart_send_task() {
    //vTaskDelay((DMX_CHECKCYCLE+DMX_READCYCLE)/portTICK_PERIOD_MS);
    uint8_t start_code = 0x00;
    for(;;) {
        // wait till uart is ready
        uart_wait_tx_done(uart, 1000);
        // set line to inverse, creates break signal
        uart_set_line_inverse(uart, UART_INVERSE_TXD);
        // wait break time
        ets_delay_us(184);
        // disable break signal
        uart_set_line_inverse(uart,  0);
        // wait mark after break
        ets_delay_us(24);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
    memcpy((uint8_t *)dmx_temp_copy+1, (uint8_t *)dmx_data[0]+1, 512);
#if !DMX_IGNORE_THREADSAFETY
    xSemaphoreGive(sync_dmx);
#endif
        // write start code
        uart_write_bytes(uart, (const char*) &start_code, 1);
        // transmit the dmx data
        // xSemaphoreTake(sync_dmx, portMAX_DELAY);
        uart_write_bytes(uart, (const char*) dmx_temp_copy+1, 512);
        // xSemaphoreGive(sync_dmx);
    }
}

void DMX::uart_event_task() {
    uart_event_t event;
    uint8_t* dtmp = (uint8_t*) malloc(BUF_SIZE);
    bool state = false;
    for(;;) {
         // wait for data in the dmx_queue
        if(xQueueReceive(dmx_rx_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
            bzero(dtmp, BUF_SIZE);
            switch(event.type) {
                case UART_DATA:
                    // read the received data
                    uart_read_bytes(uart, dtmp, event.size, portMAX_DELAY);
                    // check if break detected
                    if(dmx_state == DMX_BREAK) {
                        // if not 0, then RDM or custom protocol
                        if(dtmp[0] == 0) {
                            dmx_state = DMX_DATA;
                            // reset dmx adress to 0
                            current_rx_addr = 0;
                            state = !state;
                            vTaskDelay(1);
#if !DMX_IGNORE_THREADSAFETY
                            xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
                            byte jumps = 0;
                            for(int i = 1; i < 513 && jumps < 2; i++)
                                if(dmx_data[0][i]!=dmx_data[1][i]&&(dmx_data[0][i]==0||dmx_data[1][i]==0||dmx_data[0][i]==230||dmx_data[1][i]==230))
                                    jumps++;
                            if(jumps < 1)
                                memcpy((uint8_t *)dmx_data[2]+1, (uint8_t *)dmx_data[!state]+1, 512);

#if !DMX_IGNORE_THREADSAFETY
                            xSemaphoreGive(sync_dmx);
#endif

#if !DMX_IGNORE_THREADSAFETY
                            xSemaphoreTake(sync_health, portMAX_DELAY);
#endif
                            // store received timestamp
                            last_dmx_packet = xTaskGetTickCount();
#if !DMX_IGNORE_THREADSAFETY
                            xSemaphoreGive(sync_health);
#endif
                        }
                    }
                    // check if in data receive mode
                    if(dmx_state == DMX_DATA) {
#if !DMX_IGNORE_THREADSAFETY
                        xSemaphoreTake(sync_dmx, portMAX_DELAY);
#endif
                        // copy received bytes to dmx data array
                        for(int i = 0; i < event.size; i++) {
                            if(current_rx_addr < 513) {
                                // if(dmx_data[2][current_rx_addr]!=dtmp[i]) {
                                //     Serial.print(current_rx_addr);
                                //     Serial.print(" ");
                                //     Serial.println(dtmp[i]);
                                // }
                                dmx_data[state][current_rx_addr++] = dtmp[i];
                                // current_rx_addr++;
                            }
                        }
#if !DMX_IGNORE_THREADSAFETY
                        xSemaphoreGive(sync_dmx);
#endif
                    }
                    break;
                case UART_BREAK:
                    // break detected
                    // clear queue und flush received bytes
                    uart_flush_input(uart);
                    xQueueReset(dmx_rx_queue);
                    dmx_state = DMX_BREAK;
                    break;
                case UART_FRAME_ERR:
                case UART_PARITY_ERR:
                case UART_BUFFER_FULL:
                case UART_FIFO_OVF:
                default:
                    // error recevied, going to idle mode
                    uart_flush_input(uart);
                    xQueueReset(dmx_rx_queue);
                    dmx_state = DMX_IDLE;
                    break;
            }
        }
    }
}

void DMX::uart_check_task() {
    for(;;) {
        vTaskDelay(DMX_CHECKCYCLE/portTICK_PERIOD_MS);
        if(isHealthy())
            stateLed.writeRGB(0, 255, 0);
        else
            stateLed.writeRGB(255, 0, 0);
    }
}

void DMX::dmx_update_task() {
    for(;;) {
        vTaskDelay(DMX_UPDATE_CYCLE);
        xSemaphoreTake(sync_health, 1000);
        writeAll(dmx_temp_data);
        xSemaphoreGive(sync_health);
    }
}

void DMX::startEventTask(void *_this) {
    ((DMX*)_this)->uart_event_task();
}

void DMX::startSendTask(void *_this) {
    ((DMX*)_this)->uart_send_task();
}

void DMX::startCheckTask(void *_this) {
    ((DMX*)_this)->uart_check_task();
}

void DMX::startUpdateTask(void *_this) {
    ((DMX*)_this)->dmx_update_task();
}
