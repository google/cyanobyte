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
 */

 /**
  * This is a test description

  */


var LimitHysteresisValues = {
  TEMP_0C: 0, // 0°C (power-up default)
  TEMP_1C5: 1, // +1.5°C
  TEMP_3C: 2, // +3.0°C
  TEMP_6C: 3, // +6.0°C
}
var ShutdownModeValues = {
  CONTINOUSCONVERSION: 0, // Continuous conversion (power-up default)
  SHUTDOWN: 1, // Shutdown (Low-Power mode)
}

var DEVICE = {
  ADDR_24: 24,
  ADDR_25: 25,
  ADDR_26: 26,
  ADDR_27: 27,
  ADDR_28: 28,
  ADDR_29: 29,
  ADDR_30: 30,
  ADDR_31: 31,
}

var REGISTER = {
  CONFIGURATION: 1,
}




function MCP9808(i2c, address) {
  this.address = address
  this.i2c = i2c // Assume i2c is already setup
}

/**
 * Reads the value of register configuration
 * Configuration Register
 * The MCP9808 has a 16-bit Configuration register (CONFIG) that
allows the user to set various functions for a robust temperature
monitoring system.
Bits 10 through 0 are used to select the temperature alert output
hysteresis, device shutdown or Low-Power mode, temperature boundary
and critical temperature lock, and temperature Alert output
enable/disable.
In addition, Alert output condition (output set for TUPPER and
TLOWER temperature boundary or TCRIT only), Alert output status
and Alert output polarity and mode (Comparator Output or Interrupt
Output mode) are user-configurable.

 *
 * @return {number} The value read from the register
 */
MCP9808.prototype.getconfiguration = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.CONFIGURATION)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register configuration
 * Configuration Register
 * The MCP9808 has a 16-bit Configuration register (CONFIG) that
allows the user to set various functions for a robust temperature
monitoring system.
Bits 10 through 0 are used to select the temperature alert output
hysteresis, device shutdown or Low-Power mode, temperature boundary
and critical temperature lock, and temperature Alert output
enable/disable.
In addition, Alert output condition (output set for TUPPER and
TLOWER temperature boundary or TCRIT only), Alert output status
and Alert output polarity and mode (Comparator Output or Interrupt
Output mode) are user-configurable.

 *
 * @param {number} data - The value to write to the register
 */
MCP9808.prototype.setconfiguration = function(data) {
  this.i2c.writeTo(this.address, REGISTER.CONFIGURATION, data)
}

/**
 * Reads the value of field limitHysteresis
 * TUPPER and TLOWER Limit Hysteresis bits
 * This bit can not be altered when either of the Lock bits are set
(bit 6 and bit 7). This bit can be programmed in Shutdown mode.

 *
 * @return {number} The value of the field
 */
MCP9808.prototype.getlimitHysteresis = function() {
  // Read register data
  // '#/registers/configuration' > 'configuration'
  var register = this.getconfiguration()
  // Mask register value
  register = register & 0b0000011000000000
  // Bitshift value
  register = register >> 9
  return register
}

/**
 * Reads the value of field shutdownMode
 * Shutdown Mode bit
 * In shutdown, all power-consuming activities are disabled, though
all registers can be written to or read. This bit cannot be set
to ‘1’ when either of the Lock bits is set (bit 6 and bit 7).
However, it can be cleared to ‘0’ for continuous conversion while
locked.

 *
 * @return {number} The value of the field
 */
MCP9808.prototype.getshutdownMode = function() {
  // Read register data
  // '#/registers/configuration' > 'configuration'
  var register = this.getconfiguration()
  // Mask register value
  register = register & 0b0000000100000000
  // Bitshift value
  register = register >> 8
  return register
}


exports.connect = function(i2c, address) {
  return new MCP9808(i2c, address)
}
