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
 * Auto-generated file for BMP280 v0.1.0.
 * Generated from peripherals/BMP280.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * Bosch Digital Pressure Sensor

  */



var DEVICE = {
  ADDR: 119,
}

var REGISTER = {
  DIGP1: 142,
  DIGP2: 144,
  DIGP3: 146,
  DIGP4: 148,
  DIGP5: 150,
  DIGP6: 152,
  DIGP7: 154,
  DIGP8: 156,
  DIGP9: 158,
  DIGT1: 136,
  DIGT2: 138,
  DIGT3: 140,
  PRESSURELSB: 248,
  PRESSUREMSB: 247,
  PRESSUREXLSB: 249,
  TEMPLSB: 251,
  TEMPMSB: 250,
  TEMPXLSB: 252,
}


/**
 * Convert unsigned integer to signed integer
 */
function _sign(val, length) {
  if (val & (1 << (length - 1))) {
    return val - (1 << length)
  }
  return val
}


function BMP280(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
}

/**
 * Reads the value of register DigP1
 * Digital Pressure Compensation 1
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP1 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP1)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register DigP2
 * Digital Pressure Compensation 2
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP2 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP2)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP3
 * Digital Pressure Compensation 3
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP3 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP3)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP4
 * Digital Pressure Compensation 4
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP4 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP4)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP5
 * Digital Pressure Compensation 5
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP5 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP5)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP6
 * Digital Pressure Compensation 6
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP6 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP6)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP7
 * Digital Pressure Compensation 7
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP7 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP7)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP8
 * Digital Pressure Compensation 8
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP8 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP8)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigP9
 * Digital Pressure Compensation 9
 * Used for Pascals conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigP9 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGP9)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigT1
 * Digital Temperature Compensation 1
 * Used for Celcius conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigT1 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGT1)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register DigT2
 * Digital Temperature Compensation 2
 * Used for Celcius conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigT2 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGT2)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register DigT3
 * Digital Temperature Compensation 3
 * Used for Celcius conversion
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getDigT3 = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.DIGT3)
  var read = this.i2c.readFrom(this.address, 2) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  // Unsigned > Signed integer
  result = _sign(result, 16)
  return result
}


/**
 * Reads the value of register PressureLsb
 * Pressure LSB
 * Part 2 of Pressure
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getPressureLsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSURELSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register PressureMsb
 * Pressure MSB
 * Part 1 of Pressure
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getPressureMsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSUREMSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register PressureXlsb
 * Pressure XLSB
 * Part 3 of Pressure
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getPressureXlsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.PRESSUREXLSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempLsb
 * Temperature LSB
 * Part 2 of temperature
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getTempLsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPLSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempMsb
 * Temperature MSB
 * Part 1 of temperature
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getTempMsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPMSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register TempXlsb
 * Temperature XLSB
 * Final part of temperature
 *
 * @return {number} The value read from the register
 */
BMP280.prototype.getTempXlsb = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.TEMPXLSB)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Pressure as read by sensor
 * Reads the atmospheric pressure
 */
BMP280.prototype.pressureasHpa = function() {
  var hpa = 0 // Variable declaration
  var rawComp1 = 0 // Variable declaration
  var rawComp2 = 0 // Variable declaration
  var rawComp3 = 0 // Variable declaration
  var rawPressure = 0 // Variable declaration
  var rawTemperature = 0 // Variable declaration
  var valueDP1 = 0 // Variable declaration
  var valueDP2 = 0 // Variable declaration
  var valueDP3 = 0 // Variable declaration
  var valueDP4 = 0 // Variable declaration
  var valueDP5 = 0 // Variable declaration
  var valueDP6 = 0 // Variable declaration
  var valueDP7 = 0 // Variable declaration
  var valueDP8 = 0 // Variable declaration
  var valueDP9 = 0 // Variable declaration
  var valueLsb = 0 // Variable declaration
  var valueMsb = 0 // Variable declaration
  var valueXlsb = 0 // Variable declaration

  valueMsb = this.getPressureMsb()
  valueLsb = this.getPressureLsb()
  valueXlsb = this.getPressureXlsb()
  valueDP1 = this.getDigP1()
  valueDP2 = this.getDigP2()
  valueDP3 = this.getDigP3()
  valueDP4 = this.getDigP4()
  valueDP5 = this.getDigP5()
  valueDP6 = this.getDigP6()
  valueDP7 = this.getDigP7()
  valueDP8 = this.getDigP8()
  valueDP9 = this.getDigP9()
  rawTemperature = this.temperatureasCelsius()
  rawTemperature = (rawTemperature*5120.0)
  rawPressure = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4))
  rawComp1 = ((rawTemperature/2)-64000.0)
  rawComp2 = ((rawComp1*rawComp1*valueDP6)/32768.0)
  rawComp2 = (rawComp2+(rawComp1*valueDP5*2.0))
  rawComp2 = ((rawComp2/4.0)+(valueDP4*65536.0))
  rawComp3 = (valueDP3*rawComp1*rawComp1)
  rawComp1 = (((rawComp3/524288.0)+(valueDP2*rawComp1))/524288.0)
  rawComp1 = ((1.0+(rawComp1/32768.0))*valueDP1)
  hpa = (1048576.0-rawPressure)
  hpa = ((hpa-(rawComp2/4096.0))*(6250.0/rawComp1))
  rawComp1 = ((valueDP9*hpa*hpa)/2147483648.0)
  rawComp2 = ((hpa*valueDP8)/32768.0)
  hpa = (hpa+((rawComp1+rawComp2+valueDP7)/16.0))
  hpa = (hpa/100.0)
  return hpa
}

/**
 * Pressure as read by sensor
 * Reads the atmospheric pressure
 */
BMP280.prototype.pressureasRaw = function() {
  var output = 0 // Variable declaration
  var valueLsb = 0 // Variable declaration
  var valueMsb = 0 // Variable declaration
  var valueXlsb = 0 // Variable declaration

  valueMsb = this.getPressureMsb()
  valueLsb = this.getPressureLsb()
  valueXlsb = this.getPressureXlsb()
  output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4))
  return output
}

/**
 * Temperature as read by sensor
 * Reads the temperature
 */
BMP280.prototype.temperatureasCelsius = function() {
  var celsius = 0 // Variable declaration
  var rawComp1 = 0 // Variable declaration
  var rawComp2 = 0 // Variable declaration
  var rawComp3 = 0 // Variable declaration
  var rawTemp = 0 // Variable declaration
  var valueDT1 = 0 // Variable declaration
  var valueDT2 = 0 // Variable declaration
  var valueDT3 = 0 // Variable declaration
  var valueLsb = 0 // Variable declaration
  var valueMsb = 0 // Variable declaration
  var valueXlsb = 0 // Variable declaration

  valueMsb = this.getTempMsb()
  valueLsb = this.getTempLsb()
  valueXlsb = this.getTempXlsb()
  valueDT1 = this.getDigT1()
  valueDT2 = this.getDigT2()
  valueDT3 = this.getDigT3()
  rawTemp = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4))
  rawComp1 = (((rawTemp/16384.0)-(valueDT1/1024.0))*valueDT2)
  rawComp3 = ((rawTemp/131072.0)-(valueDT1/8192.0))
  rawComp2 = (rawComp3*rawComp3*valueDT3)
  celsius = ((rawComp1+rawComp2)/5120.0)
  return celsius
}

/**
 * Temperature as read by sensor
 * Reads the temperature
 */
BMP280.prototype.temperatureasRaw = function() {
  var output = 0 // Variable declaration
  var valueLsb = 0 // Variable declaration
  var valueMsb = 0 // Variable declaration
  var valueXlsb = 0 // Variable declaration

  valueMsb = this.getTempMsb()
  valueLsb = this.getTempLsb()
  valueXlsb = this.getTempXlsb()
  output = ((valueMsb << 12)+(valueLsb << 4)+(valueXlsb >> 4))
  return output
}


exports.connect = function(i2c) {
  return new BMP280(i2c)
}
