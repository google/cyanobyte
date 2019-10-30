{% import 'macros.jinja2' as utils %}
{% import 'ctils.jinja2' as ctils %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps -%}
{% for key in step.keys() -%}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    write{{step.register[12:]}}({{step.value}});
    {% break %}
{%- endif %}

{# Check if assignment op #}
{% if step[key][:1] == "=" %}
    {{key}} {{step[key]}}
{%- endif %}

{# Check if assignment is a send-op #}
{% if key == 'send' %}
    write{{function.register[12:]}}({{step[key]}});
{%- endif %}

{# Check if assignment is register read op #}
{% if step[key][:12] == '#/registers/' %}
    {{key}} = read{{step[key][12:]}}();
{%- endif %}

{# Check if assignment is function call op #}
{% if step[key][:12] == '#/functions/' %}
    {{key}} = {{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}();
{%- endif %}

{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
    {{key}} = {{ ctils.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}};
{%- endif %}

{%- endfor %}
{%- endfor %}
{%- endmacro %}

{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{% if function[key].enum %}
{# Create enum consts #}
    /*
{{utils.pad_string("    * ", "Valid values for " + function[key].title)}}
    */
    {% for enumObject in function[key].enum %}
    {% for enumKey in enumObject.keys() %}
    uint8_t {{key.upper()}}_{{enumKey.upper()}} = {{enumObject[enumKey].value}}; // {{enumObject[enumKey].title}}
    {% endfor %}
    {% endfor %}
{% endif %}
{% endfor %}
{% endfor %}

{% if i2c.endian == 'little' %}
short _swap_endian(val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}
{% endif %}

{# Add signing function if needed #}
{% for register in registers %}
{% for key in register.keys() %}
{% if register[key].signed %}
{% if template.sign is sameas false %}
short _sign(val, length) {
    // Convert unsigned integer to signed integer
    if val & (1 << (length - 1)) {
        return val - (1 << length);
    }
    return val;
}
{% set template.sign = true %}
{% endif %}
{% endif %}
{% endfor %}
{% endfor %}

// FIXME Use proper types for numbers
#include "{{info.title}}.h"
#define DEVICE_ADDRESS {{i2c.address}}

{% for register in registers %}
{% for key in register.keys() %}
#define REGISTER_{{key.upper()}} {{register[key].address}}
{% endfor %}
{% endfor %}

{{info.title}}::{{info.title}}(TwoWire& wire) :
    _wire(&wire)
{
}

int {{info.title}}::begin() {
    _wire->begin();
}

void {{info.title}}::end() {
    _wire->end();
}

{% for register in registers -%}
{% for key in register.keys() %}
{% set length = register[key].length %}
{% set bytes = (register[key].length / 8) | round(1, 'ceil') | int %}
{{ctils.numtype(length)}} {{info.title}}::read{{key}}() {
    uint8_t datum;
    {{ctils.numtype(length)}} value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_{{key.upper()}});
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, {{bytes}}) != {{bytes}}) {
        return 0;
    }

    {# Read a byte at a time #}
    {% for n in range(bytes) %}
    datum = wire->read();
    value = value << 8 | datum;
    {% endfor %}

    return value;
}

int {{info.title}}::write{{key}}({{ctils.numtype(length)}} data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[{{bytes + 1}}] = { (uint8_t) REGISTER_{{key.upper()}} };
    {% for n in range(bytes) %}
    uint8_t buffer[{{n + 1}}] = (data >> {{8 * (bytes - n - 1)}}) & 0xFF;
    {% endfor %}
    _wire->write(buffer, {{bytes + 1}});
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}

{% endfor %}
{%- endfor %}

{% for function in functions %}
{% for key in function.keys() %}
{% if 'R' is in(function[key].readWrite) %}
{# Getter #}
{{ctils.numtype(register[function[key].register[12:]].length)}} {{info.title}}::get{{key}}() {
    // Read register data
    // '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
    uint8_t val = read{{function[key].register[12:]}}()
    // Mask register value
    val = val & {{utils.mask(function[key].bitStart, function[key].bitEnd)}}
    {% if function[key].bitEnd %}
    // Bitshift value
    val = val >> {{function[key].bitEnd}}
    {% endif %}
    return val
}
{% endif -%}

{%- if 'W' is in(function[key].readWrite) %}
{# Setter #}

{{ctils.numtype(register[function[key].register[12:]].length)}} {{info.title}}::set{{key}}(uint8_t data) {
    {% if function[key].bitEnd %}
    // Bitshift value
    data = data << {{function[key].bitEnd}}
    {% endif %}
    // Read current register data
    // '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
    {{ctils.numtype(register[function[key].register[12:]].length)}} register_data = read{{function[key].register[12:].lower()}}()
    register_data = register_data | data
    return write{{function[key].register[12:]}}(register_data)
}
{% endif %}

{% if function[key].computed %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% if compute[computeKey].input %}
{{ctils.numconv(compute[computeKey].returnType)}} {{info.title}}::{{key}}{{computeKey}}({{ctils.params(compute[computeKey].input)}}) {
{% else %}
{{ctils.numconv(compute[computeKey].returnType)}} {{info.title}}::{{key}}{{computeKey}}() {
{% endif %}
    {# Declare our variables #}
{{ ctils.variables(compute[computeKey].variables) }}

    {# Read `value` if applicable #}
    {%- for variable in compute[computeKey].input %}
    {% for varKey in variable.keys() %}
    {% if varKey == 'value' %}
    // Read value of register into a variable
    value = read{{function[key].register[12:]}}()
    {% endif %}
    {% endfor %}
    {% endfor -%}
    {# Handle the logic #}
{{ logic(compute[computeKey].logic, function[key]) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if compute[computeKey].return is iterable and compute[computeKey].return is not string %}
    return [{% for returnValue in compute[computeKey].return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}];
    {% endif %}
    {# Return a plain value #}
    {% if compute[computeKey].return is string %}
    return {{compute[computeKey].return}};
    {% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}
{% endfor %}
{% endfor %}