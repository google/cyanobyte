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

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
static deviceAddress_t DEVICE_ADDRESS;

int example_init(deviceAddress_t address, char* bus_name) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
    example__lifecycle_begin();
}

void example_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int example_readRegisterA(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 1) != I2C_OK) {
        return -2;
    }
    return 0;
}

int example_writeRegisterA(uint8_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[2] = { (uint8_t) REGISTER_REGISTERA };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 2) != I2C_OK) {
        return -1;
    }
    return 0;
}int example_readRegisterB(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int example_writeRegisterB(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_REGISTERB };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}int example_readRegisterC(uint32_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 4) != I2C_OK) {
        return -2;
    }
    return 0;
}

int example_writeRegisterC(uint32_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[5] = { (uint8_t) REGISTER_REGISTERC };
    uint8_t buffer[1] = (data >> 32) & 0xFF;
    uint8_t buffer[2] = (data >> 24) & 0xFF;
    uint8_t buffer[3] = (data >> 16) & 0xFF;
    uint8_t buffer[4] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 5) != I2C_OK) {
        return -1;
    }
    return 0;
}int example_readRegisterD(uint8_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 0) != I2C_OK) {
        return -2;
    }
    return 0;
}

int example_writeRegisterD() {
    // Put our data into uint8_t buffer
    uint8_t buffer[1] = { (uint8_t) REGISTER_REGISTERD };
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 1) != I2C_OK) {
        return -1;
    }
    return 0;
}
int example_get_fielda(uint8_t* val) {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    int result = example_readRegisterA(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000011110000;
    // Bitshift value
    val = val >> 4;
    return 0;
}

int example_set_fieldb(uint8_t* data) {
    // Bitshift value
    data = data << 2;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data;
    int result = example_readRegisterA(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = example_writeRegisterA(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}
int example_get_fieldc(uint8_t* val) {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    int result = example_readRegisterA(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000000000010;
    // Bitshift value
    val = val >> 1;
    return 0;
}

int example_set_fieldc(uint8_t* data) {
    // Bitshift value
    data = data << 1;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    uint8_t register_data;
    int result = example_readRegisterA(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = example_writeRegisterA(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}

void example__lifecycle_begin(char* val) {
    char output; // Variable declaration


    output = 1
    example_writeRegisterA(&output);


    val = output;
}

void example__lifecycle_end(char* val) {
    char output; // Variable declaration


    output = 1
    example_writeRegisterA(&output);


    val = output;
}

void example_return_array(void* val) {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation);


    val = [summation, summation];
}

void example_return_number(short* val) {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation);


    val = summation;
}

void example_return_void() {
    short summation; // Variable declaration


    summation = (1024+1024);
    example_writeRegisterA(&summation);


}

