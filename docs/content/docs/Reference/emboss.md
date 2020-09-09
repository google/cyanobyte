---
title: "Custom serialization"
linkTitle: "Custom Serialization"
weight: 5
description: >
  This describes how to use Emboss for defining richer serialization
  techniques and integrate with communication protocols like SPI.
---


# Support Importing Emboss Files for Serialization/Deserialization Functions
This project is an example of how to import emboss files(emb file), convert the file into essential yaml file and generate cpp code with modified template.

Note: This feature requires Python3.5+.

## Emboss
[Emboss](https://github.com/google/emboss) is a tool for generating code that reads and writes binary data structures. It is designed to help write code that communicates with hardware devices such as GPS receivers, LIDAR scanners, or actuators. 

## Setup
Note: This project requires Python3 and a modified input yaml file
1. Put the emboss file under the same directory of input yaml file
2. Edit import line in the yaml file to the name of emboss file
   **Example:**
   If float.emb is imported for serialization/deserialization functions, we
   need to edit line 33 in the [example.py](peripherals/examplespi-emobss.yaml)file:

    ```yaml
    imports:
        float: float.emb
    ```

3. Set up emboss environment `git clone https://github.com/google/emboss.git`
4. Run `python3 cyanobyte/codegen.py`.

## Options
* `-t` - A template file. You can provide multiple template files.
* `-o` - The output directory where files will be generated.
* `-e` - The directory that emboss folder is stored.
* `-d` - Debug flag to print out additional information.
* `-c` - Clean the output directory before generating files.
