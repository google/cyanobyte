---
title: "Getting Started"
linkTitle: "Getting Started"
weight: 1
description: >
  Onboard onto using the project.
---

The Cyanobyte Codegen and Verification tools are available to download
via Pip (Python 3.7+).

```
pip install cyanobyte
```

You can run `cyanobyte-codegen --version` to verify your version.

## Generate a simple Markdown file

To get started, create a peripheral.yaml file. You can copy and paste
this one. Save it as `example.yaml` in your working directory.

```
cyanobyte: 0.1.0
info:
  contact:
    name: Nick Felker
    url: https://github.com/google/cyanobyte
    email: felker@google.com
  package: com.cyanobyte
  title: Example
  description: Example of a package
  copyright:
    name: Google Inc.
    date: '2019'
  license:
    name: Apache-2.0
  version: 0.1.0

i2c:
  addressType: 7-bit
  address:
    - 0x10
    - 0x20
    - 0x30
  addressMask: 0xFF

registers:
  RegisterA:
    address: 0x00
    length: 8
    title: First example
    description: An 8-bit register
  RegisterB:
    address: 0x01
    length: 16
    title: Second example
    description: A 16-bit register
  RegisterC:
    address: 0x02
    length: 32
    title: Third example
    description: A 32-bit register
  RegisterD:
    address: 0x03
    length: 0
    title: Fourth example
    description: A dummy register that has no data
```

Now, run the codegen tool:

```
cyanobyte-codegen -t doc -c example.yaml
```

In this command, we are generating an output for the file `example.yaml`. With `-t doc`, we are using a built-in Jinja2 template to generate a Markdown output. Alternatively, you can provide a filepath to your own template. The `-c` flag means that we will clean out our build directory before running.

Once this command runs, you should see the output in the new `build` directory, under the filename `example.md`. Open it. You should see the content of the YAML file now organized in a Markdown format.

Try out other templates provided by the codegen tool, such as `micropython` or `arduino`. Also, play around with modifying the YAML file and seeing how that affects the output. The documentation provides further, more advanced topics.
