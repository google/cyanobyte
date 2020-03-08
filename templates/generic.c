{% import 'macros.jinja2' as utils %}
{% import 'clang.jinja2' as cpp %}
{# Consult https://github.com/kubos/kubos/blob/master/test/integration/linux/lsm303dlhc-i2c/source/main.c #}
{# Also https://docs.kubos.com/1.18.0/deep-dive/apis/kubos-hal/i2c-hal/c-i2c/c-i2c.html #}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

{% macro logic(logicalSteps, function, read, write) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    {{info.title.lower()}}_write{{step.register[12:]}}(&{{step.value}}, write);
    {% break %}
{% endif %}
{# Check if assignment op #}
{% if step[key][0:1] == "=" %}
    {{key}} {{step[key]}}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
    {{info.title.lower()}}_write{{function.register[12:]}}(&{{step[key]}}, write);
{% endif %}
{% if step[key][:12] == '#/registers/' %}
    {{info.title.lower()}}_read{{step[key][12:]}}(&{{key}}, read);
{% endif %}
{# // Check if assignment is function call op #}
{% if step[key][:12] == '#/functions/' %}
    {{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}(&{{key}}, read, write);
{% endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
    {{key}} = {{cpp.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}};
{% endif %}
{% endfor %}
{% endfor %}
{%- endmacro %}

{% if i2c.endian == 'little' %}
static short _swap_endian(short val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}
{% endif %}

{# Add signing function if needed #}
{% for register in registers %}
{% for key in register.keys() %}
{% if register[key].signed %}
{% if template.sign is sameas false %}
static short _sign(short val, short length) {
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

#include "{{info.title}}.h"
#define DEVICE_ADDRESS {{i2c.address}}

{% for register in registers %}
{% for key in register.keys() %}
#define REGISTER_{{key.upper()}} {{register[key].address}}
{% endfor %}
{% endfor %}

// Provide an I2C connect function, return status
int {{info.title.lower()}}_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

{% for register in registers -%}
{% for key in register.keys() %}
{% set length = (register[key].length / 8) | round(1, 'ceil') | int %}
int {{info.title.lower()}}_read{{key}}(
    {{cpp.numtype(register[key].length)}}* val,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_{{key.upper()}}, val, {{length}}) != 0) {
        return -2;
    }
    return 0;
}

int {{info.title.lower()}}_write{{key}}(
    {{cpp.numtype(register[key].length)}}* data,
    int (*write)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_{{key.upper()}}, data, {{length}}) != 0) {
        return -1;
    }
    return 0;
}

{% endfor %}
{%- endfor %}

{% for field in fields %}
{% for key in field.keys() %}
{% if 'R' is in(field[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, field[key].register[12:]) %}
{# Getter #}
int {{info.title.lower()}}_get_{{key.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/{{field[key].register[12:]}}' > '{{field[key].register[12:]}}'
    int result = {{info.title.lower()}}_read{{field[key].register[12:]}}(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & {{utils.mask(field[key].bitStart, field[key].bitEnd)}};
    {% if field[key].bitEnd %}
    // Bitshift value
    val = val >> {{field[key].bitEnd}};
    {% endif %}
    return 0;
}
{% endif -%}

{%- if 'W' is in(field[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, field[key].register[12:]) %}
{# Setter #}

int {{info.title.lower()}}_set_{{key.lower()}}(
    {{int_t}}* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    {% if field[key].bitEnd %}
    // Bitshift value
    data = data << {{field[key].bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field[key].register[12:]}}' > '{{field[key].register[12:]}}'
    {{int_t}} register_data;
    int result = {{info.title.lower()}}_read{{field[key].register[12:]}}(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = {{info.title.lower()}}_write{{field[key].register[12:]}}(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}
{% endif %}
{% endfor %}
{% endfor %}

{% for function in functions %}
{% for key in function.keys() %}
{% if function[key].computed %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% set int_t = cpp.returnType(compute[computeKey]) %}
{% if compute[computeKey].input %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}(
    {{int_t}}* val,
    {{cpp.params(compute[computeKey].input)}},
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
{% else %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
{% endif %}
    {# Declare our variables #}
{{ cpp.variables(compute[computeKey].variables) }}

    {# Read `value` if applicable #}
    {%- for variable in compute[computeKey].input %}
    {% for varKey in variable.keys() %}
    {% if varKey == 'value' %}
    // Read value of register into a variable
    value = {{info.title.lower()}}_get_{{function[key].register[12:]}}(val, read);
    {% endif %}
    {% endfor %}
    {% endfor -%}
    {# Handle the logic #}
{{ logic(compute[computeKey].logic, function[key], read, write) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if compute[computeKey].return is iterable and compute[computeKey].return is not string %}
    *val = [{% for returnValue in compute[computeKey].return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}];
    {% endif %}
    {# Return a plain value #}
    {% if compute[computeKey].return is string %}
    *val = {{compute[computeKey].return}};
    {% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}
{% endfor %}
{% endfor %}