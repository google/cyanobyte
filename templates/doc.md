# {{ name }}

## Registers
{% for register in registers %}

### {{ register.name}}
*{{register.size}} bits*
{% if register.getter %}*Readable*{% endif %}
{% if register.setter %}*Writable*{% endif %}

{{ register.description }}
{% endfor %}

_Generated from version {{ version }}_