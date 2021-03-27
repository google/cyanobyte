---
title: "{{info.title}}"
linkTitle: "{{info.title}}"
weight: 4
description: >
  {{info.description}}
---

{# Create a dictionary linking a register to its associated fields #}
{% set template = namespace(registersToFields=dict()) %}
{% if fields %}
{# for hierarchical display #}
{% for key,field in fields|dictsort %}
{% set rkey = field.register %}
{% if rkey in template.registersToFields %}
{% set _dummy = field.update({ 'key': key }) %}
{{- template.registersToFields[rkey].append(field) or "" -}}
{% else %}
{% set _dummy = field.update({ 'key': key }) %}
{% set _dummy = template.registersToFields.update({ rkey: [] }) %}
{{- template.registersToFields[rkey].append(field) or "" -}}
{% endif %}
{% endfor %}
{% endif %}

## Device Details

{% if i2c.address is iterable and i2c.address is not string %}
* Device addresses:
{% for address in i2c.address %}
{{address}}{{ "," if not loop.last }}
{% endfor %}
{% else %}
* Device address {{ i2c.address }}
{% endif %}
* Address type {{ i2c.addressType }}
{% if i2c.endian == 'little' %}
* Little Endian
{% endif %}

## Registers
{% for key,register in registers|dictsort %}

### {{ key }}
**{{ register.title }}**
* Address {{register.address}}
* {{register.length}}-bytes
{% if register.readWrite == "R" %}
* Read-only
{% endif %}
{% if register.readWrite == "W" %}
* Write-only
{% endif %}
{% if register.readWrite == "n" %}
* Inaccessible
{% endif %}
{% if register.signed %}
* Signed value
{% endif %}

{{ register.description }}
{% endfor %}

{% if fields %}
## Fields
{% for key in template.registersToFields.keys() %}
{% set register = template.registersToFields[key] %}
{% for field in register %}
### {{ key }}/{{field.key}}
**{{ field.title }}**

{% if field.bitStart == field.bitEnd %}
* Bit {{field.bitStart}}
{% else %}
* Bits {{field.bitStart}}:{{field.bitEnd}}
{% endif %}

{% if field.enum %}

#### Field values

{% for key,enum in field.enum|dictsort %}
* **{{ enum.value }}**: {{ enum.title }}
{% endfor %}
{% endif %}

{{ field.description }}

{% endfor %}
{% endfor %}
{% endif %}

{% if functions %}
## Functions

{% for key,function in functions|dictsort %}
* **{{key}}**: {{function.description}}
{% endfor %}
{% endif %}

## License

_{{ info.title }} version {{ info.version }}. Generated from Cyanobyte Codegen version {{ version }}._

Contact [{{ info.contact.name }}](mailto:{{ info.contact.email }}).

Copyright {{info.copyright.name}} {{info.copyright.date}}. Published under
[{{ info.license.name }}](https://spdx.org/licenses/{{ info.license.name }}.html#licenseText).
