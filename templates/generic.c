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
    {{info.title.lower()}}_write{{step[key].register[12:]}}(&{{step[key].value}}, write);
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
{% for key,register in registers|dictsort %}
{% if register.signed %}
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

#include "{{info.title}}.h"
{% if i2c.address is number %}
#define DEVICE_ADDRESS {{i2c.address}}
{% endif %}

{% for key,register in registers|dictsort %}
#define REGISTER_{{key.upper()}} {{register.address}}
{% endfor %}

// Provide an I2C connect function, return status
{% if i2c.address is iterable and i2c.address is not string %}
static deviceAddress_t DEVICE_ADDRESS;

int {{info.title.lower()}}_init(deviceAddress_t address, int (*connect)(uint8_t)) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}
{% else %}
int {{info.title.lower()}}_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}
{% endif %}

{% for key,register in registers|dictsort -%}
{% set length = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
int {{info.title.lower()}}_read{{key}}(
    {{cpp.numtype(register.length)}}* val,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register.length)}}*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_{{key.upper()}}, val, {{length}}) != 0) {
        return -2;
    }
    return 0;
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
int {{info.title.lower()}}_write{{key}}(
    {{cpp.numtype(register.length)}}* data,
    int (*write)(uint8_t, uint8_t, {{cpp.numtype(register.length)}}*, uint8_t)
) {
    if (write(DEVICE_ADDRESS, REGISTER_{{key.upper()}}, data, {{length}}) != 0) {
        return -1;
    }
    return 0;
}{% endif %}

{%- endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Getter #}
int {{info.title.lower()}}_get_{{key.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    // Read register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(val, read);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & {{utils.mask(field.bitStart, field.bitEnd)}};
    {% if field.bitEnd %}
    // Bitshift value
    val = val >> {{field.bitEnd}};
    {% endif %}
    return 0;
}
{% endif -%}

{%- if 'W' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Setter #}

int {{info.title.lower()}}_set_{{key.lower()}}(
    {{int_t}}* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
    {% if field.bitEnd %}
    // Bitshift value
    data = data << {{field.bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    {{int_t}} register_data;
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(&register_data, read);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = {{info.title.lower()}}_write{{field.register[12:]}}(&register_data, write);
    if (result != 0) {
        return -2;
    }
    return 0;
}
{% endif %}
{% endfor %}
{% endif %}

{% if functions %}
{% for key,function in functions|dictsort %}
{% if function.computed %}
{% for ckey,compute in function.computed|dictsort %}
{% set int_t = cpp.returnType(compute) %}
{% if compute.input %}
void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}(
    {{int_t}}* val,
    {{cpp.params(compute.input)}},
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
{% else %}
void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
) {
{% endif %}
    {# Declare our variables #}
{{ cpp.variables(compute.variables) }}

    {# Read `value` if applicable #}
    {% if 'input' in compute %}
    {%- for vkey,variable in compute.input|dictsort %}
    {% if varKey == 'value' %}
    // Read value of register into a variable
    value = {{info.title.lower()}}_get_{{function.register[12:]}}(val, read);
    {% endif %}
    {% endfor -%}
    {% endif %}
    {# Handle the logic #}
{{ logic(compute.logic, function, read, write) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if compute.return is iterable and compute.return is not string %}
    *val = [{% for returnValue in compute.return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}];
    {% endif %}
    {# Return a plain value #}
    {% if compute.return is string %}
    *val = {{compute.return}};
    {% endif %}
}

{% endfor %}
{% endif %}
{% endfor %}
{% endif %}