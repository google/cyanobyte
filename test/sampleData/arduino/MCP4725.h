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
* Auto-generated file for MCP4725 v0.1.0.
* Generated from peripherals/MCP4725.yaml using Cyanobyte Codegen v0.1.0
* Class for MCP4725
* Microchip 4725 Digital-to-Analog Converter

*/

#ifndef _MCP4725_H_
#define _MCP4725_H_
#include <Arduino.h>
#include <Wire.h>

/*
 * Valid values for Digital (binary) output

 */
enum digitalOut {
    DIGITALOUT_GND = 0, // Ground
    DIGITALOUT_VCC = 4095 // Vcc (full power)
};
typedef enum digitalOut digitalOut_t;

class MCP4725 {
    public:
        MCP4725(TwoWire& wire);

        void begin();
        void end();
        /**
         * If EEPROM is set, the saved voltage output will
         * be loaded from power-on.

         */
        uint16_t readEEPROM();

        /**
         * If EEPROM is set, the saved voltage output will
         * be loaded from power-on.

         */
        int writeEEPROM(uint16_t data);
        /**
         * VOut = (Vcc * value) / 4096
         * The output is a range between 0 and Vcc with
         * steps of Vcc/4096.
         * In a 3.3v system, each step is 800 microvolts.

         */
        uint16_t readVOut();

        /**
         * VOut = (Vcc * value) / 4096
         * The output is a range between 0 and Vcc with
         * steps of Vcc/4096.
         * In a 3.3v system, each step is 800 microvolts.

         */
        int writeVOut(uint16_t data);
        /**
         * Only allows you to send fully on or off

         */
        uint16_t getdigitalOut();
        /**
         * Only allows you to send fully on or off

         */
        int setdigitalOut(uint8_t data);

        /**
         * get vout

         */
        float getVOutasVoltage(float vcc);

        /**
         * set vout

         */
        void setVOutasVoltage(float output, float vcc);


    private:
        TwoWire* _wire;
};

#endif