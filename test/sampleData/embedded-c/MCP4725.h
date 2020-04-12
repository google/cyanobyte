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


/*
 * Valid values for Digital (binary) output

 */
enum digitalOut {
    DIGITALOUT_GND = 0, // Ground
    DIGITALOUT_VCC = 4095 // Vcc (full power)
};
typedef enum digitalOut digitalOut_t;

int mcp4725_init(int (*connect)(uint8_t));
   
/**
  * If EEPROM is set, the saved voltage output will
 * be loaded from power-on.

*/
int mcp4725_readEEPROM(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
 * If EEPROM is set, the saved voltage output will
 * be loaded from power-on.

 */
int mcp4725_writeEEPROM(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
);
/**
  * VOut = (Vcc * value) / 4096
 * The output is a range between 0 and Vcc with
 * steps of Vcc/4096.
 * In a 3.3v system, each step is 800 microvolts.

*/
int mcp4725_readVOut(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
 * VOut = (Vcc * value) / 4096
 * The output is a range between 0 and Vcc with
 * steps of Vcc/4096.
 * In a 3.3v system, each step is 800 microvolts.

 */
int mcp4725_writeVOut(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
);
/**
 * Only allows you to send fully on or off

 */
int mcp4725_get_digitalout(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Only allows you to send fully on or off

 */
int mcp4725_set_digitalout(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * get vout

*/
void mcp4725_getvout_asvoltage(
    float* val,
    float vcc
);

/**
 * set vout

*/
void mcp4725_setvout_asvoltage(
    float output, float vcc,
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);


#endif