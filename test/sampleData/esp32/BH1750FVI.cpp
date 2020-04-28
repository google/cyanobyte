/*
* Copyright (C) 2020 Google Inc.
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
* Auto-generated file for BH1750FVI v0.1.0.
* Generated from peripherals/BH1750FVI.yaml using Cyanobyte Codegen v0.1.0
* Class for BH1750FVI
* Rohm Light Sensor

*/




#include "BH1750FVI.h"

#define REGISTER_CONTINUOUSHRES2MODE 17
#define REGISTER_CONTINUOUSHRESMODE 16
#define REGISTER_CONTINUOUSLYLRESMODE 19
#define REGISTER_ONCEHRES2MODE 33
#define REGISTER_ONCEHRESMODE 32
#define REGISTER_ONCELRESMODE 35
#define REGISTER_POWERDOWN 0
#define REGISTER_POWERON 1
#define REGISTER_RESET 7

BH1750FVI::BH1750FVI(TwoWire& wire, deviceAddress_t address) :
    _wire(&wire),
    DEVICE_ADDRESS ( address )
{
}

void BH1750FVI::begin() {
    _wire->begin();
    _lifecycleBegin();
}



int BH1750FVI::writeContinuousHRes2Mode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSHRES2MODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeContinuousHResMode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSHRESMODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeContinuouslyLResMode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_CONTINUOUSLYLRESMODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeOnceHRes2Mode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCEHRES2MODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeOnceHResMode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCEHRESMODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeOnceLResMode() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_ONCELRESMODE };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writePowerDown() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_POWERDOWN };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writePowerOn() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_POWERON };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


int BH1750FVI::writeReset() {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_RESET };
    _wire->write(buffer, 1);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}



void BH1750FVI::_lifecycleBegin() {


    writePowerOn();


}

void BH1750FVI::commandPowerDown() {


    writePowerDown();


}

void BH1750FVI::commandReset() {


    writePowerOn();
    writeReset();


}

uint16_t BH1750FVI::readLightIntensity() {
    uint16_t intensity; // Variable declaration


    uint8_t _datum;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->requestFrom(DEVICE_ADDRESS, 2);
    _datum = _wire->read();
    intensity = intensity << 8 | _datum;
    _datum = _wire->read();
    intensity = intensity << 8 | _datum;


    return intensity;
}

