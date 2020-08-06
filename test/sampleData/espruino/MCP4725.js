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
 */

 /**
  * Microchip 4725 Digital-to-Analog Converter

  */


var DigitalOutValues = {
  GND: 0, // Ground
  VCC: 4095, // Vcc (full power)
}

var DEVICE = {
  ADDR: 98,
}

var REGISTER = {
  EEPROM: 96,
  VOUT: 64,
}

/**
 * Swap the endianness of a number
 */
function _swapEndian(val, length) {
  if (length <= 8) {
    return val
  } else if (length <= 16) {
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8
  } else if (length <= 32) {
    return ((val & 0xFF000000) >> 24 |
           (val & 0x00FF0000) >> 8 |
           (val & 0x0000FF00) << 8 |
           (val & 0x000000FF) << 24)
  }
  throw new Error('Cannot swap endianness for length ' + length)
}



function MCP4725(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
}

/**
 * Reads the value of register EEPROM
 * EEPROM
 * If EEPROM is set, the saved voltage output will
be loaded from power-on.

 *
 * @return {number} The value read from the register
 */
MCP4725.prototype.getEEPROM = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.EEPROM)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  result = _swapEndian(result, 12)
  return result
}

/**
 * Sets the value of register EEPROM
 * EEPROM
 * If EEPROM is set, the saved voltage output will
be loaded from power-on.

 *
 * @param {number} data - The value to write to the register
 */
MCP4725.prototype.setEEPROM = function(data) {
  data = _swapEndian(data, 12)
  this.i2c.writeTo(this.address, REGISTER.EEPROM, data)
}

/**
 * Reads the value of register VOut
 * Output voltage
 * VOut = (Vcc * value) / 4096
The output is a range between 0 and Vcc with
steps of Vcc/4096.
In a 3.3v system, each step is 800 microvolts.

 *
 * @return {number} The value read from the register
 */
MCP4725.prototype.getVOut = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.VOUT)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  result = _swapEndian(result, 12)
  return result
}

/**
 * Sets the value of register VOut
 * Output voltage
 * VOut = (Vcc * value) / 4096
The output is a range between 0 and Vcc with
steps of Vcc/4096.
In a 3.3v system, each step is 800 microvolts.

 *
 * @param {number} data - The value to write to the register
 */
MCP4725.prototype.setVOut = function(data) {
  data = _swapEndian(data, 12)
  this.i2c.writeTo(this.address, REGISTER.VOUT, data)
}

/**
 * Reads the value of field digitalOut
 * Digital (binary) output
 * Only allows you to send fully on or off

 *
 * @return {number} The value of the field
 */
MCP4725.prototype.getdigitalOut = function() {
  // Read register data
  // '#/registers/EEPROM' > 'EEPROM'
  var register = this.getEEPROM()
  // Mask register value
  register = register & 0b0001111111111111
  return register
}
/**
 * Sets the value of field digitalOut
 * Digital (binary) output
 * Only allows you to send fully on or off

 *
 * @param {number} data - The value to write to the field
 */
MCP4725.prototype.setdigitalOut = function(data) {
  // Read current register data
  // '#/registers/EEPROM' > 'EEPROM'
  register = this.getEEPROM()
  register = register | data
  this.setEEPROM(register)
}

/**
 * Get output voltage
 * get vout
 */
MCP4725.prototype.getVOutasVoltage = function(vcc) {
  var voltage = 0 // Variable declaration

  // Read value of register into a variable
  var value = this.getEEPROM()
  voltage = value / 4096 * vcc
  return voltage
}

/**
 * Set output voltage
 * set vout
 */
MCP4725.prototype.setVOutasVoltage = function(output, vcc) {

  output = output / vcc * 4096
  this.setEEPROM(output)
}


exports.connect = function(i2c) {
  return new MCP4725(i2c)
}
