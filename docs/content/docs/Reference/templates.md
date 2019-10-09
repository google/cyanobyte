---
title: "Templates"
linkTitle: "Templates"
weight: 2
description: >
  Cyanobyte template files
---

A "Cyanobyte template file" is a file that provides an abstract definition of how a Cyanobyte
specification file may be rendered for your language and platform of choice. This file may be provided
off-the-shelf by the platform developer, obtained through an open-source project, or developed in-house.

For the scope of this project, templates are designed using Jinja2. The specification file is inflated
into the template and the output file should be a fully code executable file.

This project provides sample templates to show you how to get started with your own.

* `templates/raspberrypi.py` - For a Raspberry Pi
* `templates/doc.md` - For generating reference documentation