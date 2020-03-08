/*
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

int mcp9808_init(char* bus_name, int (*connect)(uint8_t));
   
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