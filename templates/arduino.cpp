{% import 'macros.jinja2' as utils %}
{% import 'clang.jinja2' as cpp %}
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
{# // Check if a raw read-op #}
{% if step[key] is mapping and 'rawRead' in step[key] %}
    {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
    uint8_t _datum;
    _wire->beginTransmission(DEVICE_ADDRESS);
    {# // Here is where I do _not_ put `write(REGISTER_ADDR) #}
    _wire->requestFrom(DEVICE_ADDRESS, {{bytes}});
    {# Read a byte at a time #}
    {% for n in range(bytes) %}
    _datum = _wire->read();
    {{key}} = {{key}} << 8 | _datum;
    {% endfor %}
    {% break %}
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
    {% if 'value' in step[key] %}
    write{{step[key].register[12:]}}({{step[key].value}});
    {% else %}
    write{{step[key].register[12:]}}();
    {% endif %}
    {% break %}
{% endif %}
{# // Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
    {{key}} {{step[key]}};
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == 'send' %}
    write{{function.register[12:]}}({{step[key]}});
{% endif %}
{# // Check if assignment is register read op #}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
    {{key}} = read{{step[key][12:]}}();
{% endif %}
{# // Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
    {{key}} = {{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}();
{% endif %}
{# // If the value is a list, then this is a logical setter #}
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
static short _sign(short val, char length) {
    // Convert unsigned integer to signed integer
    if (val & (1 << (length - 1))) {
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

{% if i2c.address is iterable and i2c.address is not string %}
{{info.title}}::{{info.title}}(TwoWire& wire, deviceAddress_t address) :
    _wire(&wire),
    DEVICE_ADDRESS ( address )
{
}
{% else %}
{{info.title}}::{{info.title}}(TwoWire& wire) :
    _wire(&wire)
{
}
{% endif %}

void {{info.title}}::begin() {
    _wire->begin();
    {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
    _lifecycleBegin();
    {% endif %}
}

{% if not options or not options.esp32 or options.esp32.end != False %}
void {{info.title}}::end() {
    _wire->end();
    {% if '_lifecycle' in functions and 'End' in functions._lifecycle.computed %}
    _lifecycleEnd();
    {% endif %}
}
{% endif %}

{% for key,register in registers|dictsort -%}
{% set length = register.length %}
{% set bytes = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
{{cpp.numtype(length)}} {{info.title}}::read{{key}}() {
    uint8_t datum;
    {{cpp.numtype(length)}} value;
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
    datum = _wire->read();
    value = value << 8 | datum;
    {% endfor %}

    return value;
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
int {{info.title}}::write{{key}}({% if length > 0 %}{{cpp.numtype(length)}} data{% endif %}) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[{{bytes + 1}}] = { (uint8_t) REGISTER_{{key.upper()}} };
    {% for n in range(bytes) %}
    buffer[{{n + 1}}] = (data >> {{8 * (bytes - n - 1)}}) & 0xFF;
    {% endfor %}
    _wire->write(buffer, {{bytes + 1}});
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}
{% endif %}

{% endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{# Getter #}
{{cpp.registerSize(registers, field.register[12:])}} {{info.title}}::get{{key}}() {
    // Read register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    uint8_t val = read{{field.register[12:]}}();
    // Mask register value
    val = val & {{utils.mask(field.bitStart, field.bitEnd)}};
    {% if field.bitEnd %}
    // Bitshift value
    val = val >> {{field.bitEnd}};
    {% endif %}
    return val;
}
{% endif -%}

{%- if 'W' is in(field.readWrite) %}
{# Setter #}

int {{info.title}}::set{{key}}(uint8_t data) {
    {% if field.bitEnd %}
    // Bitshift value
    data = data << {{field.bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    uint8_t register_data = read{{field.register[12:]}}();
    register_data = register_data | data;
    return write{{field.register[12:]}}(register_data);
}
{% endif %}
{% endfor %}
{% endif %}

{% if functions %}
{% for key,function in functions|dictsort %}
{% for ckey,compute in function.computed|dictsort %}
{% if 'input' in compute %}
{{cpp.returnType(compute)}} {{info.title}}::{{key}}{{ckey}}({{cpp.params(compute)}}) {
{% else %}
{{cpp.returnType(compute)}} {{info.title}}::{{key}}{{ckey}}({{cpp.params(compute)}}) {
{% endif %}
    {# Declare our variables #}
{{ cpp.variables(compute.variables) }}

    {# Read `value` if applicable #}
    {% if 'input' in compute %}
    {%- for vkey,variable in compute.input|dictsort %}
    {% if vkey == 'value' %}
    // Read value of register into a variable
    {{cpp.numconv(variable)}} value = read{{function.register[12:]}}();
    {% endif %}
    {% endfor %}
    {% endif %}
    {# Handle the logic #}
{{ logic(compute.logic, function) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if 'return' in compute and compute.return is not string %}
    {# In C languages, the array is a parameter `returnArray` you fill #}
    {% for variable in compute.return %}
    returnArray[{{loop.index - 1}}] = {{variable}};
    {% endfor %}
    {% endif %}
    {# Return a plain value #}
    {% if compute.return is string %}
    return {{compute.return}};
    {% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}