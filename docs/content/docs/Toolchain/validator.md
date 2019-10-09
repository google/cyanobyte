---
title: "Validator"
linkTitle: "Validator"
weight: 2
description: >
  Validates a Cyanobyte file is correct
---

Here's an example from the project source:

`python3 src/validator.py -i peripherals/MCP9808.yaml`

- i - A Cyanobyte document. You can provide multiple input files.

Usage: validator.py [OPTIONS]

  Main command line entrypoint

  Args:     input_files: A list of CyanoByte documents to validate.

Options:
  -i, --input TEXT
  --help            Show this message and exit.