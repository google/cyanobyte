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

#include <time.h>




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

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int bmp180_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void bmp180_terminate() {
    k_i2c_terminate(&i2c_bus);
}


int bmp180_writeControl(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_CONTROL };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}int bmp180_readPressureCalAC1(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalAC2(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalVB1(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalVB2(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readResult(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal3(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal4(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal5(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal6(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCalMC(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCalMD(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}



void bmp180_pressure_asmbars(float* val) {
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


    bmp180_writeControl(&52);
    bmp180_readResult(&pressure);
    temperatureasCelsius(&temperature);
    nanosleep(0, 10000)
    rawComp = (temperature-25);
    bmp180_readPressureCalAC1(&ac1);
    bmp180_readPressureCalAC2(&ac2);
    x1 = (160*pow(2, -13)*ac2);
    bmp180_readPressureCalVB2(&vb2);
    x2 = (pow(160, 2)*pow(2, -25)*vb2);
    x = ((x2*pow(rawComp, 2))+(x1*rawComp)+ac1);
    bmp180_readTempCal3(&ac3);
    c3 = (160*pow(2, -15)*ac3);
    bmp180_readTempCal4(&ac4);
    c4 = (pow(10, -3)*pow(2, -15)*ac4);
    bmp180_readPressureCalVB1(&vb1);
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



    val = pressure;
}

void bmp180_temperature_ascelsius(float* val) {
    short rawComp; // Variable declaration
    short rawMc; // Variable declaration
    short rawMd; // Variable declaration
    float temperature; // Variable declaration
    uint16_t varAc5; // Variable declaration
    uint16_t varAc6; // Variable declaration
    float varC5; // Variable declaration
    float varMc; // Variable declaration
    float varMd; // Variable declaration


    bmp180_writeControl(&46);
    bmp180_readResult(&temperature);
    bmp180_readTempCal5(&varAc5);
    bmp180_readTempCal6(&varAc6);
    varC5 = ((pow(2, -15)/160)*varAc5);
    rawComp = (varC5*(temperature-varAc6));
    bmp180_readTempCalMC(&rawMc);
    varMc = ((pow(2, 11)/pow(160, 2))*rawMc);
    bmp180_readTempCalMD(&rawMd);
    varMd = (rawMd/160);
    temperature = (rawComp+(varMc/(rawComp+varMd)));


    val = temperature;
}

