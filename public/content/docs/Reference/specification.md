---
title: "Spec"
linkTitle: "Spec"
weight: 1
description: >
  Cyanobyte specification files
---

A "Cyanobyte specification file" is like a machine-readable implementation of a peripheral datasheet.
It contains metadata about the product, a list of registers, and a series of helper functions to
perform common expected tasks like unit conversion.

This project provides sample specifications to show you how to get started with your own.

* MCP4725
* MCP9808

## Info

All specification files should start with the verison of the Cyanobyte specification they're using.
Currently, the version is `0.1.0`. While the current goal is for a stable, backwards-compatible spec,
it may be possible that backwards compatibility is broken, and need to ensure the codegen tool and
template files will be compatible.

The Info block contains metadata about the peripheral, and key information like software licensing and
contact information.

```yaml
cyanobyte: 0.1.0
info:
    title: MCP9808
    description: This is a test description
    contact:
        name: 'Joe Smith'
        url: 'http://example.com'
        email: 'joe@example.com'
    license:
        name: 'Apache 2.0'
        url: 'https://www.apache.org/licenses/LICENSE-2.0.html'
    version: 0.1.0 # version of this file, in case there are newer versions later on
```

## Communication Metadata
### I2C

Metadata about the communication type is defined in the I2C block. This is the only supported type of
communication.

```yaml
i2c:
    addressType: '7-bit'
    address: 0x18
    addressMask: 0x78
```

## Registers
For communication protocols like I2C, data is usually read and written to peripheral registers.
These are represented by a list.

```yaml
registers:
    - configuration:
        address: 0x01
        length: 16
        title: Configuration Register
        description: The MCP9808 has a 16-bit Configuration register (CONFIG) that allows the user to set various functions for a robust temperature monitoring system. Bits 10 through 0 are used to select the temperature alert output hysteresis, device shutdown or Low-Power mode, temperature boundary and critical temperature lock, and temperature Alert output enable/disable. In addition, Alert output condition (output set for TUPPER and TLOWER temperature boundary or TCRIT only), Alert output status and Alert output polarity and mode (Comparator Output or Interrupt Output mode) are user-configurable
```

## Functions
Functions are sets of logical write or read operations which may require additional logic or an enum.

```yaml
functions:
    - limitHysteresis:
        title: TUPPER and TLOWER Limit Hysteresis bits
        description: |
            This bit can not be altered when either of the Lock bits are set (bit 6 and bit 7). 
            This bit can be programmed in Shutdown mode.
        register: '#/registers/configuration'
        readWrite: 'R'
        bitStart: 10
        bitEnd: 9
        type: 'enum'
        enum:
            - 0C:
                title: 0°C (power-up default)
                value: 0b00
            - 1C5:
                title: +1.5°C
                value: 0b01
            - 3C:
                title: +3.0°C
                value: 0b10
            - 6C:
                title: +6.0°C
                value: 0b11
    - shutdownMode:
        title: Shutdown Mode bit
        description: |
            In shutdown, all power-consuming activities are disabled, though all registers can be written to or read.
            This bit cannot be set to ‘1’ when either of the Lock bits is set (bit 6 and bit 7). However, it can be cleared to ‘0’ for continuous conversion while locked.
        register: '#/registers/configuration'
        readWrite: 'R'
        bitStart: 8
        bitEnd: 8
        type: 'enum'
        enum:
            - continousConversion:
                title: Continuous conversion (power-up default)
                value: 0
            - shutdown:
                title: Shutdown (Low-Power mode)
                value: 1
```

