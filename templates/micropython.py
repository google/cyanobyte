{% import 'macros.jinja2' as utils %}
{% import 'python.jinja2' as py %}
{% set template = namespace(sign=false, math=false, struct=false) %}
{{ utils.pad_string('# ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
"""
Class for {{ info.title }}
"""
{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# // Check if a raw read-op #}
{% if step[key] is mapping and 'rawRead' in step[key] %}
        {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
        _byte_list = self.i2c.readfrom(self.device_address, {{bytes}})
        {{key}} = 0
        {% for n in range(bytes) %}
        {{key}} = {{key}} << 8 | _byte_list[{{n}}]
        {% endfor %}
        {% break %}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
        {% if 'value' in step[key] %}
        self.set_{{step[key].register[12:].lower()}}({{step[key].value}})
        {% else %}
        self.set_{{step[key].register[12:].lower()}}()
        {% endif %}
        {% break %}
{%- endif %}
{# Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
        {{key | camel_to_snake}} {{step[key]}}
{%- endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
        self.set_{{function.register[12:].lower()}}({{step[key]}})
{%- endif %}
{# Check if assignment is register read op #}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
        {{key | camel_to_snake}} = self.get_{{step[key][12:].lower()}}()
{%- endif %}
{# Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
        {{key | camel_to_snake}} = self.{{step[key].lower() | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>_\\g<compute>')}}()
{%- endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
        {{key | camel_to_snake}} = {{py.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}}
{%- endif %}

{% endfor %}
{%- endfor %}
{%- endmacro %}

{{ py.importUstdLibs(fields, functions, template) -}}
from machine import I2C

{# Create enums for fields #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if field.enum %}
{# Create enum-like constants #}
{% for ekey,enum in field.enum|dictsort %}
{{key.upper()}}_{{ekey.upper()}} = {{enum.value}} # {{enum.title}}
{% endfor %}

{% endif %}
{% endfor %}
{% endif %}
{% if i2c.address is iterable and i2c.address is not string %}
{% for address in i2c.address %}
I2C_ADDRESS_{{address}} = {{address}}
{% endfor %}

{% endif %}

{{ py.importLittleEndian(i2c) }}

{{ py.importSign(registers, template) }}

class {{ info.title }}:
    """
{{utils.pad_string("    ", info.description)}}
    """
    {% if i2c.address is number %}
    device_address = {{i2c.address}}
    {% endif %}
    {% for key,register in registers|dictsort %}
    REGISTER_{{key.upper()}} = {{register.address}}
    {% endfor %}

    {% if i2c.address is iterable and i2c.address is not string %}
    def __init__(self, i2c, address):
        # Initialize connection to peripheral
        self.i2c = i2c
        self.device_address = address
    {% else %}
    def __init__(self, i2c):
        # Initialize connection to peripheral
        self.i2c = i2c
    {% endif %}
        {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
        self._lifecycle_begin()
        {% endif %}

    {% for key,register in registers|dictsort %}
    {% set bytes = (register.length / 8) | round(1, 'ceil') | int %}
    {% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", register.description)}}
        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            {{bytes}},
            addrsize={{register.length}}
        )
        val = 0
        {% for n in range(bytes) %}
        val = val << 8 | byte_list[{{n}}]
        {% endfor %}
        {% if i2c.endian == 'little' %}
        val = _swap_endian(val, {{register.length}})
        {% endif %}
        {% if register.signed %}
        # Unsigned > Signed integer
        val = _sign(val, {{register.length}})
        {% endif %}
        return val
    {% endif %}

    {% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
    def set_{{key.lower()}}(self{% if register.length > 0 %}, data{% endif %}):
        """
{{utils.pad_string("        ", register.description)}}
        """
        {% if i2c.endian == 'little' %}
        data = _swap_endian(data, {{register.length}})
        {% endif %}
        buffer = []
        {% for n in range(bytes) %}
        buffer[{{n}}] = (data >> {{8 * (bytes - n - 1)}}) & 0xFF
        {% endfor %}
        self.i2c.writeto_mem(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            buffer,
            addrsize={{register.length}}
        )
    {% endif %}
    {% endfor %}

    {% if fields %}
    {% for key,field in fields|dictsort %}
    {% if 'R' is in(field.readWrite) %}
    {# Getter #}

    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", field.description)}}
        """
        # Read register data
        # '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
        val = self.get_{{field.register[12:].lower()}}()
        # Mask register value
        val = val & {{utils.mask(field.bitStart, field.bitEnd)}}
        {% if field.bitEnd %}
        # Bitshift value
        val = val >> {{field.bitEnd}}
        {% endif %}
        return val
    {% endif -%}

    {%- if 'W' is in(field.readWrite) %}
    {# Setter #}

    def set_{{key.lower()}}(self, data):
        """
{{utils.pad_string("        ", field.description)}}
        """
        {% if field.bitEnd %}
        # Bitshift value
        data = data << {{field.bitEnd}}
        {% endif %}
        # Read current register data
        # '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
        register_data = self.get_{{field.register[12:].lower()}}()
        register_data = register_data | data
        self.set_{{field.register[12:].lower()}}(register_data)
    {% endif %}
    {% endfor %}
    {% endif %}
    {% if functions %}
    {% for key,function in functions|dictsort %}
    {% for ckey,compute in function.computed|dictsort %}
    {% if compute.input %}
    def {{key.lower()}}_{{ckey.lower()}}(self, {{py.params(compute.input)}}):
    {% else %}
    def {{key.lower()}}_{{ckey.lower()}}(self):
    {% endif %}
        """
{{utils.pad_string("        ", function.description)}}
        """
        {# Declare our variables #}
{{ py.variables(compute.variables) }}
        {# Read `value` if applicable #}
        {% if 'input' in compute %}
        {%- for vkey,variable in compute.input|dictsort %}
        {% if vkey == 'value' %}
        # Read value of register into a variable
        value = self.get_{{function.register[12:].lower()}}()
        {% endif %}
        {% endfor -%}
        {% endif %}
        {# Handle the logic #}
{{ logic(compute.logic, function) -}}
        {# Return if applicable #}
        {# Return a tuple #}
        {% if 'return' in compute and compute.return is not string %}
        return [{% for returnValue in compute.return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}]
        {# Return a plain value #}
        {% elif compute.return is string %}
            {# See if we need to massage the data type #}
            {% if compute.output == 'int16' %}
        # Convert from a unsigned short to a signed short
        {{compute.return}} = ustruct.unpack("h", ustruct.pack("H", {{compute.return}}))[0]
            {% endif %}
        return {{compute.return}}
        {% endif %}
    {% endfor %}
    {% endfor %}
    {% endif %}