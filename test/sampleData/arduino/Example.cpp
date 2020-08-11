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
* Auto-generated file for Example v0.1.0.
* Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
* Class for Example
* Example of a package

*/




#include "Example.h"

#define REGISTER_REGISTERA 0
#define REGISTER_REGISTERB 1
#define REGISTER_REGISTERC 2
#define REGISTER_REGISTERD 3

Example::Example(TwoWire& wire, deviceAddress_t address) :
    _wire(&wire),
    DEVICE_ADDRESS ( address )
{
}

void Example::begin() {
    _wire->begin();
    _lifecycleBegin();
}

void Example::end() {
    _wire->end();
    _lifecycleEnd();
}

uint8_t Example::readRegisterA() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_REGISTERA);
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

int Example::writeRegisterA(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_REGISTERA };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint16_t Example::readRegisterB() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_REGISTERB);
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

int Example::writeRegisterB(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_REGISTERB };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint32_t Example::readRegisterC() {
    uint8_t datum;
    uint32_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_REGISTERC);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 4) != 4) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int Example::writeRegisterC(uint32_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[5] = { (uint8_t) REGISTER_REGISTERC };
    buffer[1] = (data >> 24) & 0xFF;
    buffer[2] = (data >> 16) & 0xFF;
    buffer[3] = (data >> 8) & 0xFF;
    buffer[4] = (data >> 0) & 0xFF;
    _wire->write(buffer, 5);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint8_t Example::readRegisterD() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_REGISTERD);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 0) != 0) {
        return 0;
    }


    return value;
}

int Example::writeRegisterD() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_REGISTERD };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


uint8_t Example::getFieldA() {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t val = readRegisterA();
    // Mask register value
    val = val & 0b0000000011110000;
    // Bitshift value
    val = val >> 4;
    return val;
}

int Example::setFieldB(uint8_t data) {
    // Bitshift value
    data = data << 2;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data = readRegisterA();
    register_data = register_data | data;
    return writeRegisterA(register_data);
}
uint8_t Example::getFieldC() {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t val = readRegisterA();
    // Mask register value
    val = val & 0b0000000000000010;
    // Bitshift value
    val = val >> 1;
    return val;
}

int Example::setFieldC(uint8_t data) {
    // Bitshift value
    data = data << 1;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data = readRegisterA();
    register_data = register_data | data;
    return writeRegisterA(register_data);
}

char Example::_lifecycleBegin() {
    char output; // Variable declaration


    output = 1;
    writeRegisterA(output);


    return output;
}

char Example::_lifecycleEnd() {
    char output; // Variable declaration


    output = 1;
    writeRegisterA(output);


    return output;
}

void Example::ReturnArray(short * returnArray) {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


    returnArray[0] = summation;
    returnArray[1] = summation;
}

short Example::ReturnNumber() {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


    return summation;
}

void Example::ReturnVoid() {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


}

