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
{% if step[key] is mapping and 'rawRead' in step[key] %}
    {% set length = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
    k_i2c_read(i2c_bus, DEVICE_ADDRESS, {{key}}, {{length}});
    {% break %}
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    {% if 'value' in step[key] %}
    {{info.title.lower()}}_write{{step[key].register[12:]}}(&{{step[key].value}});
    {% else %}
    {{info.title.lower()}}_write{{step[key].register[12:]}}();
    {% endif %}
    {% break %}
{% endif %}
{# Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
    {{key}} {{step[key]}}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
    {{info.title.lower()}}_write{{function.register[12:]}}(&{{step[key]}});
{% endif %}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
    {{info.title.lower()}}_read{{step[key][12:]}}(&{{key}});
{% endif %}
{# // Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
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
{% for key,register in registers|dictsort %}
{% if register.signed %}
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

#include "{{info.title}}.h"
{% if i2c.address is number %}
#define DEVICE_ADDRESS {{i2c.address}}
{% endif %}

{% for key,register in registers|dictsort %}
#define REGISTER_{{key.upper()}} {{register.address}}
{% endfor %}

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
{% if i2c.address is iterable and i2c.address is not string %}
static deviceAddress_t DEVICE_ADDRESS;

int {{info.title.lower()}}_init(deviceAddress_t address, char* bus_name) {
    DEVICE_ADDRESS = address;
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
    {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
    {{info.title.lower()}}__lifecycle_begin();
    {% endif %}
}
{% else %}
int {{info.title.lower()}}_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
    {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
    {{info.title.lower()}}__lifecycle_begin();
    {% endif %}
}
{% endif %}

void {{info.title.lower()}}_terminate() {
    k_i2c_terminate(&i2c_bus);
}

{% for key,register in registers|dictsort -%}
{% set length = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
int {{info.title.lower()}}_read{{key}}({{cpp.numtype(register.length)}}* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, {{length}}) != I2C_OK) {
        return -2;
    }
    return 0;
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
int {{info.title.lower()}}_write{{key}}({% if register.length > 0 %}{{cpp.numtype(register.length)}}* data{% endif %}) {
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
}{% endif %}

{%- endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Getter #}
int {{info.title.lower()}}_get_{{key.lower()}}({{int_t}}* val) {
    // Read register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(val);
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

int {{info.title.lower()}}_set_{{key.lower()}}({{int_t}}* data) {
    {% if field.bitEnd %}
    // Bitshift value
    data = data << {{field.bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    {{int_t}} register_data;
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(&register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = {{info.title.lower()}}_write{{field.register[12:]}}(&register_data);
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
{% for ckey,compute in function.computed|dictsort %}
{% set int_t = cpp.returnType(compute) %}
void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}({% if 'return' in compute %}{{int_t}}* val{% if 'input' in compute %},{% endif %}{% endif %}{% if 'input' in compute %} {{cpp.params(compute)}}{% endif %}) {
    {# Declare our variables #}
{{ cpp.variables(compute.variables) }}

    {# Read `value` if applicable #}
    {% if 'input' in compute %}
    {%- for vkey,variable in compute.input|dictsort %}
    {% if vkey == 'value' %}
    // Read value of register into a variable
    value = {{info.title.lower()}}_get_{{function.register[12:]}}(val);
    {% endif %}
    {% endfor -%}
    {% endif %}
    {# Handle the logic #}
{{ logic(compute.logic, function) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if 'return' in compute and compute.return is not string %}
    val = [{% for returnValue in compute.return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}];
    {# Return a plain value #}
    {% elif compute.return is string %}
    val = {{compute.return}};
    {% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}