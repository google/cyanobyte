{% import 'macros.jinja2' as utils %}
{% import 'base.python.jinja2' as py %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false, time=false) %}
{{ utils.pad_string('# ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}

import unittest

{# Copy logic macro from `raspberrypi.py` #}
{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{% if step[key] is mapping and 'rawRead' in step[key] %}
        {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
        {{key}} = 0
        {% for n in range(bytes) %}
        {# Read each byte one at a time from device #}
        _datum = self.bus.read_byte(self.device_address)
        {{key}} = {{key}} << 8 | _datum
        {% endfor %}
        {% break %}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == '$cmdWrite' %}
        {% if 'value' in step[key] %}
        self.set_{{step[key].register[12:].lower()}}({{step[key].value}})
        {% else %}
        self.set_{{step[key].register[12:].lower()}}()
        {% endif %}
        {% break %}
{%- endif %}
{% if key == '$delay' %}
        time.sleep({{ step[key].for / 1000 }})
{{ logic(step[key].after, function) }}
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

{{ py.importStdLibs(fields, functions, i2c, template) -}}

class Test{{info.title}}(unittest.TestCase):
    """
    Test class to validate behavior for {{info.title}}.
    """
    {% for r in registers %}
    def get_{{r.lower()}}(self):
        {% if 'example' in registers[r] %}
        return {{registers[r].example.valid[0]}} # Hardcoded example
        {% else %}
        # registers.{{r}}.example does not exist
        # This will be okay unless we try to call it.
        raise ValueError("Example does not exist for register {{r}}.")
        {% endif %}

    def set_{{r.lower()}}(self, val):
        # Ignore.
        return

    {% endfor %}

    {% for f in functions %}
    {% for c in functions[f].computed %}
    {% set compute = functions[f].computed[c] %}
    {% if 'example' in compute %}
    def {{f.lower()}}_{{c.lower()}}(self):
        return {{compute.example.valid[0]}} # Hardcoded example

    def test_{{c.lower()}}(self):
        # Execute actual code
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
        returnValue = [{% for returnValue in compute.return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}]
        {# Return a plain value #}
        {% elif compute.return is string %}
            {# See if we need to massage the data type #}
            {% if compute.output == 'int16' %}
        # Convert from a unsigned short to a signed short
        {{compute.return}} = struct.unpack("h", struct.pack("H", {{compute.return}}))[0]
            {% endif %}
        returnValue = {{compute.return}}
        expectedValue = {{functions[f].computed[c].example.valid[0]}}
        {% endif %}
        self.assertEqual(returnValue, expectedValue)

    {% endif %}
    {% endfor %}
    {% endfor %}
