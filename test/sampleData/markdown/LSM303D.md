---
title: "LSM303D"
linkTitle: "LSM303D"
weight: 4
description: >
  STMicroelectronics accelerometer and magnetometer
---


## Device Details

* Device address 29
* Address type 7-bit

## Registers

### AccelerometerX_High
**Accelerometer X-Axis MSB**
* Address 169
* 8-bytes
* Read-only

Most-significant bits for raw accelerometer data on X plane.

### AccelerometerX_Low
**Accelerometer X-Axis LSB**
* Address 168
* 8-bytes
* Read-only

Least-significant bits for raw accelerometer data on X plane.

### AccelerometerY_High
**Accelerometer Y-Axis MSB**
* Address 171
* 8-bytes
* Read-only

Most-significant bits for raw accelerometer data on Y plane.

### AccelerometerY_Low
**Accelerometer Y-Axis LSB**
* Address 170
* 8-bytes
* Read-only

Least-significant bits for raw accelerometer data on Y plane.

### AccelerometerZ_High
**Accelerometer Z-Axis MSB**
* Address 173
* 8-bytes
* Read-only

Most-significant bits for raw accelerometer data on Z plane.

### AccelerometerZ_Low
**Accelerometer Z-Axis LSB**
* Address 172
* 8-bytes
* Read-only

Least-significant bits for raw accelerometer data on Z plane.

### MagnetometerX_High
**Magnetometer X-Axis MSB**
* Address 137
* 8-bytes
* Read-only

Most-significant bits for raw magnetometer data on X plane.

### MagnetometerX_Low
**Magnetometer X-Axis LSB**
* Address 136
* 8-bytes
* Read-only

Least-significant bits for raw magnetometer data on X plane.

### MagnetometerY_High
**Magnetometer Y-Axis MSB**
* Address 139
* 8-bytes
* Read-only

Most-significant bits for raw magnetometer data on Y plane.

### MagnetometerY_Low
**Magnetometer Y-Axis LSB**
* Address 138
* 8-bytes
* Read-only

Least-significant bits for raw magnetometer data on Y plane.

### MagnetometerZ_High
**Magnetometer Z-Axis MSB**
* Address 141
* 8-bytes
* Read-only

Most-significant bits for raw magnetometer data on Z plane.

### MagnetometerZ_Low
**Magnetometer Z-Axis LSB**
* Address 140
* 8-bytes
* Read-only

Least-significant bits for raw magnetometer data on Z plane.


## Functions

* **acceleration**: Measures the current acceleration for each plane.
* **orientation**: Reads the magnetic orientation for each plane and compass heading.

## License

_LSM303D version 0.1.0. Generated from Cyanobyte Codegen version 0.0.2._

Contact [Nick Felker](mailto:felker@google.com).

Copyright Google Inc. 2019. Published under
[Apache-2.0](https://spdx.org/licenses/Apache-2.0.html#licenseText).