---
title: "Philosophy and Goals"
linkTitle: "Philosophy and Goals"
weight: 4
description: >
  Philosophy and goals?
---

# Philosophy and goals of CyanoByte

CyanoByte is a project whose goal is to create a standardized specification for representing
hardware peripheral characteristics and functions in a static configuration. This could be
likened to a machine-readable representation of a datasheet.

Like a datasheet, this intermediate representation (IR) should not just contain a table of registers
and values, but also functionality. This includes a series of steps that represent common
actions like initializing, closing, and other common use-cases. Temperature sensors, for example,
may need to be converted from a raw value to Celsius. This step should be represented in the
IR.

Everything should be defined so that the client can use this IR as a fully-functioning library.
Anything that a well-developed client library would do, should be automatically generated. Any
device-specific logic should be represented in the IR.

Platform-specific logic, such as the code to perform hardware connectivity, should be defined in
a platform template (PT) in a flexible way. The IR should be processed and laid into the PT.

A core goal is minimizing the integration time of hardware peripherals into a specific hardware
platform. As such, one needs to go beyond a simple set of registers and handle flows. Further
efforts to minimize integration time through a static configuration would also be useful to
explore through the development of this project.

At the moment, the project will only cover I2C. Many I2C devices use SMBus as a common format to
communicate and have straightforward data representation.

Throughout this exercise, common principles should be extracted to guide future decision
making the project.

## Goals
- The spec should be representative of how things are currently done, even if it is less "proper" or correct.
- The spec should provide everything needed to generate and publish a client library, with one-line import and one-line init
- The spec should should contain a way to provide a series of logical steps for computation
- The spec should be flexible enough to represent any hardware peripheral
- The spec should be easily human-readable, so that hardware engineers do not need to learn a complex format

## Anti-goals
- The spec should not have dependencies on a specific programming language or reference specific implementations
    - An I2C device yaml representation should not have a preference on which I2C library is used on the Raspberry Pi
- The spec should not be concerned about backwards compatibility
    - This will change in the future, but during a prototyping phase we should not be concerned about this
- The pseudo-yaml spec should not allow for flexible code functions such as importing libraries
    - Libraries then require a package manager, and a public host, and that's major scope creep
- The pseudo-yaml spec should not be developed into a full programming language
    - This could result in versioning problems and template incompatibilities