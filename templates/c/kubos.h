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
{% if functions %}
{% for key,function in functions|dictsort %}
{# Check if we need to import `math` lib #}
{% for ckey,compute in function.computed|dictsort %}
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
{{- scanForMathLib(compute.logic) -}}
{% endfor %}
{% endfor %}
{% endif %}

{# Create enums for fields #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if field.enum %}
{# Create enum #}
/*
{{utils.pad_string(" * ", "Valid values for " + field.title)}}
 */
enum {{key}} {
    {% set args = namespace(index=0) %}
    {% for ekey,enum in field.enum|dictsort %}
    {{key.upper()}}_{{ekey.upper()}} = {{enum.value}}{{- "," if args.index + 1 < field.enum | length }} // {{enum.title}}
    {% set args.index = args.index + 1 %}
    {% endfor %}
};
typedef enum {{key}} {{key}}_t;
{% endif %}
{% endfor %}
{% endif %}
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
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
/**
 {{utils.pad_string(" * ", register.description)}}
*/
int {{info.title.lower()}}_read{{key}}({{cpp.numtype(register.length)}}* val);
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
/**
{{utils.pad_string(" * ", register.description)}}
 */
int {{info.title.lower()}}_write{{key}}({% if register.length > 0 %}{{cpp.numtype(register.length)}}* data{% endif %});{% endif %}
{%- endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
/**
{{utils.pad_string(" * ", field.description)}}
 */
int {{info.title.lower()}}_get_{{key.lower()}}({{int_t}}* val);
{% endif %}
{% if 'W' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
/**
{{utils.pad_string(" * ", field.description)}}
 */
int {{info.title.lower()}}_set_{{key.lower()}}({{int_t}}* data);
{% endif %}
{% endfor %}
{% endif %}

{% if functions %}
{% for key,function in functions|dictsort %}
{% for ckey,compute in function.computed|dictsort %}
{% set int_t = cpp.returnType(compute) %}
/**
{{utils.pad_string(" * ", function.description)}}
*/
void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}({% if 'return' in compute %}{{int_t}}* val{% if 'input' in compute %},{% endif %}{% endif %}{% if 'input' in compute %} {{cpp.params(compute)}}{% endif %});
{% endfor %}

{% endfor %}
{% endif %}

#endif