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


static short _swap_endian(short val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}


#include "ADS1015.h"
#define DEVICE_ADDRESS 73

#define REGISTER_CONFIG 1
#define REGISTER_CONVERSION 0

// Provide an I2C connect function, return status
int ads1015_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int ads1015_readConfig(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_CONFIG, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int ads1015_writeConfig(
    uint16_t* data,
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONFIG, data, 2) != 0) {
        return -1;
    }
    return 0;
}int ads1015_readConversion(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_CONVERSION, val, 2) != 0) {
        return -2;
    }
    return 0;
}



int ads1015_set_deviceoperatingmode(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Bitshift value
    data = data << 8;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

int ads1015_set_programmablegain(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Bitshift value
    data = data << 9;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

int ads1015_set_samplerate(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Bitshift value
    data = data << 5;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint16_t register_data;
    int result = ads1015_readConfig(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = ads1015_writeConfig(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void ads1015_analog_read(
    short* val,
    char channel,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    short config; // Variable declaration
    char datumA; // Variable declaration
    char datumB; // Variable declaration
    short processed; // Variable declaration
    short programmableGain; // Variable declaration
    short raw; // Variable declaration


    ads1015_readConfig(&config, read);
    config = (config|(channel << 12));
    config = (config|32768);
    ads1015_writeConfig(&config, write);
    ads1015_readConversion(&raw, read);
    datumA = (raw&65280);
    datumA = (datumA >> 8);
    datumB = (raw&255);
    processed = ((datumA << 4)|(datumB >> 4));
    programmableGain = 6144
    processed = ((processed/2047/1000)*programmableGain);


    *val = processed;
}

