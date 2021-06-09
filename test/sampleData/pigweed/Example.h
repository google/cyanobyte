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
* Generated from peripherals/example.yaml using Cyanobyte Codegen v0.0.2
* Class for Example
* Example of a package

*/

#pragma once

#include <cmath>

#include "pw_bytes/byte_builder.h"
#include "pw_chrono/system_clock.h"
#include "pw_i2c/address.h"
#include "pw_i2c/device.h"
#include "pw_i2c/register_device.h"
#include "pw_i2c/initiator.h"
#include "pw_result/result.h"
#include "pw_status/status.h"

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

class Example : pw::i2c::RegisterDevice {
    public:
        Example(pw::i2c::Initiator& initiator, deviceAddress_t address);
        deviceAddress_t DEVICE_ADDRESS;

        /**
         * An 8-bit register

         */
        pw::Result<uint8_t> readRegisterA();

        /**
         * An 8-bit register

         */
        pw::Status writeRegisterA(uint8_t data);
        /**
         * A 16-bit register

         */
        pw::Result<uint16_t> readRegisterB();

        /**
         * A 16-bit register

         */
        pw::Status writeRegisterB(uint16_t data);
        /**
         * A 32-bit register

         */
        pw::Result<uint32_t> readRegisterC();

        /**
         * A 32-bit register

         */
        pw::Status writeRegisterC(uint32_t data);
        /**
         * A dummy register that has no data

         */
        pw::Result<uint8_t> readRegisterD();

        /**
         * A dummy register that has no data

         */
        pw::Status writeRegisterD();
        /**
         * This is a few bits

         */
        pw::Result<uint8_t> getFieldA();
        /**
         * This is fewer bits

         */
        pw::Status setFieldB(uint8_t data);
        /**
         * A single-bit

         */
        pw::Result<uint8_t> getFieldC();
        /**
         * A single-bit

         */
        pw::Status setFieldC(uint8_t data);

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

};