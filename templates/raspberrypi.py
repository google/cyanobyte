{% import 'macros.jinja2' as utils %}
{% set template = namespace(enum=false, sign=false) %}
{{ utils.pad_string('# ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
"""
Class for {{ info.title }}
"""
{% macro params_int(input) -%}
{% for variable in input %}
{% for key in variable.keys() -%}
{% if key != 'value' %}{{key}}, {% endif %}
{%- endfor %}
{% endfor %}
{%- endmacro %}

{% macro params(input) -%}
{{params_int(input)[:-2]}}
{%- endmacro %}

{% macro variables(vars) -%}
{% for var in vars %}
{% for key in var.keys() %}
{# Technically in Python we don't need to declare vars ahead of time. #}
{# But we'll do so anyway to verify this works. #}
        {{key | camel_to_snake}} = None # Variable declaration
{% endfor %}
{% endfor %}
{%- endmacro %}

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# Check if assignment op #}
{% if step[key][0:1] == "=" %}
        {{key | camel_to_snake}} {{step[key]}}
{% endif %}

{# Check if assignment is a send-op #}
{% if key == 'send' %}
        self.set_{{function.register[12:].lower()}}({{step[key]}})
{% endif %}

{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
        {{key | camel_to_snake}} = {{recursiveAssignLogic(step[key][0], step[key][0].keys()) -}}
{% endif %}

{% endfor %}
{% endfor %}
{%- endmacro %}

{% macro recursiveAssignLogic(logicalStep, keys) -%}
{% for key in keys -%}
{# Read from a register #}
{# {{key}} {{logicalStep[key]}} #}
{% if key == 'read' -%}
    self.get_{{logicalStep[key][12:].lower()}}()
{%- endif %}
{# Perform a recursive summation from an array of logical steps #}
{% if key == 'sum' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step | camel_to_snake}}
    {%- endif %}
    {{- "+" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a recursive difference from an array of logical steps #}
{% if key == 'difference' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step | camel_to_snake}}
    {%- endif %}
    {{- "-" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a recursive product from an array of logical steps #}
{% if key == 'product' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step | camel_to_snake}}
    {%- endif %}
    {{- "*" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a recursive division from an array of logical steps #}
{% if key == 'division' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{ step | camel_to_snake }}
    {%- endif %}
    {{- "/" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Bitwise ops #}
{%- if key == 'bitShiftLeft' -%}
    ({{logicalStep.var | camel_to_snake}} << {{logicalStep.bits}})
{%- endif %}
{%- if key == 'bitShiftRight' -%}
    ({{logicalStep.var | camel_to_snake}} >> {{logicalStep.bits}})
{%- endif %}
{%- endfor %}
{%- endmacro %}

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)
{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{% if function[key].enum %}
{# Optionally import class #}
{% if template.enum is sameas false %}
from enum import Enum
{% set template.enum = true %}
{% endif %}
{% endif %}
{% endfor %}
{% endfor %}

{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{% if function[key].enum %}
{# Create enum class #}
class {{key[0].upper()}}{{key[1:]}}Values(Enum):
    """
{{utils.pad_string("    ", "Valid values for " + function[key].title)}}
    """
    {% for enumObject in function[key].enum %}
    {% for enumKey in enumObject.keys() %}
    {{enumKey.upper()}} = {{enumObject[enumKey].value}} # {{enumObject[enumKey].title}}
    {% endfor %}
    {% endfor %}
{% endif %}
{% endfor %}
{% endfor %}

{% if i2c.endian == 'little' %}
def _swap_endian(val):
    """
    Swap the endianness of a short only
    """
    return val >> 8 | val << 8
{% endif %}

{# Add signing function if needed #}
{% for register in registers %}
{% for key in register.keys() %}
{% if register[key].signed %}
{# Optionally import class #}
{% if template.sign is sameas false %}
def _sign(val, length):
    """
    Convert unsigned integer to signed integer
    """
    if val & (1 << (length - 1)):
        return val - (1 << length)
    return val
{% set template.sign = true %}
{% endif %}
{% endif %}
{% endfor %}
{% endfor %}

class {{ info.title }}:
    """
{{utils.pad_string("    ", info.description)}}
    """
    DEVICE_ADDRESS = {{i2c.address}}
    {% for register in registers %}
    {% for key in register.keys() %}
    REGISTER_{{key.upper()}} = {{register[key].address}}
    {% endfor %}
    {% endfor %}

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    {% for register in registers -%}
    {% for key in register.keys() %}
    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", register[key].description)}}
        """
        {% if register[key].length <= 8 %}
        val = self.bus.read_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_{{key.upper()}}
        )
        {% elif register[key].length <= 16 %}
        val = self.bus.read_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_{{key.upper()}}
        )
        {% endif %}
        {% if i2c.endian == 'little' %}
        val = _swap_endian(val)
        {% endif %}
        {% if register[key].signed %}
        # Unsigned > Signed integer
        val = _sign(val, {{register[key].length}})
        {% endif %}
        return val

    def set_{{key.lower()}}(self, data):
        """
{{utils.pad_string("        ", register[key].description)}}
        """
        {% if i2c.endian == 'little' %}
        data = _swap_endian(data)
        {% endif %}
        {% if register[key].length <= 8 %}
        self.bus.write_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_{{key.upper()}},
            data
        )
        {% elif register[key].length <= 16 %}
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_{{key.upper()}},
            data
        )
        {% endif %}
    {% endfor %}
    {%- endfor %}

    {% for function in functions %}
    {% for key in function.keys() %}
    {% if 'R' is in(function[key].readWrite) %}
    {# Getter #}

    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", function[key].description)}}
        """
        # Read register data
        # '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
        val = self.get_{{function[key].register[12:].lower()}}()
        # Mask register value
        val = val & {{utils.mask(function[key].bitStart, function[key].bitEnd)}}
        {% if function[key].bitEnd %}
        # Bitshift value
        val = val >> {{function[key].bitEnd}}
        {% endif %}
        return val
    {% endif -%}

    {%- if 'W' is in(function[key].readWrite) %}
    {# Setter #}

    def set_{{key.lower()}}(self, data):
        """
{{utils.pad_string("        ", function[key].description)}}
        """
        {% if function[key].bitEnd %}
        # Bitshift value
        data = data << {{function[key].bitEnd}}
        {% endif %}
        # Read current register data
        # '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
        register_data = self.get_{{function[key].register[12:].lower()}}()
        register_data = register_data | data
        self.set_{{function[key].register[12:].lower()}}(register_data)
    {% endif %}
    {% if function[key].computed %}
    {% for compute in function[key].computed %}
    {% for computeKey in compute.keys() %}
    {% if compute[computeKey].input %}
    def {{key.lower()}}_{{computeKey.lower()}}(self, {{params(compute[computeKey].input)}}):
    {% else %}
    def {{key.lower()}}_{{computeKey.lower()}}(self):
    {% endif %}
        """
{{utils.pad_string("        ", function[key].description)}}
        """
        {# Declare our variables #}
{{ variables(compute[computeKey].variables) }}

        {# Read `value` if applicable #}
        {%- for variable in compute[computeKey].input %}
        {% for varKey in variable.keys() %}
        {% if varKey == 'value' %}
        # Read value of register into a variable
        value = self.get_{{function[key].register[12:].lower()}}()
        {% endif %}
        {% endfor %}
        {% endfor -%}
        {# Handle the logic #}
{{ logic(compute[computeKey].logic, function[key]) }}

        {# Return if applicable #}
        {% if compute[computeKey].return %}
        return {{compute[computeKey].return}}
        {% endif %}
    {% endfor %}
    {% endfor %}
    {% endif %}
    {% endfor %}
    {% endfor %}