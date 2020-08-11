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

MCP9808::MCP9808(TwoWire& wire, deviceAddress_t address) :
    _wire(&wire),
    DEVICE_ADDRESS ( address )
{
}

void MCP9808::begin() {
    _wire->begin();
}

void MCP9808::end() {
    _wire->end();
}

uint16_t MCP9808::readconfiguration() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_CONFIGURATION);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 2) != 2) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int MCP9808::writeconfiguration(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIGURATION };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


uint16_t MCP9808::getlimitHysteresis() {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    uint8_t val = readconfiguration();
    // Mask register value
    val = val & 0b0000011000000000;
    // Bitshift value
    val = val >> 9;
    return val;
}
uint16_t MCP9808::getshutdownMode() {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    uint8_t val = readconfiguration();
    // Mask register value
    val = val & 0b0000000100000000;
    // Bitshift value
    val = val >> 8;
    return val;
}

