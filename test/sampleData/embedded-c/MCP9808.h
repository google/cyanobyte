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
* Auto-generated file for MCP9808 v0.1.0.
* Generated from peripherals/MCP9808.yaml using Cyanobyte Codegen v0.1.0
* Class for MCP9808
* This is a test description

*/

#ifndef _MCP9808_H_
#define _MCP9808_H_


/*
 * Valid values for TUPPER and TLOWER Limit Hysteresis bits

 */
enum limitHysteresis {
    LIMITHYSTERESIS_TEMP_0C = 0, // 0°C (power-up default)
    LIMITHYSTERESIS_TEMP_1C5 = 1, // +1.5°C
    LIMITHYSTERESIS_TEMP_3C = 2, // +3.0°C
    LIMITHYSTERESIS_TEMP_6C = 3 // +6.0°C
};
typedef enum limitHysteresis limitHysteresis_t;
/*
 * Valid values for Shutdown Mode bit

 */
enum shutdownMode {
    SHUTDOWNMODE_CONTINOUSCONVERSION = 0, // Continuous conversion (power-up default)
    SHUTDOWNMODE_SHUTDOWN = 1 // Shutdown (Low-Power mode)
};
typedef enum shutdownMode shutdownMode_t;
enum deviceAddress {
    I2C_ADDRESS_24 = 24,
    I2C_ADDRESS_25 = 25,
    I2C_ADDRESS_26 = 26,
    I2C_ADDRESS_27 = 27,
    I2C_ADDRESS_28 = 28,
    I2C_ADDRESS_29 = 29,
    I2C_ADDRESS_30 = 30,
    I2C_ADDRESS_31 = 31
};
typedef enum deviceAddress deviceAddress_t;

int mcp9808_init(deviceAddress_t address, int (*connect)(uint8_t));
   
/**
  * The MCP9808 has a 16-bit Configuration register (CONFIG) that
 * allows the user to set various functions for a robust temperature
 * monitoring system.
 * Bits 10 through 0 are used to select the temperature alert output
 * hysteresis, device shutdown or Low-Power mode, temperature boundary
 * and critical temperature lock, and temperature Alert output
 * enable/disable.
 * In addition, Alert output condition (output set for TUPPER and
 * TLOWER temperature boundary or TCRIT only), Alert output status
 * and Alert output polarity and mode (Comparator Output or Interrupt
 * Output mode) are user-configurable.

*/
int mcp9808_readconfiguration(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
 * The MCP9808 has a 16-bit Configuration register (CONFIG) that
 * allows the user to set various functions for a robust temperature
 * monitoring system.
 * Bits 10 through 0 are used to select the temperature alert output
 * hysteresis, device shutdown or Low-Power mode, temperature boundary
 * and critical temperature lock, and temperature Alert output
 * enable/disable.
 * In addition, Alert output condition (output set for TUPPER and
 * TLOWER temperature boundary or TCRIT only), Alert output status
 * and Alert output polarity and mode (Comparator Output or Interrupt
 * Output mode) are user-configurable.

 */
int mcp9808_writeconfiguration(
    uint16_t* data,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint16_t*, uint8_t)
);
/**
 * This bit can not be altered when either of the Lock bits are set
 * (bit 6 and bit 7). This bit can be programmed in Shutdown mode.

 */
int mcp9808_get_limithysteresis(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * In shutdown, all power-consuming activities are disabled, though
 * all registers can be written to or read. This bit cannot be set
 * to ‘1’ when either of the Lock bits is set (bit 6 and bit 7).
 * However, it can be cleared to ‘0’ for continuous conversion while
 * locked.

 */
int mcp9808_get_shutdownmode(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);


#endif