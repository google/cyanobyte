---
title: "Codegen"
linkTitle: "Codegen"
weight: 2
description: >
  How to generate code from an IR and template
---

Here's an example from the project source code:

`python3 src/codegen.py -t templates/doc.md -o ./build -i peripherals/Mcp4725.yaml`

- t - A template file. You can provide multiple template files.
- i - A peripheral file. You can provide multiple input files.
- o - The output directory where files will be generated.
- d - Debug flag to print out additional information

Usage: codegen.py [OPTIONS]

  Takes command line arguments and generates source files for every
  peripheral to each template file.

  Args:     input_files: A list of CyanoByte documents to generate.
  template_files: A list of files that are part of the template.
  output_dir: The directory to output the generated files.     debug: Print
  debug messages?

Options:
  -i, --input TEXT
  -t, --template TEXT
  -o, --output TEXT    [default: ./build]
  -d, --debug TEXT
  --help               Show this message and exit.
