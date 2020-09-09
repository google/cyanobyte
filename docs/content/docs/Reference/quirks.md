---
title: "Strange chip quirks"
linkTitle: "Strange chip quirks"
weight: 4
description: >
  This is a directory of strange peripheral chip quarks that were unexpected or unintuative.
---

## BMP280

* Multiple register values can have the same logical interpretation. For the register settings osrs_t[2:0] the following values all mean that the setting is oversampling x16: 0b101, 0b110, and 0b111. This means that they can't be represented as a typical enum in the generated code. It should likely always write one of the values and read all values with the correct interpretation.
* There is an I2C command to enable the SPI interface.