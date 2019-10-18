{% import 'macros.jinja2' as utils %}
{% set template = namespace(math=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

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
{%- if sign -%}
{%- if len <= 8 -%}
char
{%- elif len <= 16 -%}
short
{%- elif len <= 32 -%}
long
{%- else -%}
long long
{%- endif -%}
{%- else -%}
{%- if len <= 8 -%}
uint8_t
{%- elif len <= 16 -%}
uint16_t
{%- elif len <= 32 -%}
uint32_t
{%- else -%}
uint64_t
{%- endif -%}
{%- endif -%}
{%- endmacro %}

#ifndef _{{info.title}}_H_
#define _{{info.title}}_H_
#include <Arduino.h>
#include <Wire.h>
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

class {{info.title}} {
    public:
        {{info.title}}(TwoWire& wire);

        int begin();
        void end();
        {% for register in registers -%}
        {% for key in register.keys() %}
        /**
{{utils.pad_string("         * ", register[key].description)}}
         */
        {{numtype(register[key].length)}} read{{key}}();

        /**
{{utils.pad_string("         * ", register[key].description)}}
         */
        int write{{key}}(uint8_t data);
        {% endfor %}
        {%- endfor %}
        {% for function in functions %}
        {% for key in function.keys() %}
        {% if 'R' is in(function[key].readWrite) %}
        /**
{{utils.pad_string("         * ", function[key].description)}}
         */
        {{numtype(register[function[key].register[12:]].length)}} get{{key}}();
        {% endif %}
        {% if 'W' is in(function[key].readWrite) %}
        /**
{{utils.pad_string("         * ", function[key].description)}}
         */
        int set{{key}}(uint8_t data);
        {% endif %}

        {% if function[key].computed %}
        {% for compute in function[key].computed %}
        {% for computeKey in compute.keys() %}
        /**
{{utils.pad_string("         * ", function[key].description)}}
         */
        {% if compute[computeKey].input %}
        {{numconv(compute[computeKey].returnType)}} {{key}}{{computeKey}}({{params(compute[computeKey].input)}});
        {% else %}
        {{numconv(compute[computeKey].returnType)}} {{key}}{{computeKey}}();
        {% endif %}
        {% endfor %}
        {% endfor %}
        {% endif %}

        {% endfor %}
        {% endfor %}

    private:
        TwoWire* _wire;
};

#endif
