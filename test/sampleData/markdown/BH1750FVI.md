---
title: "BH1750FVI"
linkTitle: "BH1750FVI"
weight: 4
description: >
  Rohm Light Sensor
---


## Device Details

* Device addresses:
35,
92
* Address type 7-bit

## Registers

### ContinuousHRes2Mode
**Continously High-Resolution Mode 2**
* Address 17
* 0-bytes
* Write-only

Start measurement at 0.5lx resolution. Typically 120ms.

### ContinuousHResMode
**Continuously High-Resolution Mode**
* Address 16
* 0-bytes
* Write-only

Start measurement at 1lx resolution. Typically 120ms.

### ContinuouslyLResMode
**Continuously Low-Resolution Mode**
* Address 19
* 0-bytes
* Write-only

Start measurement at 4lx resolution. Typically 16ms.

### OnceHRes2Mode
**One Time High-Resolution Mode2**
* Address 33
* 0-bytes
* Write-only

Start measurement at 0.5lx resolution. Typically 120ms.
Power Down after measurement.


### OnceHResMode
**One Time High-Resolution Mode**
* Address 32
* 0-bytes
* Write-only

Start measurement at 1lx resolution. Typically 120ms.
Power Down after measurement.


### OnceLResMode
**One Time Low-Resolution Mode**
* Address 35
* 0-bytes
* Write-only

Start measurement at 4lx resolution. Typically 16ms.
Power Down after measurement.


### PowerDown
**Power Down**
* Address 0
* 0-bytes
* Write-only

State when the device is not active.

### PowerOn
**Power On**
* Address 1
* 0-bytes
* Write-only

State when device is on and waiting measurement command.

### Reset
**Reset**
* Address 7
* 0-bytes
* Write-only

Reset data register value. Not accepted in Power Down mode.


## Functions

* **_lifecycle**: Sends a POWER ON cmd to device.
* **command**: Commands that can be sent to the device.
* **read**: Read light intensity from device.

## License

_BH1750FVI version 0.1.0. Generated from Cyanobyte Codegen version 0.0.2._

Contact [Nick Felker](mailto:felker@google.com).

Copyright Google Inc. 2020. Published under
[Apache-2.0](https://spdx.org/licenses/Apache-2.0.html#licenseText).