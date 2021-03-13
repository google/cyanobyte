---
title: "Pseduo-YAML"
linkTitle: "Pseduo-YAML"
weight: 2
description: >
  Logic defined in YAML
---

Pseduo-YAML is a set of operations that are defined in a Cyanobyte specification.
It is not entirely a programming language, but lets one define what is effectively
pseduocode in a YAML format. In writing these operations you define essentially
an abstract syntax tree that can be parsed into specific programming languages
for a particular device platform.

The features available in Pseduo-YAML are meant to be broadly available across
languages, and should work in ways that respect a variety of platform features
like threads and callbacks.

The available operations and parameters are defined in [JSON schema](https://github.com/google/cyanobyte/blob/master/spec/cyanobyte.schema.json).

## Commands

All commands are prefixed by a dollar sign rather than a variable name.

### Write Operation

This will write a specific value or variable to a specified register.

```yaml
- $cmdWrite:
    register: '#/registers/myRegisterName'
    value: variableName
```

## Operations

### Common Arithmetic

These common arithmetic operations can accept variables, numbers, or
nested operations of any size.

* sum
* difference
* product
* division

```yaml
- variableName:
    - sum:
        - previousVariable
        - product:
            - otherVariable
            - 5

```

### Advanced Arithemtic

These more advanced arithmetic operations accept **2** elements, which may
be variables, numbers, or nested operations.

* power
* modulus

```yaml
- variableName:
    - power:
        - previousVariable
        - sum:
            - otherVariable
            - 5
```

## Bitwise Operations

These bitwise operations can accept variables, numbers, or
nested operations of any size.

* bitwiseOr
* bitwiseAnd

```yaml
- variableName:
    - bitwiseOr:
        - previousVariable
        - bitwiseAnd:
            - otherVariable
            - 0b11
```

### Bit Shifting

These bit shift operations require two properties. The `var` field requires
a variable name. The `bits` field requires an integer number of bits to shift.

* bitShiftLeft
* bitShiftRight

```yaml
- variableName:
    - bitShiftLeft:
        var: variableName
        bits: 2
```

## Trigonometry

These operations only accept the string variable name or number for which
the operations should be computed. These are computed in _radians_.

* arc tangent

```yaml
- variableName:
    - arc tanget: previousVariable
```

## I/O Operations

### Raw Read

This operation will directly read a number of bits from the device bus.

```yaml
- variableName:
    rawRead: 16
```