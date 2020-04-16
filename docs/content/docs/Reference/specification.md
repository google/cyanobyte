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

## Fields
Fields are sets of logical write or read operations which may require additional logic or an enum.

```yaml
fields:
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

## Functions

Functions are chunks of simple computation which can be used to generate
functions on the embedded device. A number of mathematical operations are
available.

```yaml
functions:
  temperature:
    title: Temperature as read by sensor
    description: Reads the temperature
    computed:
      asCelsius:
        variables:
          valueMsb: int8
          valueLsb: int8
          valueXlsb: int8
          valueDT1: int8
          valueDT2: int8
          valueDT3: int8
          rawTemp: int16
          rawComp1: int16
          rawComp2: int16
          rawComp3: int16
          celsius: float32
        logic:
          - valueMsb: '#/registers/TempMsb'
          - valueLsb: '#/registers/TempLsb'
          - valueXlsb: '#/registers/TempXlsb'
          - valueDT1: '#/registers/DigT1'
          - valueDT2: '#/registers/DigT2'
          - valueDT3: '#/registers/DigT3'
          - rawTemp:
            - sum:
              - bitShiftLeft:
                var: valueMsb
                bits: 12
              - bitShiftLeft:
                var: valueLsb
                bits: 4
              - bitShiftRight:
                var: valueXlsb
                bits: 4
          - rawComp1:
            - product:
              - difference:
                - division:
                  - rawTemp
                  - 16384.0
                - division:
                  - valueDT1
                  - 1024.0
              - valueDT2
          - rawComp3:
            - difference:
              - division:
                - rawTemp
                - 131072.0
              - division:
                - valueDT1
                - 8192.0
          - rawComp2:
            - product:
              - rawComp3
              - rawComp3
              - valueDT3
          - celsius:
            - division:
              - sum:
                - rawComp1
                - rawComp2
              - 5120.0
        return: celsius
```

There are a few things to note:

* Multiple computational functions can be grouped under a top-level name,
like `temperature`.
    * This allows multiple related temperature functions to exist in that
    namespace
    * This top-level container may include a title, description, and can
    be optionally bound to a register
* A computational block is defined by a key in the `computed` field
* A computational block must define all variables and their type in the
    `variables` field
* Logical operations are defined in order as an array.
    * Nested math operations can exist to specify the order of operations
* A `return` field can provide a single value or a list of values
    * The `return` type is automatically inferred from `variables`
    * If no `return` field is specified, the function is said to be `void`

### Lifecycle

There is a unique top-level name for functions that allow one to specify
behaviors that should run when the device class is created or destroyed.

You should name the top-level function `_lifecycle` with computations
called `Begin` and `End`. Depending on the specifics of each device template,
these functions may or may not be automatically called. Even if they are
not, they will be generated as ordinary functions that can be called manually.

```yaml
functions:
    _lifecycle:
        title: Lifecycle events
        description: Enables features on device
        register: '#/registers/enable'
        computed:
            Begin:
                variables:
                    enables: int8
                logic:
                    # Enable register = ENABLE_RGBC | ENABLE_POWER
                    - enables:
                        - sum:
                            - 1
                            - 0b10
                    - send: enables
```

## Extensions

Additional parameters may be added in the specification files,
which may be relevant for a given device or provide extra metadata for
tooling.

Extensions can be provided in two ways.

First, they can be placed in any field with the `x-` prefix.

```
info:
    name: BMP280
    x-altname: BMP2XX
```

Other more general fields can be provided in the top-level `extensions`
section. Fields in this section do not need the prefix.

```
extensions:
    foo: bar
```