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
* Generated from peripherals/BMP180.yaml using Cyanobyte Codegen v0.1.0
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

// Provide an I2C connect function, return status
int bmp180_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}


int bmp180_writeControl(
    uint8_t* data,
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONTROL, data, 1) != 0) {
        return -1;
    }
    return 0;
}int bmp180_readPressureCalAC1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSURECALAC1, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalAC2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSURECALAC2, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalVB1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSURECALVB1, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readPressureCalVB2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_PRESSURECALVB2, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readResult(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_RESULT, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal3(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCAL3, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal4(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCAL4, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal5(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCAL5, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCal6(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCAL6, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCalMC(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCALMC, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int bmp180_readTempCalMD(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_TEMPCALMD, val, 2) != 0) {
        return -2;
    }
    return 0;
}



void bmp180_temperature_ascelsius(
    float* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    short rawComp; // Variable declaration
    short rawMc; // Variable declaration
    short rawMd; // Variable declaration
    float temperature; // Variable declaration
    uint16_t varAc5; // Variable declaration
    uint16_t varAc6; // Variable declaration
    float varC5; // Variable declaration
    float varMc; // Variable declaration
    float varMd; // Variable declaration


    bmp180_writeControl(&46, write);
    bmp180_readResult(&temperature, read);
    bmp180_readTempCal5(&varAc5, read);
    bmp180_readTempCal6(&varAc6, read);
    varC5 = ((pow(2, -15)/160)*varAc5);
    rawComp = (varC5*(temperature-varAc6));
    bmp180_readTempCalMC(&rawMc, read);
    varMc = ((pow(2, 11)/pow(160, 2))*rawMc);
    bmp180_readTempCalMD(&rawMd, read);
    varMd = (rawMd/160);
    temperature = (rawComp+(varMc/(rawComp+varMd)));


    *val = temperature;
}

