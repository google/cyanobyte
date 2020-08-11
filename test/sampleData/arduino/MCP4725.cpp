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

MCP4725::MCP4725(TwoWire& wire) :
    _wire(&wire)
{
}

void MCP4725::begin() {
    _wire->begin();
}

void MCP4725::end() {
    _wire->end();
}

uint16_t MCP4725::readEEPROM() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_EEPROM);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 1) != 1) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int MCP4725::writeEEPROM(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_EEPROM };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint16_t MCP4725::readVOut() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_VOUT);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 1) != 1) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int MCP4725::writeVOut(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_VOUT };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


uint16_t MCP4725::getdigitalOut() {
    // Read register data
    // '#/registers/EEPROM' > 'EEPROM'
    uint8_t val = readEEPROM();
    // Mask register value
    val = val & 0b0001111111111111;
    return val;
}

int MCP4725::setdigitalOut(uint8_t data) {
    // Read current register data
    // '#/registers/EEPROM' > 'EEPROM'
    uint8_t register_data = readEEPROM();
    register_data = register_data | data;
    return writeEEPROM(register_data);
}

float MCP4725::getVOutasVoltage(float vcc) {
    float voltage; // Variable declaration


    // Read value of register into a variable
    float value = readEEPROM();
    voltage = value / 4096 * vcc;


    return voltage;
}

void MCP4725::setVOutasVoltage(float output, float vcc) {


    output = output / vcc * 4096;
    writeEEPROM(output);


}

