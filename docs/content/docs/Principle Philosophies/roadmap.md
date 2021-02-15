---
title: "Roadmap"
linkTitle: "Roadmap"
weight: 4
description: >
  And other items to consider?
---

See [releases](https://github.com/google/cyanobyte/releases) for a detailed list
of package releases and changelogs.

## Current roadmap
- Support Envirophat drivers to identify areas to improve specification
- Add support for a second hardware platform (MSP430? Particle?) to identify areas to improve templates
- Any other I2C changes/improvements

## Other Thoughts
- I2C
  - How do we deal with addresses that are configurable?
  - How do we support sequential register reads for certain chips?
- SPI
- UART
  - How do we support the common methods for encoding data sent over UART? Do we make the specification extendable with custom extensions and plugins in the codegen?
- USB
  - Do we want to even attempt this?