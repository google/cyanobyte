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
#include <Arduino.h>
#include <Wire.h>

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

class Example {
    public:
        Example(TwoWire& wire, deviceAddress_t address);
        deviceAddress_t DEVICE_ADDRESS;

        void begin();
        /**
         * An 8-bit register

         */
        uint8_t readRegisterA();

        /**
         * An 8-bit register

         */
        int writeRegisterA(uint8_t data);
        /**
         * A 16-bit register

         */
        uint16_t readRegisterB();

        /**
         * A 16-bit register

         */
        int writeRegisterB(uint16_t data);
        /**
         * A 32-bit register

         */
        uint32_t readRegisterC();

        /**
         * A 32-bit register

         */
        int writeRegisterC(uint32_t data);
        /**
         * A dummy register that has no data

         */
        uint8_t readRegisterD();

        /**
         * A dummy register that has no data

         */
        int writeRegisterD();
        /**
         * This is a few bits

         */
        uint8_t getFieldA();
        /**
         * This is fewer bits

         */
        int setFieldB(uint8_t data);
        /**
         * A single-bit

         */
        uint8_t getFieldC();
        /**
         * A single-bit

         */
        int setFieldC(uint8_t data);

        /**
         * Enables features on device

         */
        char _lifecycleBegin();
        /**
         * Enables features on device

         */
        char _lifecycleEnd();

        /**
         * Computes and returns

         */
        void ReturnArray(short * returnArray);
        /**
         * Computes and returns

         */
        short ReturnNumber();
        /**
         * Computes and returns

         */
        void ReturnVoid();


    private:
        TwoWire* _wire;
};

#endif