{% set template = namespace(registersToFields=dict()) %}
{% import 'macros.jinja2' as utils %}
{{ utils.pad_string('# ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
from i2cdevice import Device, Register, BitField

{% if i2c.address is iterable and i2c.address is not string %}
{% for address in i2c.address %}
I2C_ADDR_{{address}} = {{address}}
{% endfor %}
I2C_ADDR = [{% for address in i2c.address %}I2C_ADDR_{{address}}{{', ' if not loop.last}}{% endfor %}]

{% else %}
I2C_ADDR = {{i2c.address}}

{% endif %}
{# Create a dictionary linking a register to its associated fields #}
{# for hierarchical display #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% set rkey = field.register[12:] %}
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
{% macro values_map(field) %}
{% if field.type == 'enum' %}
{
{% for ekey, enum in field.enum|dictsort %}
        {{ekey}}: {{enum.value}}{{',' if not loop.last }}
{% endfor %}
    }{% endif %}
{%- endmacro %}
{% for key,register in registers|dictsort %}
{% if key in template.registersToFields %}
{{key.upper()}} = Register('{{key.upper()}}', {{register.address}}, fields=(
    {% for field in template.registersToFields[key] %}
    BitField('{{field.key}}', {{utils.mask(field.bitStart, field.bitEnd)}}, bitwidth={{field.bitStart - field.bitEnd + 1}}{% if i2c.endian == 'little' %}, values_in=_byte_swap, values_out=_byte_swap{% endif %}{% if field.type == 'enum' %}, values_map={{values_map(field)}}{% endif %}){{',' if not loop.last }}
    {% endfor %}
), read_only={{register.readWrite == 'R'}}, bitwidth={{register.length}})
{% else %}
{{key.upper()}} = Register('{{key.upper()}}', {{register.address}}, read_only={{register.readWrite == 'R'}}, bitwidth={{register.length}})
{% endif %}
{% endfor %}

{{info.title.lower()}} = Device(I2C_ADDR, registers=(
    {% for key,register in registers|dictsort %}
    {{key.upper()}}{{',' if not loop.last}}
    {% endfor %}
))
