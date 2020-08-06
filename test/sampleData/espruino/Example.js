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
 * Auto-generated file for Example v0.1.0.
 * Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * Example of a package

  */


var FieldBValues = {
  VAL_1: 1, // Value 1
  VAL_2: 2, // Value 2
  VAL_3: 4, // Value 3
  VAL_4: 8, // Value 4
}

var DEVICE = {
  ADDR_16: 16,
  ADDR_32: 32,
  ADDR_48: 48,
}

var REGISTER = {
  REGISTERA: 0,
  REGISTERB: 1,
  REGISTERC: 2,
  REGISTERD: 3,
}




function Example(i2c, address) {
  this.address = address
  this.i2c = i2c // Assume i2c is already setup
  this._lifecycle_begin()
}

/**
 * Reads the value of register RegisterA
 * First example
 * An 8-bit register
 *
 * @return {number} The value read from the register
 */
Example.prototype.getRegisterA = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.REGISTERA)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register RegisterA
 * First example
 * An 8-bit register
 *
 * @param {number} data - The value to write to the register
 */
Example.prototype.setRegisterA = function(data) {
  this.i2c.writeTo(this.address, REGISTER.REGISTERA, data)
}

/**
 * Reads the value of register RegisterB
 * Second example
 * A 16-bit register
 *
 * @return {number} The value read from the register
 */
Example.prototype.getRegisterB = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.REGISTERB)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register RegisterB
 * Second example
 * A 16-bit register
 *
 * @param {number} data - The value to write to the register
 */
Example.prototype.setRegisterB = function(data) {
  this.i2c.writeTo(this.address, REGISTER.REGISTERB, data)
}

/**
 * Reads the value of register RegisterC
 * Third example
 * A 32-bit register
 *
 * @return {number} The value read from the register
 */
Example.prototype.getRegisterC = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.REGISTERC)
  var read = this.i2c.readFrom(this.address, 4) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register RegisterC
 * Third example
 * A 32-bit register
 *
 * @param {number} data - The value to write to the register
 */
Example.prototype.setRegisterC = function(data) {
  this.i2c.writeTo(this.address, REGISTER.REGISTERC, data)
}

/**
 * Reads the value of register RegisterD
 * Fourth example
 * A dummy register that has no data
 *
 * @return {number} The value read from the register
 */
Example.prototype.getRegisterD = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.REGISTERD)
  var read = this.i2c.readFrom(this.address, 0) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}

/**
 * Sets the value of register RegisterD
 * Fourth example
 * A dummy register that has no data
 *
 * @param {number} data - The value to write to the register
 */
Example.prototype.setRegisterD = function() {
  this.i2c.writeTo(this.address, REGISTER.REGISTERD)
}

/**
 * Reads the value of field FieldA
 * Read-only fields for RegisterA
 * This is a few bits
 *
 * @return {number} The value of the field
 */
Example.prototype.getFieldA = function() {
  // Read register data
  // '#/registers/RegisterA' > 'RegisterA'
  var register = this.getRegisterA()
  // Mask register value
  register = register & 0b0000000011110000
  // Bitshift value
  register = register >> 4
  return register
}

/**
 * Sets the value of field FieldB
 * Write-only fields for RegisterA
 * This is fewer bits
 *
 * @param {number} data - The value to write to the field
 */
Example.prototype.setFieldB = function(data) {
  // Bitshift value
  data = data << 2
  // Read current register data
  // '#/registers/RegisterA' > 'RegisterA'
  register = this.getRegisterA()
  register = register | data
  this.setRegisterA(register)
}

/**
 * Reads the value of field FieldC
 * Read/write field for RegisterA
 * A single-bit
 *
 * @return {number} The value of the field
 */
Example.prototype.getFieldC = function() {
  // Read register data
  // '#/registers/RegisterA' > 'RegisterA'
  var register = this.getRegisterA()
  // Mask register value
  register = register & 0b0000000000000010
  // Bitshift value
  register = register >> 1
  return register
}
/**
 * Sets the value of field FieldC
 * Read/write field for RegisterA
 * A single-bit
 *
 * @param {number} data - The value to write to the field
 */
Example.prototype.setFieldC = function(data) {
  // Bitshift value
  data = data << 1
  // Read current register data
  // '#/registers/RegisterA' > 'RegisterA'
  register = this.getRegisterA()
  register = register | data
  this.setRegisterA(register)
}


/**
 * Code to run when device class is constructed
 * Enables features on device
 */
Example.prototype._lifecycleBegin = function() {
  var output = 0 // Variable declaration

  output = 1
  this.setRegisterA(output)
  return output
}

/**
 * Code to run when device class is constructed
 * Enables features on device
 */
Example.prototype._lifecycleEnd = function() {
  var output = 0 // Variable declaration

  output = 1
  this.setRegisterA(output)
  return output
}

/**
 * Return a value
 * Computes and returns
 */
Example.prototype.ReturnArray = function() {
  var summation = 0 // Variable declaration

  summation = (1024+1024)
  this.setRegisterA(summation)
  return [summation, summation]
}

/**
 * Return a value
 * Computes and returns
 */
Example.prototype.ReturnNumber = function() {
  var summation = 0 // Variable declaration

  summation = (1024+1024)
  this.setRegisterA(summation)
  return summation
}

/**
 * Return a value
 * Computes and returns
 */
Example.prototype.ReturnVoid = function() {
  var summation = 0 // Variable declaration

  summation = (1024+1024)
  this.setRegisterA(summation)
}


exports.connect = function(i2c, address) {
  return new Example(i2c, address)
}
