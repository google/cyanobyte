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
#include <Arduino.h>
#include <Wire.h>
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

class {{info.title}} {
    public:
        {{info.title}}(TwoWire& wire);

        void begin();
        void end();
        {% for register in registers -%}
        {% for key in register.keys() %}
        {% set length = register[key].length %}
        /**
{{utils.pad_string("         * ", register[key].description)}}
         */
        {{cpp.numtype(register[key].length)}} read{{key}}();

        /**
{{utils.pad_string("         * ", register[key].description)}}
         */
        int write{{key}}({{cpp.numtype(length)}} data);
        {% endfor %}
        {%- endfor %}
        {% for field in fields %}
        {% for key in field.keys() %}
        {% if 'R' is in(field[key].readWrite) %}
        /**
{{utils.pad_string("         * ", field[key].description)}}
         */
        {{cpp.registerSize(registers, field[key].register[12:])}} get{{key}}();
        {% endif %}
        {% if 'W' is in(field[key].readWrite) %}
        /**
{{utils.pad_string("         * ", field[key].description)}}
         */
        int set{{key}}(uint8_t data);
        {% endif %}
        {% endfor %}
        {% endfor %}

        {% for function in functions %}
        {% for key in function.keys() %}
        {% for compute in function[key].computed %}
        {% for computeKey in compute.keys() %}
        /**
{{utils.pad_string("         * ", function[key].description)}}
         */
        {% if compute[computeKey].input %}
        {{cpp.returnType(compute[computeKey])}} {{key}}{{computeKey}}({{cpp.params(compute[computeKey])}});
        {% else %}
        {{cpp.returnType(compute[computeKey])}} {{key}}{{computeKey}}({{cpp.params(compute[computeKey])}});
        {% endif %}
        {% endfor %}
        {% endfor %}

        {% endfor %}
        {% endfor %}

    private:
        TwoWire* _wire;
};

#endif
