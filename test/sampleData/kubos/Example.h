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

#ifndef _Example_H_
#define _Example_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c.h"


/*
 * Valid values for Write-only fields for RegisterA

 */
enum FieldB {
    FIELDB_VAL_1 = 1, // Value 1
    FIELDB_VAL_2 = 2, // Value 2
    FIELDB_VAL_3 = 4, // Value 3
    FIELDB_VAL_4 = 8 // Value 4
};
typedef enum FieldB FieldB_t;
enum deviceAddress {
    I2C_ADDRESS_16 = 16,
    I2C_ADDRESS_32 = 32,
    I2C_ADDRESS_48 = 48
};
typedef enum deviceAddress deviceAddress_t;

int example_init(deviceAddress_t address, char* bus_name);
void example_terminate();
/**
  * An 8-bit register

*/
int example_readRegisterA(uint8_t* val);

/**
 * An 8-bit register

 */
int example_writeRegisterA(uint8_t* data);/**
  * A 16-bit register

*/
int example_readRegisterB(uint16_t* val);

/**
 * A 16-bit register

 */
int example_writeRegisterB(uint16_t* data);/**
  * A 32-bit register

*/
int example_readRegisterC(uint32_t* val);

/**
 * A 32-bit register

 */
int example_writeRegisterC(uint32_t* data);/**
  * A dummy register that has no data

*/
int example_readRegisterD(uint8_t* val);

/**
 * A dummy register that has no data

 */
int example_writeRegisterD();
/**
 * This is a few bits

 */
int example_get_fielda(uint8_t* val);
/**
 * This is fewer bits

 */
int example_set_fieldb(uint8_t* data);
/**
 * A single-bit

 */
int example_get_fieldc(uint8_t* val);
/**
 * A single-bit

 */
int example_set_fieldc(uint8_t* data);

/**
 * Enables features on device

*/
void example__lifecycle_begin(char* val);
/**
 * Enables features on device

*/
void example__lifecycle_end(char* val);

/**
 * Computes and returns

*/
void example_return_array(void* val);
/**
 * Computes and returns

*/
void example_return_number(short* val);
/**
 * Computes and returns

*/
void example_return_void();


#endif