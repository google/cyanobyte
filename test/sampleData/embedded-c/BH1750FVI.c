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

// Provide an I2C connect function, return status
static deviceAddress_t DEVICE_ADDRESS;

int bh1750fvi_init(deviceAddress_t address, int (*connect)(uint8_t)) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}


int bh1750fvi_writeContinuousHRes2Mode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONTINUOUSHRES2MODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeContinuousHResMode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONTINUOUSHRESMODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeContinuouslyLResMode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_CONTINUOUSLYLRESMODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceHRes2Mode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_ONCEHRES2MODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceHResMode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_ONCEHRESMODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeOnceLResMode(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_ONCELRESMODE, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writePowerDown(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_POWERDOWN, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writePowerOn(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_POWERON, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int bh1750fvi_writeReset(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_RESET, data, 0) != 0) {
        return -1;
    }
    return 0;
}

void bh1750fvi__lifecycle_begin(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {


    bh1750fvi_writePowerOn(write);


}

void bh1750fvi_command_powerdown(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {


    bh1750fvi_writePowerDown(write);


}

void bh1750fvi_command_reset(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {


    bh1750fvi_writePowerOn(write);
    bh1750fvi_writeReset(write);


}

void bh1750fvi_read_lightintensity(
    uint16_t* val,

) {
    uint16_t intensity; // Variable declaration


    read(DEVICE_ADDRESS, NULL, intensity, 2);


    *val = intensity;
}

