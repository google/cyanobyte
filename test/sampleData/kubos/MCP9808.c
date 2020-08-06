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
* Auto-generated file for MCP9808 v0.1.0.
* Generated from peripherals/MCP9808.yaml using Cyanobyte Codegen v0.1.0
* Class for MCP9808
* This is a test description

*/




#include "MCP9808.h"

#define REGISTER_CONFIGURATION 1

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
static deviceAddress_t DEVICE_ADDRESS;

int mcp9808_init(deviceAddress_t address, char* bus_name) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void mcp9808_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int mcp9808_readconfiguration(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int mcp9808_writeconfiguration(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIGURATION };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}
int mcp9808_get_limithysteresis(uint16_t* val) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000011000000000;
    // Bitshift value
    val = val >> 9;
    return 0;
}
int mcp9808_get_shutdownmode(uint16_t* val) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000100000000;
    // Bitshift value
    val = val >> 8;
    return 0;
}

