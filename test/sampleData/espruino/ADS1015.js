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
 * Auto-generated file for ADS1015 v0.1.0.
 * Generated from peripherals/ADS1015.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * Texas Instruments Analog-Digital Converter

  */


var ChannelValues = {
  CHANNEL_1: 0, // Channel 1
  CHANNEL_2: 1, // Channel 2
  CHANNEL_3: 2, // Channel 3
  CHANNEL_4: 3, // Channel 4
}
var DeviceOperatingModeValues = {
  CONTINUOUS_CONVERSION: 0, // Continuous Conversion
  SINGLE_SHOT: 1, // Single-shot or power-down state
}
var ProgrammableGainValues = {
  PGA0_256: 5, // Plus/minus 0.256V
  PGA0_512: 4, // Plus/minus 0.512V
  PGA1_024V: 3, // Plus/minus 1.024V
  PGA2_048V: 2, // Plus/minus 2.048V
  PGA4_096V: 1, // Plus/minus 4.096V
  PGA6_144V: 0, // Plus/minus 6.144V
}
var SampleRateValues = {
  HZ128: 0, // 128 samples/second
  HZ1600: 4, // 1600 samples/second
  HZ2400: 5, // 2400 samples/second
  HZ250: 1, // 250 samples/second
  HZ3300: 6, // 3300 samples/second
  HZ490: 2, // 490 samples/second
  HZ920: 3, // 920 samples/second
}

var DEVICE = {
  ADDR: 73,
}

var REGISTER = {
  CONFIG: 1,
  CONVERSION: 0,
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



function ADS1015(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
}

/**
 * Reads the value of register Config
 * ADC config
 * Describes the specifics of the sensing implementation
 *
 * @return {number} The value read from the register
 */
ADS1015.prototype.getConfig = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.CONFIG)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  result = _swapEndian(result, 16)
  return result
}

/**
 * Sets the value of register Config
 * ADC config
 * Describes the specifics of the sensing implementation
 *
 * @param {number} data - The value to write to the register
 */
ADS1015.prototype.setConfig = function(data) {
  data = _swapEndian(data, 16)
  this.i2c.writeTo(this.address, REGISTER.CONFIG, data)
}

/**
 * Reads the value of register Conversion
 * ADC Value
 * Conversion register contains the result of the last conversion
 *
 * @return {number} The value read from the register
 */
ADS1015.prototype.getConversion = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.CONVERSION)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  result = _swapEndian(result, 16)
  return result
}



/**
 * Sets the value of field DeviceOperatingMode
 * Set the operating mode
 * This bit controls the operating mode

 *
 * @param {number} data - The value to write to the field
 */
ADS1015.prototype.setDeviceOperatingMode = function(data) {
  // Bitshift value
  data = data << 8
  // Read current register data
  // '#/registers/Config' > 'Config'
  register = this.getConfig()
  register = register | data
  this.setConfig(register)
}

/**
 * Sets the value of field ProgrammableGain
 * Setup programmable gain
 * This sets the programmable gain for reading analog voltage

 *
 * @param {number} data - The value to write to the field
 */
ADS1015.prototype.setProgrammableGain = function(data) {
  // Bitshift value
  data = data << 9
  // Read current register data
  // '#/registers/Config' > 'Config'
  register = this.getConfig()
  register = register | data
  this.setConfig(register)
}

/**
 * Sets the value of field SampleRate
 * Setup sample rate for reading analog voltage
 * This sets the samples-per-second value

 *
 * @param {number} data - The value to write to the field
 */
ADS1015.prototype.setSampleRate = function(data) {
  // Bitshift value
  data = data << 5
  // Read current register data
  // '#/registers/Config' > 'Config'
  register = this.getConfig()
  register = register | data
  this.setConfig(register)
}

/**
 * Value read from ADC
 * Reads the analog voltage in Volts
 */
ADS1015.prototype.analogread = function(channel) {
  var config = 0 // Variable declaration
  var datumA = 0 // Variable declaration
  var datumB = 0 // Variable declaration
  var processed = 0 // Variable declaration
  var programmableGain = 0 // Variable declaration
  var raw = 0 // Variable declaration

  config = this.getConfig()
  config = (config|(channel << 12))
  config = (config|32768)
  this.setConfig(config)
  raw = this.getConversion()
  datumA = (raw&65280)
  datumA = (datumA >> 8)
  datumB = (raw&255)
  processed = ((datumA << 4)|(datumB >> 4))
  programmableGain = 6144
  processed = ((processed/2047/1000)*programmableGain)
  return processed
}


exports.connect = function(i2c) {
  return new ADS1015(i2c)
}
