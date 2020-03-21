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
* Auto-generated file for BMP280 v0.1.0.
* Generated from peripherals/BMP280.yaml using Cyanobyte Codegen v0.1.0
* Class for BMP280
* Bosch Digital Pressure Sensor

*/



static short _sign(short val, char length) {
    // Convert unsigned integer to signed integer
    if (val & (1 << (length - 1))) {
        return val - (1 << length);
    }
    return val;
}

#include "BMP280.h"
#define DEVICE_ADDRESS 119

#define REGISTER_DIGP1 142
#define REGISTER_DIGP2 144
#define REGISTER_DIGP3 146
#define REGISTER_DIGP4 148
#define REGISTER_DIGP5 150
#define REGISTER_DIGP6 152
#define REGISTER_DIGP7 154
#define REGISTER_DIGP8 156
#define REGISTER_DIGP9 158
#define REGISTER_DIGT1 136
#define REGISTER_DIGT2 138
#define REGISTER_DIGT3 140
#define REGISTER_PRESSURELSB 248
#define REGISTER_PRESSUREMSB 247
#define REGISTER_PRESSUREXLSB 249
#define REGISTER_TEMPLSB 251
#define REGISTER_TEMPMSB 250
#define REGISTER_TEMPXLSB 252

BMP280::BMP280(TwoWire& wire) :
    _wire(&wire)
{
}

void BMP280::begin() {
    _wire->begin();
}

void BMP280::end() {
    _wire->end();
}

uint16_t BMP280::readDigP1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP1);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP1(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP1 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP2);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP2(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP2 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP3() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP3);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP3(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP3 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP4() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP4);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP4(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP4 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP5() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP5);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP5(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP5 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP6() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP6);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP6(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP6 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP7() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP7);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP7(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP7 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP8() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP8);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP8(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP8 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigP9() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP9);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigP9(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP9 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigT1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT1);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigT1(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT1 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigT2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT2);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigT2(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT2 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint16_t BMP280::readDigT3() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT3);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;
    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeDigT3(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT3 };
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readPressureLsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURELSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writePressureLsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSURELSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readPressureMsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSUREMSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writePressureMsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSUREMSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readPressureXlsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSUREXLSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writePressureXlsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSUREXLSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readTempLsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPLSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeTempLsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPLSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readTempMsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPMSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeTempMsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPMSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}uint8_t BMP280::readTempXlsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPXLSB);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 8) != 8) {
        return 0;
    }

    datum = _wire->read();
    value = value << 8 | datum;

    return value;
}

int BMP280::writeTempXlsb(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPXLSB };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

float BMP280::pressureasHpa() {
    float hpa; // Variable declaration
    short rawComp1; // Variable declaration
    short rawComp2; // Variable declaration
    short rawComp3; // Variable declaration
    short rawPressure; // Variable declaration
    short rawTemperature; // Variable declaration
    char valueDP1; // Variable declaration
    char valueDP2; // Variable declaration
    char valueDP3; // Variable declaration
    char valueDP4; // Variable declaration
    char valueDP5; // Variable declaration
    char valueDP6; // Variable declaration
    char valueDP7; // Variable declaration
    char valueDP8; // Variable declaration
    char valueDP9; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    valueMsb = readPressureMsb();
    valueLsb = readPressureLsb();
    valueXlsb = readPressureXlsb();
    valueDP1 = readDigP1();
    valueDP2 = readDigP2();
    valueDP3 = readDigP3();
    valueDP4 = readDigP4();
    valueDP5 = readDigP5();
    valueDP6 = readDigP6();
    valueDP7 = readDigP7();
    valueDP8 = readDigP8();
    valueDP9 = readDigP9();
    rawTemperature = temperatureasCelsius();
    rawTemperature = (rawTemperature*5120.0);
    rawPressure = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));
    rawComp1 = ((rawTemperature/2)-64000.0);
    rawComp2 = ((rawComp1*rawComp1*valueDP6)/32768.0);
    rawComp2 = (rawComp2+(rawComp1*valueDP5*2.0));
    rawComp2 = ((rawComp2/4.0)+(valueDP4*65536.0));
    rawComp3 = (valueDP3*rawComp1*rawComp1);
    rawComp1 = (((rawComp3/524288.0)+(valueDP2*rawComp1))/524288.0);
    rawComp1 = ((1.0+(rawComp1/32768.0))*valueDP1);
    hpa = (1048576.0-rawPressure);
    hpa = ((hpa-(rawComp2/4096.0))*(6250.0/rawComp1));
    rawComp1 = ((valueDP9*hpa*hpa)/2147483648.0);
    rawComp2 = ((hpa*valueDP8)/32768.0);
    hpa = (hpa+((rawComp1+rawComp2+valueDP7)/16.0));
    hpa = (hpa/100.0);


    return hpa;
}

short BMP280::pressureasRaw() {
    short output; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    valueMsb = readPressureMsb();
    valueLsb = readPressureLsb();
    valueXlsb = readPressureXlsb();
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    return output;
}

float BMP280::temperatureasCelsius() {
    float celsius; // Variable declaration
    short rawComp1; // Variable declaration
    short rawComp2; // Variable declaration
    short rawComp3; // Variable declaration
    short rawTemp; // Variable declaration
    char valueDT1; // Variable declaration
    char valueDT2; // Variable declaration
    char valueDT3; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    valueMsb = readTempMsb();
    valueLsb = readTempLsb();
    valueXlsb = readTempXlsb();
    valueDT1 = readDigT1();
    valueDT2 = readDigT2();
    valueDT3 = readDigT3();
    rawTemp = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));
    rawComp1 = (((rawTemp/16384.0)-(valueDT1/1024.0))*valueDT2);
    rawComp3 = ((rawTemp/131072.0)-(valueDT1/8192.0));
    rawComp2 = (rawComp3*rawComp3*valueDT3);
    celsius = ((rawComp1+rawComp2)/5120.0);


    return celsius;
}

short BMP280::temperatureasRaw() {
    short output; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    valueMsb = readTempMsb();
    valueLsb = readTempLsb();
    valueXlsb = readTempXlsb();
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    return output;
}

