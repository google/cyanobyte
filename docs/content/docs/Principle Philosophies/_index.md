---
title: "Cyanobyte"
linkTitle: "Cyanobyte"
weight: 1
description: >
  What is this project?
---

This file contains a proposed updated CyanoByte specification. It is currently a work in progress and aimed at spurring a discussion surrounding what the specification should look like.

While there are some peripheral libraries for some hardware platforms, there is not broad support
for every peripheral on every microcontroller or IoT platform. For engineers, there is an M*N problem
in scaling support.

The CyanoByte specification is a tool to describe the interface to embedded communications in a machine-readable format. It builds off the successes of OpenAPI for web APIs. This will reduce the
problem to M+N.

## Philosophy of CyanoByte

Throughout this exercise, common principles should be extracted to guide future decision making the project.

- The spec should be representative of how things are currently done, even if it is less "proper" or correct.
- The spec should properly separate the datasheet values and the underlying software platform, not
making assumptions about runtime or programming language.

## Example Usage

For a sample sensor, like a BMP280 temperature sensor, there are several pieces that need to be
taken into consideration. For example, the basic temperature value in the registers isn't in any
logical unit. You need to go through a series of arithmetic steps to get Celsius. Traditionally,
engineers needed to read the datasheet and translate that into code. This is prone to error and
time-consuming.

Manufacturers typically host several files alongside their product. One is a CAD file, which may
be used in designing hardware casing. One may be an electrical schematic for circuit board design,
available in programs like KiCad. However, for software engineers, you only get the datasheet.

What if the manufacturer provided a Cyanobyte file for the part? The software engineer could
download it, and run a command-line tool to get the file they need for their platform:

`python3 src/codegen.py -t templates/raspberrypi.py -o ./build -i peripherals/Bmp280.yaml`

This would produce a `Bmp280.py` file.

On their platform, which in this case is a Raspberry Pi, they can easily instantiate and read a value:

```
from Bmp280 import Bmp280
bmp280 = Bmp280()
print(Bmp280.temperature_ascelsius())
```