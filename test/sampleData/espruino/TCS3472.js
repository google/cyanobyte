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
 * Auto-generated file for TCS3472 v0.1.0.
 * Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * Color Light-to-Digital Converter with IR Filter

  */


var InitValues = {
  POWER: 1, // Power
  RGBC: 2, // Color
}

var DEVICE = {
  ADDR: 41,
}

var REGISTER = {
  BLUE: 186,
  CLEAR: 180,
  ENABLE: 128,
  GREEN: 184,
  RED: 182,
}




function TCS3472(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
  this._lifecycle_begin()
}

/**
 * Reads the value of register blue
 * Blue channel
 * Blue light as an int. Divide by ambient light to get scaled number.
 *
 * @return {number} The value read from the register
 */
TCS3472.prototype.getblue = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.BLUE)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register clear
 * Clear channel
 * This is the ambient amount of detected light.
 *
 * @return {number} The value read from the register
 */
TCS3472.prototype.getclear = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.CLEAR)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register enable
 * Enable
 * Enable specific components of the peripheral
 *
 * @return {number} The value read from the register
 */
TCS3472.prototype.getenable = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ENABLE)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register enable
 * Enable
 * Enable specific components of the peripheral
 *
 * @param {number} data - The value to write to the register
 */
TCS3472.prototype.setenable = function(data) {
  this.i2c.writeTo(this.address, REGISTER.ENABLE, data)
}

/**
 * Reads the value of register green
 * Green channel
 * Green light as an int. Divide by ambient light to get scaled number.
 *
 * @return {number} The value read from the register
 */
TCS3472.prototype.getgreen = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.GREEN)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register red
 * Red channel
 * Red light as an int. Divide by ambient light to get scaled number.
 *
 * @return {number} The value read from the register
 */
TCS3472.prototype.getred = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.RED)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of field init
 * Setup the device configuration
 * Enable RGBC and Power
 *
 * @return {number} The value of the field
 */
TCS3472.prototype.getinit = function() {
  // Read register data
  // '#/registers/enable' > 'enable'
  var register = this.getenable()
  // Mask register value
  register = register & 0b0000000011111111
  return register
}
/**
 * Sets the value of field init
 * Setup the device configuration
 * Enable RGBC and Power
 *
 * @param {number} data - The value to write to the field
 */
TCS3472.prototype.setinit = function(data) {
  // Read current register data
  // '#/registers/enable' > 'enable'
  register = this.getenable()
  register = register | data
  this.setenable(register)
}

/**
 * Code to run when device class is constructed
 * Enables features on device
 */
TCS3472.prototype._lifecycleBegin = function() {
  var enables = 0 // Variable declaration

  enables = (1+2)
  this.setenable(enables)
}


exports.connect = function(i2c) {
  return new TCS3472(i2c)
}
