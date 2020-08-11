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

// Provide an I2C connect function, return status
static deviceAddress_t DEVICE_ADDRESS;

int mcp9808_init(deviceAddress_t address, int (*connect)(uint8_t)) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int mcp9808_readconfiguration(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_CONFIGURATION, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int mcp9808_writeconfiguration(
    uint16_t* data,
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONFIGURATION, data, 2) != 0) {
        return -1;
    }
    return 0;
}
int mcp9808_get_limithysteresis(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000011000000000;
    // Bitshift value
    val = val >> 9;
    return 0;
}
int mcp9808_get_shutdownmode(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000100000000;
    // Bitshift value
    val = val >> 8;
    return 0;
}

