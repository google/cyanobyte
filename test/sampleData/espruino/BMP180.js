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
 * Auto-generated file for BMP180 v0.1.0.
 * Generated from peripherals/BMP180.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * Bosch Digital Temperature / Pressure Sensor

  */



var DEVICE = {
  ADDR: 119,
}

var REGISTER = {
  CONTROL: 244,
  PRESSURECALAC1: 170,
  PRESSURECALAC2: 172,
  PRESSURECALVB1: 182,
  PRESSURECALVB2: 184,
  RESULT: 246,
  TEMPCAL3: 174,
  TEMPCAL4: 176,
  TEMPCAL5: 178,
  TEMPCAL6: 180,
  TEMPCALMC: 188,
  TEMPCALMD: 190,
}




function BMP180(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
}


/**
 * Sets the value of register Control
 * Register to write commands
 * Register stores what the measurement type should be
 *
 * @param {number} data - The value to write to the register
 */
BMP180.prototype.setControl = function(data) {
  this.i2c.writeTo(this.address, REGISTER.CONTROL, data)
}

/**
 * Reads the value of register PressureCalAC1
 * Pressure calibration AC1
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getPressureCalAC1 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSURECALAC1)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register PressureCalAC2
 * Pressure calibration AC2
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getPressureCalAC2 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSURECALAC2)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register PressureCalVB1
 * Pressure calibration VB1
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getPressureCalVB1 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSURECALVB1)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register PressureCalVB2
 * Pressure calibration VB2
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getPressureCalVB2 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSURECALVB2)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register Result
 * Register that stores measurement results
 * Register stores most recent measurement result
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getResult = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.RESULT)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCal3
 * Temperature calibration 3
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCal3 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCAL3)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCal4
 * Temperature calibration 4
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCal4 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCAL4)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCal5
 * Temperature calibration 5
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCal5 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCAL5)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCal6
 * Temperature calibration 6
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCal6 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCAL6)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCalMC
 * Temperature calibration MC
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCalMC = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCALMC)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempCalMD
 * Temperature calibration MD
 * For calibration
 *
 * @return {number} The value read from the register
 */
BMP180.prototype.getTempCalMD = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPCALMD)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Temperature as read by sensor
 * Reads the temperature
 */
BMP180.prototype.temperatureasCelsius = function() {
  var rawComp = 0 // Variable declaration
  var rawMc = 0 // Variable declaration
  var rawMd = 0 // Variable declaration
  var temperature = 0 // Variable declaration
  var varAc5 = 0 // Variable declaration
  var varAc6 = 0 // Variable declaration
  var varC5 = 0 // Variable declaration
  var varMc = 0 // Variable declaration
  var varMd = 0 // Variable declaration

  this.setControl(46)
  temperature = this.getResult()
  varAc5 = this.getTempCal5()
  varAc6 = this.getTempCal6()
  varC5 = ((Math.pow(2, -15)/160)*varAc5)
  rawComp = (varC5*(temperature-varAc6))
  rawMc = this.getTempCalMC()
  varMc = ((Math.pow(2, 11)/Math.pow(160, 2))*rawMc)
  rawMd = this.getTempCalMD()
  varMd = (rawMd/160)
  temperature = (rawComp+(varMc/(rawComp+varMd)))
  return temperature
}


exports.connect = function(i2c) {
  return new BMP180(i2c)
}
