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



static short _sign(short val, short length) {
    // Convert unsigned integer to signed integer
    if val & (1 << (length - 1)) {
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

// Provide an I2C connect function, return status
int bmp280_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int bmp280_readDigP1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP1, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP2, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP3(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP3, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP4(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP4, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP5(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP5, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP6(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP6, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP7(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP7, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP8(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP8, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigP9(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGP9, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigT1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGT1, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigT2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGT2, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readDigT3(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_DIGT3, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readPressureLsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSURELSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readPressureMsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSUREMSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readPressureXlsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSUREXLSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readTempLsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPLSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readTempMsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPMSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int bmp280_readTempXlsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPXLSB, val, 1) != 0) {
        return -2;
    }
    return 0;
}



void bmp280_pressure_ashpa(
    float* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
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


    bmp280_readPressureMsb(&valueMsb, read);
    bmp280_readPressureLsb(&valueLsb, read);
    bmp280_readPressureXlsb(&valueXlsb, read);
    bmp280_readDigP1(&valueDP1, read);
    bmp280_readDigP2(&valueDP2, read);
    bmp280_readDigP3(&valueDP3, read);
    bmp280_readDigP4(&valueDP4, read);
    bmp280_readDigP5(&valueDP5, read);
    bmp280_readDigP6(&valueDP6, read);
    bmp280_readDigP7(&valueDP7, read);
    bmp280_readDigP8(&valueDP8, read);
    bmp280_readDigP9(&valueDP9, read);
    bmp280_temperature_ascelsius(&rawTemperature, read);
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


    *val = hpa;
}

void bmp280_pressure_asraw(
    long* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    long output; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    bmp280_readPressureMsb(&valueMsb, read);
    bmp280_readPressureLsb(&valueLsb, read);
    bmp280_readPressureXlsb(&valueXlsb, read);
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    *val = output;
}

void bmp280_temperature_ascelsius(
    float* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
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


    bmp280_readTempMsb(&valueMsb, read);
    bmp280_readTempLsb(&valueLsb, read);
    bmp280_readTempXlsb(&valueXlsb, read);
    bmp280_readDigT1(&valueDT1, read);
    bmp280_readDigT2(&valueDT2, read);
    bmp280_readDigT3(&valueDT3, read);
    rawTemp = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));
    rawComp1 = (((rawTemp/16384.0)-(valueDT1/1024.0))*valueDT2);
    rawComp3 = ((rawTemp/131072.0)-(valueDT1/8192.0));
    rawComp2 = (rawComp3*rawComp3*valueDT3);
    celsius = ((rawComp1+rawComp2)/5120.0);


    *val = celsius;
}

void bmp280_temperature_asraw(
    long* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    long output; // Variable declaration
    char valueLsb; // Variable declaration
    char valueMsb; // Variable declaration
    char valueXlsb; // Variable declaration


    bmp280_readTempMsb(&valueMsb, read);
    bmp280_readTempLsb(&valueLsb, read);
    bmp280_readTempXlsb(&valueXlsb, read);
    output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4));


    *val = output;
}

