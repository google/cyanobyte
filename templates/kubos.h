{% import 'macros.jinja2' as utils %}
{% import 'clang.jinja2' as cpp %}
{% set template = namespace(math=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

#ifndef _{{info.title}}_H_
#define _{{info.title}}_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c.h"

{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{# Check if we need to import `math` lib #}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% macro scanForMathLib(logicKeys) -%}
{% for logic in logicKeys %}
{% if logic is mapping %}
{% for logicKey in logic.keys() %}
{% if logicKey == 'power' or logicKey == 'arc tangent' %}
{% if template.math is sameas false %}
#include <math.h>
{% set template.math = true %}
{% endif %}
{% elif logic[logicKey] is iterable and logic[logicKey] is not string -%}
{{- scanForMathLib(logic[logicKey]) -}}
{% endif %}
{% endfor %}
{% endif %}
{% endfor %}
{%- endmacro %}
{{- scanForMathLib(compute[computeKey].logic) -}}
{% endfor %}
{% endfor %}
{% endfor %}
{% endfor %}

{# Create enums for fields #}
{% for field in fields %}
{% for key in field.keys() %}
{% if field[key].enum %}
{# Create enum #}
/*
{{utils.pad_string(" * ", "Valid values for " + field[key].title)}}
 */
enum {{key}} {
    {% set args = namespace(index=0) %}
    {% for enumObject in field[key].enum %}
    {% for enumKey in enumObject.keys() %}
    {{key.upper()}}_{{enumKey.upper()}} = {{enumObject[enumKey].value}}{{- "," if args.index + 1 < field[key].enum | length }} // {{enumObject[enumKey].title}}
    {% set args.index = args.index + 1 %}
    {% endfor %}
    {% endfor %}
};
typedef enum {{key}} {{key}}_t;
{% endif %}
{% endfor %}
{% endfor %}
{% if i2c.address is iterable and i2c.address is not string %}
enum deviceAddress {
    {% for address in i2c.address %}
    I2C_ADDRESS_{{address}} = {{address}}{{ "," if not loop.last }}
    {% endfor %}
};
typedef enum deviceAddress deviceAddress_t;
{% endif %}

{% if i2c.address is iterable and i2c.address is not string %}
int {{info.title.lower()}}_init(deviceAddress_t address, char* bus_name);
{% else %}
int {{info.title.lower()}}_init(char* bus_name);
{% endif %}
void {{info.title.lower()}}_terminate();
{% for key,register in registers|dictsort -%}
{% set length = (register.length / 8) | round(1, 'ceil') | int %}
/**
 {{utils.pad_string(" * ", register.description)}}
*/
int {{info.title.lower()}}_read{{key}}({{cpp.numtype(register.length)}}* val);

/**
{{utils.pad_string(" * ", register.description)}}
 */
int {{info.title.lower()}}_write{{key}}({{cpp.numtype(register.length)}}* data);
{%- endfor %}

{% for field in fields %}
{% for key in field.keys() %}
{% if 'R' is in(field[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, field[key].register[12:]) %}
/**
{{utils.pad_string(" * ", field[key].description)}}
 */
int {{info.title.lower()}}_get_{{key.lower()}}({{int_t}}* val);
{% endif %}
{% if 'W' is in(field[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, field[key].register[12:]) %}
/**
{{utils.pad_string(" * ", field[key].description)}}
 */
int {{info.title.lower()}}_set_{{key.lower()}}({{int_t}}* data);
{% endif %}
{% endfor %}
{% endfor %}

{% for function in functions %}
{% for key in function.keys() %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% set int_t = cpp.returnType(compute[computeKey]) %}
/**
{{utils.pad_string(" * ", function[key].description)}}
*/
{% if compute[computeKey].input %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}({{int_t}}* val, {{cpp.params(compute[computeKey].input)}});
{% else %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}({{int_t}}* val);
{% endif %}
{% endfor %}
{% endfor %}

{% endfor %}
{% endfor %}

#endif