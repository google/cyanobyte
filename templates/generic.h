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

{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{# Check if we need to import `math` lib #}
{% if function[key].computed %}
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
{% endif %}
{% endfor %}
{% endfor %}

{# Create enums for functions #}
{% for function in functions %}
{% for key in function.keys() %}
{% if function[key].enum %}
{# Create enum #}
/*
{{utils.pad_string(" * ", "Valid values for " + function[key].title)}}
 */
enum {{key}} {
    {% set args = namespace(index=0) %}
    {% for enumObject in function[key].enum %}
    {% for enumKey in enumObject.keys() %}
    {{key.upper()}}_{{enumKey.upper()}} = {{enumObject[enumKey].value}}{{- "," if args.index + 1 < function[key].enum | length }} // {{enumObject[enumKey].title}}
    {% set args.index = args.index + 1 %}
    {% endfor %}
    {% endfor %}
};
typedef enum {{key}} {{key}}_t;
{% endif %}
{% endfor %}
{% endfor %}

int {{info.title.lower()}}_init(char* bus_name, int (*connect)(uint8_t));
{% for register in registers -%}
{% for key in register.keys() %}
{% set length = (register[key].length / 8) | round(1, 'ceil') | int %}   
/**
 {{utils.pad_string(" * ", register[key].description)}}
*/
int {{info.title.lower()}}_read{{key}}(
    {{cpp.numtype(register[key].length)}}* val,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
);

/**
{{utils.pad_string(" * ", register[key].description)}}
 */
int {{info.title.lower()}}_write{{key}}(
    {{cpp.numtype(register[key].length)}}* data,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t),
    int (*write)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
);
{% endfor %}
{%- endfor %}

{% for function in functions %}
{% for key in function.keys() %}
{% if 'R' is in(function[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, function[key].register[12:]) %}
/**
{{utils.pad_string(" * ", function[key].description)}}
 */
int {{info.title.lower()}}_get_{{key.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
);
{% endif %}
{% if 'W' is in(function[key].readWrite) %}
{% set int_t = cpp.registerSize(registers, function[key].register[12:]) %}
/**
{{utils.pad_string(" * ", function[key].description)}}
 */
int {{info.title.lower()}}_set_{{key.lower()}}(
    {{int_t}}* data,
    int (*read)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t),
    int (*write)(uint8_t, uint8_t, {{cpp.numtype(register[key].length)}}*, uint8_t)
);
{% endif %}

{% if function[key].computed %}
{% for compute in function[key].computed %}
{% for computeKey in compute.keys() %}
{% set int_t = cpp.returnType(compute[computeKey]) %}
/**
{{utils.pad_string(" * ", function[key].description)}}
*/
{% if compute[computeKey].input %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}(
    {{int_t}}* val,
    {{cpp.params(compute[computeKey].input)}},
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);
{% else %}
void {{info.title.lower()}}_{{key.lower()}}_{{computeKey.lower()}}(
    {{int_t}}* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);
{% endif %}
{% endfor %}
{% endfor %}
{% endif %}

{% endfor %}
{% endfor %}

#endif