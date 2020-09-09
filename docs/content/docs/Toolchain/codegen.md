---
title: "Codegen"
linkTitle: "Codegen"
weight: 2
description: >
  How to generate code from an IR and template
---

Here's an example from the project source code:

`python3 src/codegen.py -t templates/doc.md -o ./build peripherals/Mcp4725.yaml`

- t - A template file. You can provide multiple template files.
- o - The output directory where files will be generated.
- d - Debug flag to print out additional information
- e - The directory that emboss folder is stored.
- c - Clean the output directory before generating files.

Usage: codegen.py [OPTIONS] [INPUT_FILES]...

  Takes command line arguments and generates source files for every
  peripheral to each template file.

  Args:
    template_files: A list of files that are part of the template.
    output_dir: The directory to output the generated files.
    debug: Print debug messages?
    emboss - The directory that emboss folder is stored.
    clean: Clean the output directory before output?
    input_files: A list of CyanoByte documents to generate.

Options:
  -t, --template TEXT
  -o, --output TEXT    [default: ./build]
  -d, --debug TEXT
  -e  --emboss TEXT    [default: ../emboss]
  -c, --clean
  --help               Show this message and exit.
