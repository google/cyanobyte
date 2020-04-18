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

#ifndef _BMP180_H_
#define _BMP180_H_
#include <Arduino.h>
#include <Wire.h>
#include <math.h>


class BMP180 {
    public:
        BMP180(TwoWire& wire);

        void begin();
        void end();

        /**
         * Register stores what the measurement type should be

         */
        int writeControl(uint8_t data);
        /**
         * For calibration

         */
        uint16_t readPressureCalAC1();


        /**
         * For calibration

         */
        uint16_t readPressureCalAC2();


        /**
         * For calibration

         */
        uint16_t readPressureCalVB1();


        /**
         * For calibration

         */
        uint16_t readPressureCalVB2();


        /**
         * Register stores most recent measurement result

         */
        uint16_t readResult();


        /**
         * For calibration

         */
        uint16_t readTempCal3();


        /**
         * For calibration

         */
        uint16_t readTempCal4();


        /**
         * For calibration

         */
        uint16_t readTempCal5();


        /**
         * For calibration

         */
        uint16_t readTempCal6();


        /**
         * For calibration

         */
        uint16_t readTempCalMC();


        /**
         * For calibration

         */
        uint16_t readTempCalMD();



        /**
         * Reads the temperature

         */
        float temperatureasCelsius();


    private:
        TwoWire* _wire;
};

#endif