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


uint16_t BMP280::readDigP1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP1);
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


uint16_t BMP280::readDigP2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP2);
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


uint16_t BMP280::readDigP3() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP3);
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


uint16_t BMP280::readDigP4() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP4);
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


uint16_t BMP280::readDigP5() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP5);
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


uint16_t BMP280::readDigP6() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP6);
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


uint16_t BMP280::readDigP7() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP7);
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


uint16_t BMP280::readDigP8() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP8);
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


uint16_t BMP280::readDigP9() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGP9);
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


uint16_t BMP280::readDigT1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT1);
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


uint16_t BMP280::readDigT2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT2);
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


uint16_t BMP280::readDigT3() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_DIGT3);
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


uint8_t BMP280::readPressureLsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURELSB);
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


uint8_t BMP280::readPressureMsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSUREMSB);
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


uint8_t BMP280::readPressureXlsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSUREXLSB);
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


uint8_t BMP280::readTempLsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPLSB);
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


uint8_t BMP280::readTempMsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPMSB);
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


uint8_t BMP280::readTempXlsb() {
    uint8_t datum;
    uint8_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPXLSB);
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




float BMP280::pressureasHpa() {
    float hpa; // Variable declaration
    long rawComp1; // Variable declaration
    long rawComp2; // Variable declaration
    long rawComp3; // Variable declaration
    long rawPressure; // Variable declaration
    long rawTemperature; // Variable declaration
    short valueDP1; // Variable declaration
    short valueDP2; // Variable declaration
    short valueDP3; // Variable declaration
    short valueDP4; // Variable declaration
    short valueDP5; // Variable declaration
    short valueDP6; // Variable declaration
    short valueDP7; // Variable declaration
    short valueDP8; // Variable declaration
    short valueDP9; // Variable declaration
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

long BMP280::pressureasRaw() {
    long output; // Variable declaration
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
    long rawComp1; // Variable declaration
    long rawComp2; // Variable declaration
    long rawComp3; // Variable declaration
    long rawTemp; // Variable declaration
    short valueDT1; // Variable declaration
    short valueDT2; // Variable declaration
    short valueDT3; // Variable declaration
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

long BMP280::temperatureasRaw() {
    long output; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    valueMsb = readTempMsb();
    valueLsb = readTempLsb();
    valueXlsb = readTempXlsb();
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    return output;
}

