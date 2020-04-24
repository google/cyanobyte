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
 */

 /**
  * Rohm Light Sensor

  */



var DEVICE = {
  ADDR_35: 35,
  ADDR_92: 92,
}

var REGISTER = {
  CONTINUOUSHRES2MODE: 17,
  CONTINUOUSHRESMODE: 16,
  CONTINUOUSLYLRESMODE: 19,
  ONCEHRES2MODE: 33,
  ONCEHRESMODE: 32,
  ONCELRESMODE: 35,
  POWERDOWN: 0,
  POWERON: 1,
  RESET: 7,
}




function BH1750FVI(i2c, address) {
  this.address = address
  this.i2c = i2c // Assume i2c is already setup
  this._lifecycle_begin()
}


/**
 * Sets the value of register ContinuousHRes2Mode
 * Continously H-Resolution Mode2
 * Start measurement at 0.5lx resolution. Typically 120ms.
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setContinuousHRes2Mode = function() {
  this.i2c.writeTo(this.address, REGISTER.CONTINUOUSHRES2MODE)
}


/**
 * Sets the value of register ContinuousHResMode
 * Continuously H-Resolution Mode
 * Start measurement at 1lx resolution. Typically 120ms.
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setContinuousHResMode = function() {
  this.i2c.writeTo(this.address, REGISTER.CONTINUOUSHRESMODE)
}


/**
 * Sets the value of register ContinuouslyLResMode
 * Continuously L-Resolution Mode
 * Start measurement at 4lx resolution. Typically 16ms.
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setContinuouslyLResMode = function() {
  this.i2c.writeTo(this.address, REGISTER.CONTINUOUSLYLRESMODE)
}


/**
 * Sets the value of register OnceHRes2Mode
 * One Time H-Resolution Mode2
 * Start measurement at 0.5lx resolution. Typically 120ms.
Power Down after measurement.

 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setOnceHRes2Mode = function() {
  this.i2c.writeTo(this.address, REGISTER.ONCEHRES2MODE)
}


/**
 * Sets the value of register OnceHResMode
 * One Time H-Resolution Mode
 * Start measurement at 1lx resolution. Typically 120ms.
Power Down after measurement.

 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setOnceHResMode = function() {
  this.i2c.writeTo(this.address, REGISTER.ONCEHRESMODE)
}


/**
 * Sets the value of register OnceLResMode
 * One Time L-Resolution Mode
 * Start measurement at 4lx resolution. Typically 16ms.
Power Down after measurement.

 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setOnceLResMode = function() {
  this.i2c.writeTo(this.address, REGISTER.ONCELRESMODE)
}


/**
 * Sets the value of register PowerDown
 * Power Down
 * No active state
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setPowerDown = function() {
  this.i2c.writeTo(this.address, REGISTER.POWERDOWN)
}


/**
 * Sets the value of register PowerOn
 * Power On
 * Waiting for measurement command
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setPowerOn = function() {
  this.i2c.writeTo(this.address, REGISTER.POWERON)
}


/**
 * Sets the value of register Reset
 * Reset
 * Reset data register value. Not accepted in Power Down mode.
 *
 * @param {number} data - The value to write to the register
 */
BH1750FVI.prototype.setReset = function() {
  this.i2c.writeTo(this.address, REGISTER.RESET)
}

/**
 * Powers on the device
 * Sends a POWER ON cmd to device
 */
BH1750FVI.prototype._lifecycleBegin = function() {

  this.setPowerOn()
}

/**
 * Commands to device
 * Things you can do to device
 */
BH1750FVI.prototype.commandPowerDown = function() {

  this.setPowerDown()
}

/**
 * Commands to device
 * Things you can do to device
 */
BH1750FVI.prototype.commandReset = function() {

  this.setPowerOn()
  this.setReset()
}

/**
 * Read light intensity from device
 * Read light intensity from device
 */
BH1750FVI.prototype.readLightIntensity = function() {
  var intensity = 0 // Variable declaration

  intensity = 0
  var _temp = this.i2c.readFrom(this.address, 2)
  for (var n of _temp) {
    intensity = intensity << 8 | n
  }
  return intensity
}


exports.connect = function(i2c, address) {
  return new BH1750FVI(i2c, address)
}
