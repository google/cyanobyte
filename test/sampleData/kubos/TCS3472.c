/*
* Copyright (C) 2019 Google Inc.
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
* Auto-generated file for TCS3472 v0.1.0.
* Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
* Class for TCS3472
* Color Light-to-Digital Converter with IR Filter

*/




#include "TCS3472.h"
#define DEVICE_ADDRESS 41

#define REGISTER_BLUE 186
#define REGISTER_CLEAR 180
#define REGISTER_ENABLE 128
#define REGISTER_GREEN 184
#define REGISTER_RED 182

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int tcs3472_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
    tcs3472__lifecycle_begin();
}

void tcs3472_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int tcs3472_readblue(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int tcs3472_readclear(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int tcs3472_readenable(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int tcs3472_writeenable(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_ENABLE };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}int tcs3472_readgreen(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int tcs3472_readred(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}


int tcs3472_get_init(uint8_t* val) {
    // Read register data
    // '#/registers/enable' > 'enable'
    int result = tcs3472_readenable(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000011111111;
    return 0;
}

int tcs3472_set_init(uint8_t* data) {
    // Read current register data
    // '#/registers/enable' > 'enable'
    uint8_t register_data;
    int result = tcs3472_readenable(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = tcs3472_writeenable(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void tcs3472__lifecycle_begin() {
    char enables; // Variable declaration


    enables = (1+2);
    tcs3472_writeenable(&enables);


}

