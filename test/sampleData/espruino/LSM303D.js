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
 * Auto-generated file for LSM303D v0.1.0.
 * Generated from peripherals/LSM303D.yaml using Cyanobyte Codegen v0.1.0
 */

 /**
  * STMicroelectronics accelerometer and magnetometer

  */



var DEVICE = {
  ADDR: 29,
}

var REGISTER = {
  ACCELEROMETERX_HIGH: 169,
  ACCELEROMETERX_LOW: 168,
  ACCELEROMETERY_HIGH: 171,
  ACCELEROMETERY_LOW: 170,
  ACCELEROMETERZ_HIGH: 173,
  ACCELEROMETERZ_LOW: 172,
  MAGNETOMETERX_HIGH: 137,
  MAGNETOMETERX_LOW: 136,
  MAGNETOMETERY_HIGH: 139,
  MAGNETOMETERY_LOW: 138,
  MAGNETOMETERZ_HIGH: 141,
  MAGNETOMETERZ_LOW: 140,
}




function LSM303D(i2c) {
  this.address = DEVICE.ADDR
  this.i2c = i2c // Assume i2c is already setup
}

/**
 * Reads the value of register AccelerometerX_High
 * Accelerometer X
 * Raw accelerometer data on X plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerX_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERX_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register AccelerometerX_Low
 * Accelerometer X
 * Raw accelerometer data on X plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerX_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERX_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register AccelerometerY_High
 * Accelerometer Y
 * Raw accelerometer data on Y plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerY_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERY_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register AccelerometerY_Low
 * Accelerometer Y
 * Raw accelerometer data on Y plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerY_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERY_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register AccelerometerZ_High
 * Accelerometer Z
 * Raw accelerometer data on Z plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerZ_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERZ_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register AccelerometerZ_Low
 * Accelerometer Z
 * Raw accelerometer data on Z plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getAccelerometerZ_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.ACCELEROMETERZ_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerX_High
 * Magnetometer X
 * Raw magnetometer data on X plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerX_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERX_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerX_Low
 * Magnetometer X
 * Raw magnetometer data on X plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerX_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERX_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerY_High
 * Magnetometer Y
 * Raw magnetometer data on Y plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerY_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERY_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerY_Low
 * Magnetometer Y
 * Raw magnetometer data on Y plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerY_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERY_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerZ_High
 * Magnetometer Z
 * Raw magnetometer data on Z plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerZ_High = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERZ_HIGH)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Reads the value of register MagnetometerZ_Low
 * Magnetometer Z
 * Raw magnetometer data on Z plane
 *
 * @return {number} The value read from the register
 */
LSM303D.prototype.getMagnetometerZ_Low = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.MAGNETOMETERZ_LOW)
  var read = this.i2c.readFrom(this.address, 1) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  return result
}


/**
 * Acceleration as read by sensor
 * Measures the current acceleration
 */
LSM303D.prototype.accelerationasG = function() {
  var accelerationScale = 0 // Variable declaration
  var valueX = 0 // Variable declaration
  var valueY = 0 // Variable declaration
  var valueZ = 0 // Variable declaration

  accelerationScale = 2
  valueX = this.accelerationxPlane()
  valueY = this.accelerationyPlane()
  valueZ = this.accelerationzPlane()
  valueX = ((valueX/Math.pow(2, 15))*accelerationScale)
  valueY = ((valueY/Math.pow(2, 15))*accelerationScale)
  valueZ = ((valueZ/Math.pow(2, 15))*accelerationScale)
  return [valueX, valueY, valueZ]
}

/**
 * Acceleration as read by sensor
 * Measures the current acceleration
 */
LSM303D.prototype.accelerationxPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getAccelerometerX_Low()
  upper = this.getAccelerometerX_High()
  datum = ((upper << 8)+lower)
  return datum
}

/**
 * Acceleration as read by sensor
 * Measures the current acceleration
 */
LSM303D.prototype.accelerationyPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getAccelerometerY_Low()
  upper = this.getAccelerometerY_High()
  datum = ((upper << 8)+lower)
  return datum
}

/**
 * Acceleration as read by sensor
 * Measures the current acceleration
 */
LSM303D.prototype.accelerationzPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getAccelerometerZ_Low()
  upper = this.getAccelerometerZ_High()
  datum = ((upper << 8)+lower)
  return datum
}

/**
 * Orientation data as read by sensor
 * Reads the magnetic orientation
 */
LSM303D.prototype.orientationheading = function() {
  var dividend = 0 // Variable declaration
  var heading = 0 // Variable declaration
  var valueX = 0 // Variable declaration
  var valueY = 0 // Variable declaration

  valueX = this.orientationxPlane()
  valueY = this.orientationyPlane()
  dividend = (valueX/valueY)
  heading = Math.atan(dividend)
  heading = (heading%(2*3.141592653589793))
  heading = ((heading/3.141592653589793)*180)
  return heading
}

/**
 * Orientation data as read by sensor
 * Reads the magnetic orientation
 */
LSM303D.prototype.orientationxPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getMagnetometerX_Low()
  upper = this.getMagnetometerX_High()
  datum = ((upper << 8)+lower)
  return datum
}

/**
 * Orientation data as read by sensor
 * Reads the magnetic orientation
 */
LSM303D.prototype.orientationyPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getMagnetometerY_Low()
  upper = this.getMagnetometerY_High()
  datum = ((upper << 8)+lower)
  return datum
}

/**
 * Orientation data as read by sensor
 * Reads the magnetic orientation
 */
LSM303D.prototype.orientationzPlane = function() {
  var datum = 0 // Variable declaration
  var lower = 0 // Variable declaration
  var upper = 0 // Variable declaration

  lower = this.getMagnetometerZ_Low()
  upper = this.getMagnetometerZ_High()
  datum = ((upper << 8)+lower)
  return datum
}


exports.connect = function(i2c) {
  return new LSM303D(i2c)
}
