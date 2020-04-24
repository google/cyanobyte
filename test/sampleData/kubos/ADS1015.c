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
* Auto-generated file for ADS1015 v0.1.0.
* Generated from peripherals/ADS1015.yaml using Cyanobyte Codegen v0.1.0
* Class for ADS1015
* Texas Instruments Analog-Digital Converter

*/


short _swap_endian(val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}


#include "ADS1015.h"
#define DEVICE_ADDRESS 73

#define REGISTER_CONFIG 1
#define REGISTER_CONVERSION 0

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int ads1015_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void ads1015_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int ads1015_readConfig(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int ads1015_writeConfig(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIG };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}int ads1015_readConversion(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}



int ads1015_set_deviceoperatingmode(uint16_t* data) {
    // Bitshift value
    data = data << 8;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

int ads1015_set_programmablegain(uint16_t* data) {
    // Bitshift value
    data = data << 9;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

int ads1015_set_samplerate(uint16_t* data) {
    // Bitshift value
    data = data << 5;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void ads1015_analog_read(short* val, char channel) {
    short config; // Variable declaration
    char datumA; // Variable declaration
    char datumB; // Variable declaration
    short processed; // Variable declaration
    short programmableGain; // Variable declaration
    short raw; // Variable declaration


    ads1015_readConfig(&config);
    config = (config|(channel << 12));
    config = (config|32768);
    ads1015_writeConfig(&config);
    ads1015_readConversion(&raw);
    datumA = (raw&65280);
    datumA = (datumA >> 8);
    datumB = (raw&255);
    processed = ((datumA << 4)|(datumB >> 4));
    programmableGain = 6144
    processed = ((processed/2047/1000)*programmableGain);


    val = processed;
}

