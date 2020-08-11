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
* Auto-generated file for TCS3472 v0.1.0.
* Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
* Class for TCS3472
* Color Light-to-Digital Converter with IR Filter

*/




#include "TCS3472.h"
#define DEVICE_ADDRESS 41

#define REGISTER_BLUE 186
#define REGISTER_CLEAR 180
#define REGISTER_ENABLE 128
#define REGISTER_GREEN 184
#define REGISTER_RED 182

// Provide an I2C connect function, return status
int tcs3472_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int tcs3472_readblue(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_BLUE, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int tcs3472_readclear(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_CLEAR, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int tcs3472_readenable(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ENABLE, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int tcs3472_writeenable(
    uint8_t* data,
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_ENABLE, data, 1) != 0) {
        return -1;
    }
    return 0;
}int tcs3472_readgreen(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_GREEN, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int tcs3472_readred(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_RED, val, 2) != 0) {
        return -2;
    }
    return 0;
}


int tcs3472_get_init(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/enable' > 'enable'
    int result = tcs3472_readenable(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000011111111;
    return 0;
}

int tcs3472_set_init(
    uint8_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read current register data
    // '#/registers/enable' > 'enable'
    uint8_t register_data;
    int result = tcs3472_readenable(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = tcs3472_writeenable(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void tcs3472__lifecycle_begin(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    char enables; // Variable declaration


    enables = (1+2);
    tcs3472_writeenable(&enables, write);


}

