---
title: "Example Spec"
linkTitle: "Example Spec"
weight: 1
description: >
  What does this project look like?
---

An example specification for part of the [MCP9808 chip](http://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf).

NOTE: This is designed as an example to uncover the spirit of the documentation and not to be perfectly accurate.

```yaml
cyanobyte: 0.1.0
info:
    title: MCP9808
    package: com.cyanobyte
    description: This is a test description
    contact:
        name: 'Joe Smith'
        url: 'example.com'
        email: 'joe@example.com'
    license:
        name: 'Apache 2.0'
        url: 'https://www.apache.org/licenses/LICENSE-2.0.html'
    version: 0.1.0
i2c:
    addressType: '7-bit' # Could be '7-bit', '8-bit', or '10-bit'
    address: 0x18
    addressMask: 0x78 # This specifys which address bits are configurable
    endian: 'big' # Could be 'little' or 'big' endian
registers:
    - configuration:
        address: 0x01
        length: 16
        title: Configuration Register
        description: The MCP9808 has a 16-bit Configuration register (CONFIG) that allows the user to set various functions for a robust temperature monitoring system. Bits 10 through 0 are used to select the temperature alert output hysteresis, device shutdown or Low-Power mode, temperature boundary and critical temperature lock, and temperature Alert output enable/disable. In addition, Alert output condition (output set for TUPPER and TLOWER temperature boundary or TCRIT only), Alert output status and Alert output polarity and mode (Comparator Output or Interrupt Output mode) are user-configurable
        
functions: // Should this be called functions or values or what?
    - limitHysteresis:
        title: TUPPER and TLOWER Limit Hysteresis bits
        description: |
            This bit can not be altered when either of the Lock bits are set (bit 6 and bit 7). 
            This bit can be programmed in Shutdown mode.
        register: '#/registers/configuration' # What should the syntax be when it is split among multiple registers?
        readWrite: 'R' # Could be 'R', 'W', or 'R/W'
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
    - critLock:
        title: TCRIT Lock bit
        description: |
            When enabled, this bit remains set to ‘1’ or locked until cleared by an internal Reset.
        register: '#/registers/configuration'
        bitStart: 7
        bitEnd: 7
        type: 'enum'
        enum:
            - unlocked:
                title: Unlocked. TCRIT register can be written (power-up default)
                value: 0
            - locked:
                title: Locked. TCRIT register can not be written
                value: 1
    - tempBoundary:
        title: Temperature Boundary bits
        type: 'twos-complement'
        computed:
            - asTemp: // https://en.wikipedia.org/wiki/Pseudocode aka pseudo-yaml
                input: test // Not here, but somewhere
                variables:
                    - temp: float32
                logic:
                    - if: value > 256
                        - temp:= value
                    - else:
                        - temp:= 0
                return: temp
```