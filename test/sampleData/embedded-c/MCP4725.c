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
* Auto-generated file for MCP4725 v0.1.0.
* Generated from peripherals/MCP4725.yaml using Cyanobyte Codegen v0.1.0
* Class for MCP4725
* Microchip 4725 Digital-to-Analog Converter

*/


static short _swap_endian(short val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}


#include "MCP4725.h"
#define DEVICE_ADDRESS 98

#define REGISTER_EEPROM 96
#define REGISTER_VOUT 64

// Provide an I2C connect function, return status
int mcp4725_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int mcp4725_readEEPROM(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_EEPROM, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int mcp4725_writeEEPROM(
    uint16_t* data,
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_EEPROM, data, 1) != 0) {
        return -1;
    }
    return 0;
}int mcp4725_readVOut(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_VOUT, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int mcp4725_writeVOut(
    uint16_t* data,
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_VOUT, data, 1) != 0) {
        return -1;
    }
    return 0;
}
int mcp4725_get_digitalout(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/EEPROM' > 'EEPROM'
    int result = mcp4725_readEEPROM(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0001111111111111;
    return 0;
}

int mcp4725_set_digitalout(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read current register data
    // '#/registers/EEPROM' > 'EEPROM'
    uint16_t register_data;
    int result = mcp4725_readEEPROM(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = mcp4725_writeEEPROM(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void mcp4725_getvout_asvoltage(
    float* val,
    float vcc
) {
    float voltage; // Variable declaration


    voltage = value / 4096 * vcc


    *val = voltage;
}

void mcp4725_setvout_asvoltage(
    float output, float vcc,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {


    output = output / vcc * 4096
    mcp4725_writeEEPROM(&output, write);


}

