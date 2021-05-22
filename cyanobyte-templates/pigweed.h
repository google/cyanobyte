{% import 'macros.jinja2' as utils %}
{% import 'base.c.jinja2' as cpp %}
{% set template = namespace(math=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

#pragma once

#include "pw_bytes/byte_builder.h"
#include "pw_chrono/system_clock.h"
#include "pw_i2c/address.h"
#include "pw_i2c/device.h"
#include "pw_i2c/initiator.h"
#include "pw_result/result.h"
#include "pw_status/status.h"

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

class {{info.title}} : RegisterDevice {
    public:
        {% if i2c.address is iterable and i2c.address is not string %}
        {{info.title}}(Initiator& initiator, deviceAddress_t address);
        deviceAddress_t DEVICE_ADDRESS;
        {% else %}
        {{info.title}}(Initiator& initiator);
        {% endif %}

        {% for key,register in registers|dictsort -%}
        {% set length = register.length %}
        {% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
        /**
{{utils.pad_string("         * ", register.description)}}
         */
        Result<{{cpp.numtype(register.length)}}> read{{key}}();
        {% endif %}

        {% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
        /**
{{utils.pad_string("         * ", register.description)}}
         */
        Status write{{key}}({% if length > 0 %}{{cpp.numtype(length)}} data{% endif %});{% endif %}

        {% endfor %}
        {% if fields %}
        {% for key,field in fields|dictsort %}
        {% if 'R' is in(field.readWrite) %}
        /**
{{utils.pad_string("         * ", field.description)}}
         */
        Result<{{cpp.registerSize(registers, field.register[12:])}}> get{{key}}();
        {% endif %}
        {% if 'W' is in(field.readWrite) %}
        /**
{{utils.pad_string("         * ", field.description)}}
         */
        Status set{{key}}(uint8_t data);
        {% endif %}
        {% endfor %}
        {% endif %}

        {% if functions %}
        {% for key,function in functions|dictsort %}
        {% for ckey,compute in function.computed|dictsort %}
        /**
{{utils.pad_string("         * ", function.description)}}
         */
        {% if 'input' in compute %}
        {{cpp.returnType(compute)}} {{key}}{{ckey}}({{cpp.params(compute)}});
        {% else %}
        {{cpp.returnType(compute)}} {{key}}{{ckey}}({{cpp.params(compute)}});
        {% endif %}
        {% endfor %}

        {% endfor %}
        {% endif %}
};
