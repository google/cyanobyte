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
* Auto-generated file for Example v0.1.0.
* Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
* Class for Example
* Example of a package

*/




#include "Example.h"

#define REGISTER_REGISTERA 0
#define REGISTER_REGISTERB 1
#define REGISTER_REGISTERC 2
#define REGISTER_REGISTERD 3

// Provide an I2C connect function, return status
static deviceAddress_t DEVICE_ADDRESS;

int example_init(deviceAddress_t address, int (*connect)(uint8_t)) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int example_readRegisterA(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_REGISTERA, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int example_writeRegisterA(
    uint8_t* data,
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_REGISTERA, data, 1) != 0) {
        return -1;
    }
    return 0;
}int example_readRegisterB(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_REGISTERB, val, 2) != 0) {
        return -2;
    }
    return 0;
}

int example_writeRegisterB(
    uint16_t* data,
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_REGISTERB, data, 2) != 0) {
        return -1;
    }
    return 0;
}int example_readRegisterC(
    uint32_t* val,
    int (*read)(uint8_t, uint8_t, uint32_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_REGISTERC, val, 4) != 0) {
        return -2;
    }
    return 0;
}

int example_writeRegisterC(
    uint32_t* data,
    int (*write)(uint8_t, uint8_t, uint32_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_REGISTERC, data, 4) != 0) {
        return -1;
    }
    return 0;
}int example_readRegisterD(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_REGISTERD, val, 0) != 0) {
        return -2;
    }
    return 0;
}

int example_writeRegisterD(
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_REGISTERD, data, 0) != 0) {
        return -1;
    }
    return 0;
}
int example_get_fielda(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    int result = example_readRegisterA(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000011110000;
    // Bitshift value
    val = val >> 4;
    return 0;
}

int example_set_fieldb(
    uint8_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Bitshift value
    data = data << 2;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data;
    int result = example_readRegisterA(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = example_writeRegisterA(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}
int example_get_fieldc(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    int result = example_readRegisterA(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000000000010;
    // Bitshift value
    val = val >> 1;
    return 0;
}

int example_set_fieldc(
    uint8_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Bitshift value
    data = data << 1;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data;
    int result = example_readRegisterA(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = example_writeRegisterA(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void example__lifecycle_begin(
    char* val,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    char output; // Variable declaration


    output = 1
    example_writeRegisterA(&output, write);


    *val = output;
}

void example__lifecycle_end(
    char* val,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    char output; // Variable declaration


    output = 1
    example_writeRegisterA(&output, write);


    *val = output;
}

void example_return_array(
    void* val,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation, write);


    *val = [summation, summation];
}

void example_return_number(
    short* val,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation, write);


    *val = summation;
}

void example_return_void(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation, write);


}

