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

ADS1015::ADS1015(TwoWire& wire) :
    _wire(&wire)
{
}

void ADS1015::begin() {
    _wire->begin();
}

void ADS1015::end() {
    _wire->end();
}

uint16_t ADS1015::readConfig() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_CONFIG);
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

int ADS1015::writeConfig(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIG };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint16_t ADS1015::readConversion() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_CONVERSION);
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




int ADS1015::setDeviceOperatingMode(uint8_t data) {
    // Bitshift value
    data = data << 8;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint8_t register_data = readConfig();
    register_data = register_data | data;
    return writeConfig(register_data);
}

int ADS1015::setProgrammableGain(uint8_t data) {
    // Bitshift value
    data = data << 9;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint8_t register_data = readConfig();
    register_data = register_data | data;
    return writeConfig(register_data);
}

int ADS1015::setSampleRate(uint8_t data) {
    // Bitshift value
    data = data << 5;
    // Read current register data
    // '#/registers/Config' > 'Config'
    uint8_t register_data = readConfig();
    register_data = register_data | data;
    return writeConfig(register_data);
}

short ADS1015::analogread(char channel) {
    short config; // Variable declaration
    char datumA; // Variable declaration
    char datumB; // Variable declaration
    short processed; // Variable declaration
    short programmableGain; // Variable declaration
    short raw; // Variable declaration


    config = readConfig();
    config = (config|(channel << 12));
    config = (config|32768);
    writeConfig(config);
    raw = readConversion();
    datumA = (raw&65280);
    datumA = (datumA >> 8);
    datumB = (raw&255);
    processed = ((datumA << 4)|(datumB >> 4));
    programmableGain = 6144;
    processed = ((processed/2047/1000)*programmableGain);


    return processed;
}

