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


short _swap_endian(val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}


#include "MCP4725.h"
#define DEVICE_ADDRESS 98

#define REGISTER_EEPROM 96
#define REGISTER_VOUT 64

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int mcp4725_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void mcp4725_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int mcp4725_readEEPROM(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int mcp4725_writeEEPROM(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_EEPROM };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}int mcp4725_readVOut(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int mcp4725_writeVOut(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_VOUT };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}
int mcp4725_get_digitalout(uint16_t* val) {
    // Read register data
    // '#/registers/EEPROM' > 'EEPROM'
    int result = mcp4725_readEEPROM(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0001111111111111;
    return 0;
}

int mcp4725_set_digitalout(uint16_t* data) {
    // Read current register data
    // '#/registers/EEPROM' > 'EEPROM'
    uint16_t register_data;
    int result = mcp4725_readEEPROM(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = mcp4725_writeEEPROM(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void mcp4725_getvout_asvoltage(float* val, float vcc) {
    float voltage; // Variable declaration


    // Read value of register into a variable
    value = mcp4725_get_EEPROM(val);
    voltage = value / 4096 * vcc


    val = voltage;
}

void mcp4725_setvout_asvoltage( float output, float vcc) {


    output = output / vcc * 4096
    mcp4725_writeEEPROM(&output);


}

