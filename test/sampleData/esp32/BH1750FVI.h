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

#ifndef _BH1750FVI_H_
#define _BH1750FVI_H_
#include <Arduino.h>
#include <Wire.h>

enum deviceAddress {
    I2C_ADDRESS_35 = 35,
    I2C_ADDRESS_92 = 92
};
typedef enum deviceAddress deviceAddress_t;

class BH1750FVI {
    public:
        BH1750FVI(TwoWire& wire, deviceAddress_t address);
        deviceAddress_t DEVICE_ADDRESS;

        void begin();

        /**
         * Start measurement at 0.5lx resolution. Typically 120ms.

         */
        int writeContinuousHRes2Mode();

        /**
         * Start measurement at 1lx resolution. Typically 120ms.

         */
        int writeContinuousHResMode();

        /**
         * Start measurement at 4lx resolution. Typically 16ms.

         */
        int writeContinuouslyLResMode();

        /**
         * Start measurement at 0.5lx resolution. Typically 120ms.
         * Power Down after measurement.

         */
        int writeOnceHRes2Mode();

        /**
         * Start measurement at 1lx resolution. Typically 120ms.
         * Power Down after measurement.

         */
        int writeOnceHResMode();

        /**
         * Start measurement at 4lx resolution. Typically 16ms.
         * Power Down after measurement.

         */
        int writeOnceLResMode();

        /**
         * No active state

         */
        int writePowerDown();

        /**
         * Waiting for measurement command

         */
        int writePowerOn();

        /**
         * Reset data register value. Not accepted in Power Down mode.

         */
        int writeReset();

        /**
         * Sends a POWER ON cmd to device

         */
        void _lifecycleBegin();

        /**
         * Things you can do to device

         */
        void commandPowerDown();
        /**
         * Things you can do to device

         */
        void commandReset();

        /**
         * Read light intensity from device

         */
        uint16_t readLightIntensity();


    private:
        TwoWire* _wire;
};

#endif