# {{ info.title }}
{{ info.description }}

## Registers
{% for register in registers %}

### {{ register.title }}
{{ register.description }}
{% endfor %}

## License
Licensed under [{{ info.license.name }}](https://spdx.org/licenses/{{ info.license.name }}.html#licenseText).

_{{ info.title }} version {{ info.version }}_

_Based on Cyanobyte spec version {{cyanobyte}}_

_Generated from Cyanobyte Codegen version {{ version }}_