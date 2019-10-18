{% import 'macros.jinja2' as utils %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/
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
    {{ numconv(var[key]) }} {{key}}; // Variable declaration
{% endfor %}
{% endfor %}
{%- endmacro %}

{% macro numconv(cyan) -%}
{%- if cyan == 'int8' -%}
char
{%- elif cyan == 'uint8' -%}
uint8_t
{%- elif cyan == 'int16' -%}
short
{%- elif cyan == 'uint16' -%}
uint16_t
{%- elif cyan == 'float32' -%}
float
{%- else -%}
/* ERROR UNDEFINED TYPE */
{%- endif -%}
{%- endmacro %}

{% macro numtype(len, sign) -%}
{% if sign %}
{% if len <= 8 %}
char
{% elif len <= 16 %}
short
{% elif len <= 32 %}
long
{% else %}
long long
{% endif %}
{% else %}
{% if len <= 8 %}
uint8_t
{% elif len <= 16 %}
uint16_t
{% elif len <= 32 %}
uint32_t
{% else %}
uint64_t
{% endif %}
{% endif %}
{%- endmacro %}

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    write{{step.register[12:]}}({{step.value}});
    {% break %}
{% endif %}
{# Check if assignment op #}
{% if step[key][0:1] == "=" %}
    {{key}} {{step[key]}}
{% endif %}

{# Check if assignment is a send-op #}
{% if key == 'send' %}
    write{{function.register[12:]}}({{step[key]}});
{% endif %}

{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
    {{key}} = {{recursiveAssignLogic(step[key][0], step[key][0].keys()) -}};
{% endif %}

{% endfor %}
{% endfor %}
{%- endmacro %}

{% macro recursiveAssignLogic(logicalStep, keys) -%}
{% for key in keys -%}
{# Read from a register #}
{# {{key}} {{logicalStep[key]}} #}
{% if key == 'read' -%}
    read{{logicalStep[key][12:]}}()
{%- endif %}
{# Read from a function #}
{# {{key}} {{logicalStep[key]}} #}
{% if key == 'function' -%}
    {{logicalStep[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>_\\g<compute>')}}()
{%- endif %}
{# Perform a recursive summation from an array of logical steps #}
{% if key == 'sum' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step}}
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
    {{step}}
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
    {{step}}
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
    {{ step }}
    {%- endif %}
    {{- "/" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a recursive modulus from an array of logical steps #}
{% if key == 'modulus' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{ step }}
    {%- endif %}
    {{- "%" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a bitwise OR from an array of logical steps #}
{% if key == 'bitwiseOr' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step}}
    {%- endif %}
    {{- "|" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a bitwise AND from an array of logical steps #}
{% if key == 'bitwiseAnd' -%}
    ({%- for step in logicalStep[key] -%}
    {% if step is iterable and step is not string -%}
    {{ recursiveAssignLogic(step, step.keys()) -}}
    {%- else -%}
    {{step}}
    {%- endif %}
    {{- "&" if not loop.last -}}
    {%- endfor -%})
{%- endif %}
{# Perform a power operation #}
{% if key == 'power' -%}
    pow({{logicalStep[key][0]}}, {{logicalStep[key][1]}})
{%- endif %}
{# Perform an arc tangent operation #}
{% if key == 'arc tangent' -%}
    atan({{logicalStep[key]}})
{%- endif %}
{# Bitwise ops #}
{%- if key == 'bitShiftLeft' -%}
    ({{logicalStep.var}} << {{logicalStep.bits}})
{%- endif %}
{%- if key == 'bitShiftRight' -%}
    ({{logicalStep.var}} >> {{logicalStep.bits}})
{%- endif %}
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
int {{info.title}}::read{{key}}() {
    uint8_t value;
    {% set length = (register[key].length / 8) | round(1, 'ceil') %}
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_{{key.upper()}});
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, {{length}}) != {{length}}) {
        return 0;
    }

    for (size_t i = 0; i < {{length}}; i++) {
        *value++ = wire->read();
    }

    return value;
}

int {{info.title}}::write{{key}}(uint8_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_{{key.upper()}});
    _wire->write(data);
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
{{numtype(register[function[key].register[12:]].length)}} {{info.title}}::get{{key}}() {
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

{{numtype(register[function[key].register[12:]].length)}} {{info.title}}::set{{key}}(uint8_t data) {
    {% if function[key].bitEnd %}
    // Bitshift value
    data = data << {{function[key].bitEnd}}
    {% endif %}
    // Read current register data
    // '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
    uint8_t register_data = read{{function[key].register[12:].lower()}}()
    register_data = register_data | data
    return write{{function[key].register[12:]}}(register_data)
}
{% endif %}

{% if function[key].computed %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% if compute[computeKey].input %}
{{numconv(compute[computeKey].returnType)}} {{info.title}}::{{key}}{{computeKey}}({{params(compute[computeKey].input)}}) {
{% else %}
{{numconv(compute[computeKey].returnType)}} {{info.title}}::{{key}}{{computeKey}}() {
{% endif %}
    {# Declare our variables #}
{{ variables(compute[computeKey].variables) }}

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