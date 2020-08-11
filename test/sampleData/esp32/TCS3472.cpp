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

TCS3472::TCS3472(TwoWire& wire) :
    _wire(&wire)
{
}

void TCS3472::begin() {
    _wire->begin();
    _lifecycleBegin();
}


uint16_t TCS3472::readblue() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_BLUE);
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


uint16_t TCS3472::readclear() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_CLEAR);
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


uint8_t TCS3472::readenable() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_ENABLE);
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

int TCS3472::writeenable(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_ENABLE };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint16_t TCS3472::readgreen() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_GREEN);
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


uint16_t TCS3472::readred() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_RED);
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



uint8_t TCS3472::getinit() {
    // Read register data
    // '#/registers/enable' > 'enable'
    uint8_t val = readenable();
    // Mask register value
    val = val & 0b0000000011111111;
    return val;
}

int TCS3472::setinit(uint8_t data) {
    // Read current register data
    // '#/registers/enable' > 'enable'
    uint8_t register_data = readenable();
    register_data = register_data | data;
    return writeenable(register_data);
}

void TCS3472::_lifecycleBegin() {
    char enables; // Variable declaration


    enables = (1+2);
    writeenable(enables);


}

