/*
* Copyright (C) 2020 Google Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Auto-generated file for BH1750FVI v0.1.0.
* Generated from peripherals/BH1750FVI.yaml using Cyanobyte Codegen v0.1.0
* Class for BH1750FVI
* Rohm Light Sensor

*/




#include "BH1750FVI.h"

#define REGISTER_CONTINUOUSHRES2MODE 17
#define REGISTER_CONTINUOUSHRESMODE 16
#define REGISTER_CONTINUOUSLYLRESMODE 19
#define REGISTER_ONCEHRES2MODE 33
#define REGISTER_ONCEHRESMODE 32
#define REGISTER_ONCELRESMODE 35
#define REGISTER_POWERDOWN 0
#define REGISTER_POWERON 1
#define REGISTER_RESET 7

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
static deviceAddress_t DEVICE_ADDRESS;

int bh1750fvi_init(deviceAddress_t address, char* bus_name) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
    bh1750fvi__lifecycle_begin();
}

void bh1750fvi_terminate() {
    k_i2c_terminate(&i2c_bus);
}


int bh1750fvi_writeContinuousHRes2Mode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSHRES2MODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeContinuousHResMode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSHRESMODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeContinuouslyLResMode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSLYLRESMODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceHRes2Mode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCEHRES2MODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceHResMode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCEHRESMODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceLResMode() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCELRESMODE };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writePowerDown() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_POWERDOWN };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writePowerOn() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_POWERON };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeReset() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_RESET };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}

void bh1750fvi__lifecycle_begin() {


    bh1750fvi_writePowerOn();


}

void bh1750fvi_command_powerdown() {


    bh1750fvi_writePowerDown();


}

void bh1750fvi_command_reset() {


    bh1750fvi_writePowerOn();
    bh1750fvi_writeReset();


}

void bh1750fvi_read_lightintensity(uint16_t* val) {
    uint16_t intensity; // Variable declaration


    k_i2c_read(i2c_bus, DEVICE_ADDRESS, intensity, 2);


    val = intensity;
}

