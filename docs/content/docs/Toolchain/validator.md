---
title: "Validator"
linkTitle: "Validator"
weight: 2
description: >
  Validates a Cyanobyte file is correct
---

Here's an example from the project source:

`python3 src/validator.py peripherals/MCP9808.yaml`

Usage: validator.py [OPTIONS] [INPUT_FILES]...

  Main command line entrypoint

  Args:     input_files: A list of CyanoByte documents to validate.

Options:
  --help  Show this message and exit.