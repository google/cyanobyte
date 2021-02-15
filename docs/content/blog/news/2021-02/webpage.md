---
date: 2021-02-16
title: "web-documentation"
linkTitle: "Cyanobyte turns machine-readable datasheets into web documentation"
description: "One benefit of Cyanobyte is around documentation. By defining it in this way, not only can code be generated, but any type of file. In the past, LaTeX was used as the basis for generating documentation as PDFs. Now, there is a new type of output: HTML."
author: Nick Felker
---

<small>This article was cross-posted [from Medium](https://medium.com/@fleker/bc5db3c28f35)</small>

Cyanobyte is an ongoing project which aims to define machine-readable datasheets for embedded peripheral devices. Through this, one is able to quickly generate device drivers for a given hardware platform like Arduino or Raspberry Pi.

One additional benefit is around documentation. By defining it in this way, not only can code be generated, but any type of file. In the past, [LaTeX was used](https://fleker.medium.com/using-machine-readable-datasheets-to-create-datasheets-with-cyanobyte-and-latex-cf57a0e953e7) as the basis for generating documentation as PDFs. Now, there is a new type of output: HTML.

You can try this out with [a peripheral file](https://github.com/google/cyanobyte/tree/master/peripherals) and version 0.0.2 of the Cyanobyte codegen from pip.

```
pip install cyanobyte
cyanobyte-codegen -t webpage /path/to/peripheral-file.yaml
```

The webpage should be located in your `build` directory. It will provide a description of the peripheral and a visual table of every register.

<img src="https://cdn-images-1.medium.com/max/1400/1*-rlKtkMQFT9dSCFV-e8Ung.png" />

The top of the page, and the footer, contains metadata about the peripheral and the file itself.

```
cyanobyte: 0.1.0
info:
  contact:
    name: Nick Felker
    url: https://github.com/google/cyanobyte
  package: com.cyanobyte
  title: ADS1015
  description: Texas Instruments Analog-Digital Converter
  copyright:
    name: Google Inc.
    date: '2019'
  license:
    name: Apache-2.0
  version: 0.1.0
i2c:
  addressType: 7-bit
  address: 0x49
  addressMask: 0xFF
  endian: little
```

You can see each address on the left-hand side and its size. Each cell of the table includes a readable label for what it is and a more detailed description of that register. It also works for multiple fields that may be defined as one register.

Each register is defined in the `registers` top-level field of a peripheral YAML file:

```
registers:
  Conversion:
    address: 0x00
    length: 16
    title: ADC Value
    description: Contains the result of the last conversion
    readWrite: R
  Config:
    address: 0x01
    length: 16
    title: ADC config
    description: Specifics of the sensing implementation
```

Here, register-level properties like being read-only can be defined.

Fields are defined in the `fields` top-level attribute of the peripheral YAML file:

```
fields:
  SampleRate:
    title: Setup sample rate for reading analog voltage
    description: |
      This sets the samples-per-second value
    register: '#/registers/Config'
    readWrite: 'W'
    bitStart: 7
    bitEnd: 5
    type: 'enum'
    enum: ...
  ProgrammableGain:
    title: Setup programmable gain
    description: |
      This sets the programmable gain for reading analog voltage
    register: '#/registers/Config'
    readWrite: 'W'
    bitStart: 11
    bitEnd: 9
    type: enum
    enum: ...
  DeviceOperatingMode:
    title: Set the operating mode
    description: |
      This bit controls the operating mode
    register: '#/registers/Config'
    readWrite: 'W'
    bitStart: 8
    bitEnd: 8
    type: enum
    enum: ...
  Channel:
    title: Set the channel to read
    description: |
      This sets the channel for reading analog voltage
    register: '#/registers/Config'
    readWrite: 'n'
    bitStart: 14
    bitEnd: 12
    type: enum
    enum: ...
```

Each field can have independent bit fields, names, descriptions, and I/O access. Note that in the rendered HTML output, the size of each cell corresponds to the size of the field with respect to the register.

Below this table is more information, such as any functions that may be available on the device. For this peripheral in particular, an analog-digital converter, it can convert the internal sensor value into voltage. The logic for this function is defined in machine-readable logic within the YAML file.

```
functions:
  analog:
    title: Value read from ADC
    description: Reads the analog voltage in Volts
    computed:
      read:
        input:
          channel: int8
        variables:
          config: int16
          raw: int16
          datumA: int8
          datumB: int8
          programmableGain: int16
          processed: int16
        logic:
          - config: '#/registers/Config'
          - config:
            - bitwiseOr:
              - config
              - bitShiftLeft:
                var: channel
                bits: 12
          - config:
              - bitwiseOr:
                - config
                - 0x8000 # Set single-shot mode
          - cmdWrite:
              register: '#/registers/Config'
              value: config
          - raw: '#/registers/Conversion'
          - datumA:
            - bitwiseAnd:
              - raw
              - 0xFF00
          - datumA:
            - bitShiftRight:
              var: datumA
              bits: 8
          - datumB:
            - bitwiseAnd:
              - raw
              - 0x00FF
          - processed:
            - bitwiseOr:
              - bitShiftLeft:
                var: datumA
                bits: 4
              - bitShiftRight:
                var: datumB
                bits: 4
          # Get gain from config
          - programmableGain: = 6144
          - processed:
            - product:
              - division:
                - processed
                - 2047
                - 1000
              - programmableGain
        return: processed
```

Adopting a machine-readable format may be a significant change to the development workflow. Developing a template for your platform may require time and engineering resources.

It may be worthwhile to explore using this format for documentation first. In doing this, you can see the benefits more quickly and improve the productivity of engineers who may still be using manually-crafted datasheets. From here, it may be more reasonable to iterate and develop a code template.

The Cyanobyte project continues to be [developed on GitHub](https://github.com/google/cyanobyte) and has an open issue tracker for any issues or feature requests.