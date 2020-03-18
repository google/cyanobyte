{% import 'macros.jinja2' as utils %}
{% import 'python.jinja2' as py %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
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
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
        self.set_{{step[key].register[12:].lower()}}({{step[key].value}})
        {% break %}
{%- endif %}
{# Check if assignment op #}
{% if step[key][0:1] == "=" %}
        {{key | camel_to_snake}} {{step[key]}}
{%- endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
        self.set_{{function.register[12:].lower()}}({{step[key]}})
{%- endif %}
{# Check if assignment is register read op #}
{% if step[key][:12] == '#/registers/' %}
        {{key | camel_to_snake}} = self.get_{{step[key][12:].lower()}}()
{%- endif %}
{# Check if assignment is function call op #}
{% if step[key][:12] == '#/functions/' %}
        {{key | camel_to_snake}} = self.{{step[key].lower() | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>_\\g<compute>')}}()
{%- endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
        {{key | camel_to_snake}} = {{py.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}}
{%- endif %}

{% endfor %}
{%- endfor %}
{%- endmacro %}

{{ py.importStdLibs(fields, functions, template) -}}
{# Create enums for fields #}
{% for field in fields %}
{% for key in field.keys() %}
{% if field[key].enum %}
{# Create enum class #}
class {{key[0].upper()}}{{key[1:]}}Values(Enum):
    """
{{utils.pad_string("    ", "Valid values for " + field[key].title)}}
    """
    {% for enumObject in field[key].enum %}
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
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8
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

    {% for field in fields %}
    {% for key in field.keys() %}
    {% if 'R' is in(field[key].readWrite) %}
    {# Getter #}

    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", field[key].description)}}
        """
        # Read register data
        # '#/registers/{{field[key].register[12:]}}' > '{{field[key].register[12:]}}'
        val = self.get_{{field[key].register[12:].lower()}}()
        # Mask register value
        val = val & {{utils.mask(field[key].bitStart, field[key].bitEnd)}}
        {% if field[key].bitEnd %}
        # Bitshift value
        val = val >> {{field[key].bitEnd}}
        {% endif %}
        return val
    {% endif -%}

    {%- if 'W' is in(field[key].readWrite) %}
    {# Setter #}

    def set_{{key.lower()}}(self, data):
        """
{{utils.pad_string("        ", field[key].description)}}
        """
        {% if field[key].bitEnd %}
        # Bitshift value
        data = data << {{field[key].bitEnd}}
        {% endif %}
        # Read current register data
        # '#/registers/{{field[key].register[12:]}}' > '{{field[key].register[12:]}}'
        register_data = self.get_{{field[key].register[12:].lower()}}()
        register_data = register_data | data
        self.set_{{field[key].register[12:].lower()}}(register_data)
    {% endif %}
    {% endfor %}
    {% endfor %}
    {% for function in functions %}
    {% for key in function.keys() %}
    {% for compute in function[key].computed %}
    {% for computeKey in compute.keys() %}
    {% if compute[computeKey].input %}
    def {{key.lower()}}_{{computeKey.lower()}}(self, {{py.params(compute[computeKey].input)}}):
    {% else %}
    def {{key.lower()}}_{{computeKey.lower()}}(self):
    {% endif %}
        """
{{utils.pad_string("        ", function[key].description)}}
        """
        {# Declare our variables #}
{{ py.variables(compute[computeKey].variables) }}
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
        {# Return a tuple #}
        {% if compute[computeKey].return is iterable and compute[computeKey].return is not string %}
        return [{% for returnValue in compute[computeKey].return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}]
        {% endif %}
        {# Return a plain value #}
        {% if compute[computeKey].return is string %}
            {# See if we need to massage the data type #}
            {% if compute[computeKey].output == 'int16' %}
        # Convert from a unsigned short to a signed short
        {{compute[computeKey].return}} = struct.unpack("h", struct.pack("H", {{compute[computeKey].return}}))[0]
            {% endif %}
        return {{compute[computeKey].return}}
        {% endif %}
    {% endfor %}
    {% endfor %}
    {% endfor %}
    {% endfor %}