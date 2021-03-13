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
* Auto-generated file for BMP180 v0.1.0.
* Generated from peripherals/BMP180.yaml using Cyanobyte Codegen v0.0.2
* Class for BMP180
* Bosch Digital Temperature / Pressure Sensor

*/




#include "BMP180.h"
#define DEVICE_ADDRESS 119

#define REGISTER_CONTROL 244
#define REGISTER_PRESSURECALAC1 170
#define REGISTER_PRESSURECALAC2 172
#define REGISTER_PRESSURECALVB1 182
#define REGISTER_PRESSURECALVB2 184
#define REGISTER_RESULT 246
#define REGISTER_TEMPCAL3 174
#define REGISTER_TEMPCAL4 176
#define REGISTER_TEMPCAL5 178
#define REGISTER_TEMPCAL6 180
#define REGISTER_TEMPCALMC 188
#define REGISTER_TEMPCALMD 190

BMP180::BMP180(TwoWire& wire) :
    _wire(&wire)
{
}

void BMP180::begin() {
    _wire->begin();
}

void BMP180::end() {
    _wire->end();
}


int BMP180::writeControl(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_CONTROL };
    buffer[1] = (data >> 0) & 0xFF;
    _wire->write(buffer, 2);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

uint16_t BMP180::readPressureCalAC1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURECALAC1);
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


uint16_t BMP180::readPressureCalAC2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURECALAC2);
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


uint16_t BMP180::readPressureCalVB1() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURECALVB1);
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


uint16_t BMP180::readPressureCalVB2() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_PRESSURECALVB2);
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


uint16_t BMP180::readResult() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_RESULT);
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


uint16_t BMP180::readTempCal3() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCAL3);
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


uint16_t BMP180::readTempCal4() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCAL4);
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


uint16_t BMP180::readTempCal5() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCAL5);
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


uint16_t BMP180::readTempCal6() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCAL6);
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


uint16_t BMP180::readTempCalMC() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCALMC);
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


uint16_t BMP180::readTempCalMD() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_TEMPCALMD);
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




float BMP180::pressureasMbars() {
    short ac1; // Variable declaration
    short ac2; // Variable declaration
    short ac3; // Variable declaration
    uint16_t ac4; // Variable declaration
    float b1; // Variable declaration
    float c3; // Variable declaration
    float c4; // Variable declaration
    float p0; // Variable declaration
    float p1; // Variable declaration
    float p2; // Variable declaration
    float pressure; // Variable declaration
    float rawComp; // Variable declaration
    float temperature; // Variable declaration
    short vb1; // Variable declaration
    short vb2; // Variable declaration
    float x; // Variable declaration
    float x1; // Variable declaration
    float x2; // Variable declaration
    float y; // Variable declaration
    float y0; // Variable declaration
    float y1; // Variable declaration
    float y2; // Variable declaration
    float z; // Variable declaration


    writeControl(52);
    pressure = readResult();
    temperature = temperatureasCelsius();
    delay(10)
    rawComp = (temperature-25);
    ac1 = readPressureCalAC1();
    ac2 = readPressureCalAC2();
    x1 = (160*pow(2, -13)*ac2);
    vb2 = readPressureCalVB2();
    x2 = (pow(160, 2)*pow(2, -25)*vb2);
    x = ((x2*pow(rawComp, 2))+(x1*rawComp)+ac1);
    ac3 = readTempCal3();
    c3 = (160*pow(2, -15)*ac3);
    ac4 = readTempCal4();
    c4 = (pow(10, -3)*pow(2, -15)*ac4);
    vb1 = readPressureCalVB1();
    b1 = (pow(160, 2)*pow(2, -30)*vb1);
    y0 = (c4*pow(2, 15));
    y1 = (c4*c3);
    y2 = (c4*b1);
    y = ((y2*pow(rawComp, 2))+(y1*rawComp)+y0);
    z = ((pressure-x)/y);
    p0 = ((3791-8)/1600);
    p1 = (1-(7357*pow(2, -30)));
    p2 = (3038*100*pow(2, -36));
    pressure = ((p2*pow(z, 2))+(p1*z)+p0);



    return pressure;
}

float BMP180::temperatureasCelsius() {
    short rawComp; // Variable declaration
    short rawMc; // Variable declaration
    short rawMd; // Variable declaration
    float temperature; // Variable declaration
    uint16_t varAc5; // Variable declaration
    uint16_t varAc6; // Variable declaration
    float varC5; // Variable declaration
    float varMc; // Variable declaration
    float varMd; // Variable declaration


    writeControl(46);
    temperature = readResult();
    varAc5 = readTempCal5();
    varAc6 = readTempCal6();
    varC5 = ((pow(2, -15)/160)*varAc5);
    rawComp = (varC5*(temperature-varAc6));
    rawMc = readTempCalMC();
    varMc = ((pow(2, 11)/pow(160, 2))*rawMc);
    rawMd = readTempCalMD();
    varMd = (rawMd/160);
    temperature = (rawComp+(varMc/(rawComp+varMd)));


    return temperature;
}

