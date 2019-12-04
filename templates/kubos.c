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

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    {{info.title.lower()}}_write{{step.register[12:]}}(&{{step.value}});
    {% break %}
{% endif %}
{# Check if assignment op #}
{% if step[key][0:1] == "=" %}
    {{key}} {{step[key]}}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
    {{info.title.lower()}}_write{{function.register[12:]}}(&{{step[key]}});
{% endif %}
{% if step[key][:12] == '#/registers/' %}
    {{info.title.lower()}}_read{{step[key][12:]}}(&{{key}});
{% endif %}
{# // Check if assignment is function call op #}
{% if step[key][:12] == '#/functions/' %}
    {{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}(&{{key}});
{% endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
    {{key}} = {{cpp.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}};
{% endif %}
{% endfor %}
{% endfor %}
{%- endmacro %}

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

#include "{{info.title}}.h"
#define DEVICE_ADDRESS {{i2c.address}}

{% for register in registers %}
{% for key in register.keys() %}
#define REGISTER_{{key.upper()}} {{register[key].address}}
{% endfor %}
{% endfor %}

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int {{info.title.lower()}}_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void {{info.title.lower()}}_terminate() {
    k_i2c_terminate(&i2c_bus);
}

{% for register in registers -%}
{% for key in register.keys() %}
{% set length = (register[key].length / 8) | round(1, 'ceil') | int %}
int {{info.title.lower()}}_read{{key}}({{cpp.numtype(register[key].length)}}* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, {{length}}) != I2C_OK) {
        return -2;
    }
    return 0;
}

int {{info.title.lower()}}_write{{key}}({{cpp.numtype(register[key].length)}}* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[{{length + 1}}] = { (uint8_t) REGISTER_{{key.upper()}} };
    {% for n in range(length) %}
    uint8_t buffer[{{n + 1}}] = (data >> {{8 * (length - n)}}) & 0xFF;
    {% endfor %}
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, {{length + 1}}) != I2C_OK) {
        return -1;
    }
    return 0;
}

{% endfor %}
{%- endfor %}

{% for function in functions %}
{% for key in function.keys() %}
{% if 'R' is in(function[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, function[key].register[12:]) %}
{# Getter #}
int {{info.title.lower()}}_get_{{key.lower()}}({{int_t}}* val) {
    // Read register data
    // '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
    int result = {{info.title.lower()}}_read{{function[key].register[12:]}}(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & {{utils.mask(function[key].bitStart, function[key].bitEnd)}};
    {% if function[key].bitEnd %}
    // Bitshift value
    val = val >> {{function[key].bitEnd}};
    {% endif %}
    return 0;
}
{% endif -%}

{%- if 'W' is in(function[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, function[key].register[12:]) %}
{# Setter #}

int {{info.title.lower()}}_set_{{key.lower()}}({{int_t}}* data) {
    {% if function[key].bitEnd %}
    // Bitshift value
    data = data << {{function[key].bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{function[key].register[12:]}}' > '{{function[key].register[12:]}}'
    {{int_t}} register_data;
    int result = {{info.title.lower()}}_read{{function[key].register[12:]}}(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = {{info.title.lower()}}_write{{function[key].register[12:]}}(&register_data);
    if (result != 0) {
        return -2;
    }
    return 0;
}
{% endif %}

{% if function[key].computed %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% set int_t = cpp.returnType(compute[computeKey]) %}
{% if compute[computeKey].input %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}({{int_t}}* val, {{cpp.params(compute[computeKey].input)}}) {
{% else %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}({{int_t}}* val) {
{% endif %}
    {# Declare our variables #}
{{ cpp.variables(compute[computeKey].variables) }}

    {# Read `value` if applicable #}
    {%- for variable in compute[computeKey].input %}
    {% for varKey in variable.keys() %}
    {% if varKey == 'value' %}
    // Read value of register into a variable
    value = {{info.title.lower()}}_get_{{function[key].register[12:]}}(val);
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