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

#pragma once

#include "pw_bytes/byte_builder.h"
#include "pw_chrono/system_clock.h"
#include "pw_i2c/address.h"
#include "pw_i2c/device.h"
#include "pw_i2c/initiator.h"
#include "pw_result/result.h"
#include "pw_status/status.h"


class BMP180 : RegisterDevice {
    public:
        BMP180(Initiator& initiator);


        /**
         * Stores the current measurement type.

         */
        Status writeControl(uint8_t data);
        /**
         * Constant register for pressure measurement calibration.

         */
        Result<uint16_t> readPressureCalAC1();


        /**
         * Constant register for pressure measurement calibration.

         */
        Result<uint16_t> readPressureCalAC2();


        /**
         * Constant register for pressure measurement calibration.

         */
        Result<uint16_t> readPressureCalVB1();


        /**
         * Constant register for pressure measurement calibration.

         */
        Result<uint16_t> readPressureCalVB2();


        /**
         * Stores the most recent measurement result.

         */
        Result<uint16_t> readResult();


        /**
         * Third constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCal3();


        /**
         * Fourth constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCal4();


        /**
         * Fifth constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCal5();


        /**
         * Sixth constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCal6();


        /**
         * Constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCalMC();


        /**
         * Constant register for temperature measurement calibration.

         */
        Result<uint16_t> readTempCalMD();



        /**
         * Reads the pressure in absolute millibars,
         * not compensated for sea level.

         */
        float pressureasMbars();

        /**
         * Reads the temperature as a raw value or in Celsius.

         */
        float temperatureasCelsius();

};