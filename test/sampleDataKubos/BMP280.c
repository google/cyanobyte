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



short _sign(val, length) {
    // Convert unsigned integer to signed integer
    if val & (1 << (length - 1)) {
        return val - (1 << length);
    }
    return val;
}

#include "BMP280.h"
#define DEVICE_ADDRESS 119

#define REGISTER_TEMPMSB 250
#define REGISTER_TEMPLSB 251
#define REGISTER_TEMPXLSB 252
#define REGISTER_DIGT1 136
#define REGISTER_DIGT2 138
#define REGISTER_DIGT3 140
#define REGISTER_PRESSUREMSB 247
#define REGISTER_PRESSURELSB 248
#define REGISTER_PRESSUREXLSB 249
#define REGISTER_DIGP1 142
#define REGISTER_DIGP2 144
#define REGISTER_DIGP3 146
#define REGISTER_DIGP4 148
#define REGISTER_DIGP5 150
#define REGISTER_DIGP6 152
#define REGISTER_DIGP7 154
#define REGISTER_DIGP8 156
#define REGISTER_DIGP9 158

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int bmp280_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void bmp280_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int bmp280_readTempMsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeTempMsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPMSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readTempLsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeTempLsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPLSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readTempXlsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeTempXlsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_TEMPXLSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigT1(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigT1(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT1 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigT2(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigT2(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT2 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigT3(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigT3(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGT3 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readPressureMsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writePressureMsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSUREMSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readPressureLsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writePressureLsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSURELSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readPressureXlsb(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writePressureXlsb(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_PRESSUREXLSB };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP1(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP1(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP1 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP2(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP2(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP2 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP3(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP3(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP3 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP4(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP4(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP4 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP5(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP5(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP5 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP6(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP6(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP6 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP7(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP7(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP7 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP8(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP8(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP8 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}

int bmp280_readDigP9(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp280_writeDigP9(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_DIGP9 };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}



void bmp280_temperature_asraw(short* val) {
    char valueMsb; // Variable declaration
    char valueLsb; // Variable declaration
    char valueXlsb; // Variable declaration
    short output; // Variable declaration


    bmp280_readTempMsb(&valueMsb);
    bmp280_readTempLsb(&valueLsb);
    bmp280_readTempXlsb(&valueXlsb);
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    return output;
}

void bmp280_temperature_ascelsius(float* val) {
    char valueMsb; // Variable declaration
    char valueLsb; // Variable declaration
    char valueXlsb; // Variable declaration
    char valueDT1; // Variable declaration
    char valueDT2; // Variable declaration
    char valueDT3; // Variable declaration
    short rawTemp; // Variable declaration
    short rawComp1; // Variable declaration
    short rawComp2; // Variable declaration
    short rawComp3; // Variable declaration
    float celsius; // Variable declaration


    bmp280_readTempMsb(&valueMsb);
    bmp280_readTempLsb(&valueLsb);
    bmp280_readTempXlsb(&valueXlsb);
    bmp280_readDigT1(&valueDT1);
    bmp280_readDigT2(&valueDT2);
    bmp280_readDigT3(&valueDT3);
    rawTemp = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));
    rawComp1 = (((rawTemp/16384.0)-(valueDT1/1024.0))*valueDT2);
    rawComp3 = ((rawTemp/131072.0)-(valueDT1/8192.0));
    rawComp2 = (rawComp3*rawComp3*valueDT3);
    celsius = ((rawComp1+rawComp2)/5120.0);


    return celsius;
}


void bmp280_pressure_asraw(short* val) {
    char valueMsb; // Variable declaration
    char valueLsb; // Variable declaration
    char valueXlsb; // Variable declaration
    short output; // Variable declaration


    bmp280_readPressureMsb(&valueMsb);
    bmp280_readPressureLsb(&valueLsb);
    bmp280_readPressureXlsb(&valueXlsb);
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    return output;
}

void bmp280_pressure_ashpa(float* val) {
    char valueMsb; // Variable declaration
    char valueLsb; // Variable declaration
    char valueXlsb; // Variable declaration
    char valueDP1; // Variable declaration
    char valueDP2; // Variable declaration
    char valueDP3; // Variable declaration
    char valueDP4; // Variable declaration
    char valueDP5; // Variable declaration
    char valueDP6; // Variable declaration
    char valueDP7; // Variable declaration
    char valueDP8; // Variable declaration
    char valueDP9; // Variable declaration
    short rawPressure; // Variable declaration
    short rawTemperature; // Variable declaration
    short rawComp1; // Variable declaration
    short rawComp2; // Variable declaration
    short rawComp3; // Variable declaration
    float hpa; // Variable declaration


    bmp280_readPressureMsb(&valueMsb);
    bmp280_readPressureLsb(&valueLsb);
    bmp280_readPressureXlsb(&valueXlsb);
    bmp280_readDigP1(&valueDP1);
    bmp280_readDigP2(&valueDP2);
    bmp280_readDigP3(&valueDP3);
    bmp280_readDigP4(&valueDP4);
    bmp280_readDigP5(&valueDP5);
    bmp280_readDigP6(&valueDP6);
    bmp280_readDigP7(&valueDP7);
    bmp280_readDigP8(&valueDP8);
    bmp280_readDigP9(&valueDP9);
    temperatureasCelsius(&rawTemperature);
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

