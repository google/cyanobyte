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
* Auto-generated file for LSM303D v0.1.0.
* Generated from peripherals/LSM303D.yaml using Cyanobyte Codegen v0.1.0
* Class for LSM303D
* STMicroelectronics accelerometer and magnetometer

*/

#ifndef _LSM303D_H_
#define _LSM303D_H_
#include <Arduino.h>
#include <Wire.h>
#include <math.h>


class LSM303D {
    public:
        LSM303D(TwoWire& wire);

        void begin();
        /**
         * Raw accelerometer data on X plane

         */
        uint8_t readAccelerometerX_High();


        /**
         * Raw accelerometer data on X plane

         */
        uint8_t readAccelerometerX_Low();


        /**
         * Raw accelerometer data on Y plane

         */
        uint8_t readAccelerometerY_High();


        /**
         * Raw accelerometer data on Y plane

         */
        uint8_t readAccelerometerY_Low();


        /**
         * Raw accelerometer data on Z plane

         */
        uint8_t readAccelerometerZ_High();


        /**
         * Raw accelerometer data on Z plane

         */
        uint8_t readAccelerometerZ_Low();


        /**
         * Raw magnetometer data on X plane

         */
        uint8_t readMagnetometerX_High();


        /**
         * Raw magnetometer data on X plane

         */
        uint8_t readMagnetometerX_Low();


        /**
         * Raw magnetometer data on Y plane

         */
        uint8_t readMagnetometerY_High();


        /**
         * Raw magnetometer data on Y plane

         */
        uint8_t readMagnetometerY_Low();


        /**
         * Raw magnetometer data on Z plane

         */
        uint8_t readMagnetometerZ_High();


        /**
         * Raw magnetometer data on Z plane

         */
        uint8_t readMagnetometerZ_Low();



        /**
         * Measures the current acceleration

         */
        void accelerationasG(short * returnArray);
        /**
         * Measures the current acceleration

         */
        short accelerationxPlane();
        /**
         * Measures the current acceleration

         */
        short accelerationyPlane();
        /**
         * Measures the current acceleration

         */
        short accelerationzPlane();

        /**
         * Reads the magnetic orientation

         */
        short orientationheading();
        /**
         * Reads the magnetic orientation

         */
        short orientationxPlane();
        /**
         * Reads the magnetic orientation

         */
        short orientationyPlane();
        /**
         * Reads the magnetic orientation

         */
        short orientationzPlane();


    private:
        TwoWire* _wire;
};

#endif