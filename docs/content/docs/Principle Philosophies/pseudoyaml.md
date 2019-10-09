---
title: "PseudoYAML Spec"
linkTitle: "PseudoYAML Spec"
weight: 2
description: >
  What is this project?
---

PseudoYAML is a sub-specification of CyanoByte that allows for code to be specified in a method that can be easily translated into multiple different languages. PseudoYAML is not designed to be able to be run independently and is intentionally restricted to only programming concepts standard to all languages.

## Philosophy of PseudoYAML

- Everything is strongly typed as it is easier to ignore the type than infer it.
- Limit control flow and looping etc to minimal necessary. PseudoYAML is not intended to be used for complicated logic.
- Support the vast majority of variable types
- The intent of PseudoYAML is to easily create computed and helper values. It is not intended to be used for complex application specific logic. Therefore, we intentionally only support a very limited subset of use cases. If this does not work for your application, then you must work at a higher level.

## Language Features and Syntax
### PseudoYAML Block

A block of PseudoYAML contains only three keys: `input`, `variables`, and `logic`. No other keys should be included in a Pseudo-YAML block, however they may be omitted if they would otherwise be empty.

The `input` block contains a list of all input variables to the PseudoYAML block. Each element in the input block should contain the type as specific in section X. The `variables` block contains a list of all temporary variables and output variables used within the script / logic.

The `logic` block contains the actual logic of the script. As defined in sections X - X, the `logic` block can contain control flow statements, loops, and other common software features.

An example of a PseudoYAML block is listed below:

```yaml
triangleAreaMinSize:
    input:
        - base: float32
        - height: float32
    variables:
        - area: float32
    logic:
        - if: area <= 5:
            - return: 0
        - else:
            - return: area
```

### Control Structures

#### If / Else Statements

```yaml
exampleIfStatement:
    input:
        - x: int32
    logic:
        - if: x > 2
            - return: x
        - else:
            - return: 0
```

#### Else If Statements

```yaml
exampleElseIfStatement:
    input:
        - x: int32
    logic:
        - if: x == 0
            - return: 0
        - else if: x == 1
            - return: 1
        - else if: x == 2
            - return: 1
        - else:
            return: -1
```

#### For Loops

```yaml
exampleForLoop:
    input:
        - x: int32
    variables:
        - i: int32
        - acc: int32
    logic:
        - i:= 0
        - for:
            - condition: i < 10
            - increment: i
            - do:
                - acc := acc + 1
        - return: acc
```

#### While Loops

```yaml
exampleWhileLoop:
    input:
        - x: int32
    variables:
        - i: int32
        - acc: int32
    logic:
        - i:= 0
        - while: i < 10
            - acc := acc + i
            - i := 1
        - return: acc
```

#### Assignment

```yaml
exampleAssignment:
    input:
        - x: int32
    variables:
        - y: int32
    logic:
        - y := x
        - return: y
```

#### Types

```yaml
exampleTypes:
    variables:
        - testInt8: int8
        - testInt16: int16
        - testInt32: int32
        - testInt64: int64
        - testUint8: uint8
        - testUint16: uint16
        - testUint32: uint32
        - testUint64: uint64
        - testFloat16: float16
        - testFloat32: float32
        - testBool: bool
        - testChar: char
        - testString: str
        - testEnum: enum
            - option1
            - option2
        - testArray:
            - type: int16
            - length: 10
    logic:
        - return: testInt8
```

#### Type Conversion

```yaml
exampleTypeConversion:
    input:
        - x: int32
    variables:
        - y: float16
    logic:
        - y := (float16) x
        - return: y
```

#### Operators

```yaml
- y := x && z  // Logical AND
- y := !x // Logical NOT
- y := x || z // Logical OR
- y := x & z // Bitwise AND
- y := ~x // Bitwise NOT
- y := x | z // Bitwise OR
- y := x + z // Addition
- y := x - z // Subtraction
- y := x / z // Division
- y := x * z // Multiplication
- y := x ** z // Exponential
- y := x << z // Bit shift left
- y := x >> z // Bit shift right
- y := x % z // Modulous
- y := x < z // Less than
- y := x <= z // Less than or equal to
- y := x > z // Greater than
- y := x >= z // Greater than or equal to
- y := x == z // Equality
- y := x != z // Not equal to
```