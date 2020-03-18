---
title: "{{info.title}}"
linkTitle: "{{info.title}}"
weight: 4
description: >
  {{info.description}}
---

## Registers
{% for key,register in registers|dictsort %}

### {{ register.title }}
{{ register.description }}
{% endfor %}

## License
Licensed under [{{ info.license.name }}](https://spdx.org/licenses/{{ info.license.name }}.html#licenseText).

_{{ info.title }} version {{ info.version }}_

_Based on Cyanobyte spec version {{cyanobyte}}_

_Generated from Cyanobyte Codegen version {{ version }}_
