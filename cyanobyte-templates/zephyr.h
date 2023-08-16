{% import 'macros.jinja2' as utils %}
{% import 'base.c.jinja2' as cpp %}
/*
 * SPDX-License-Identifier: {{info.license.name}}
 */

#ifndef CYANOBYTE_DRIVER_{{info.title}}_H_
#define CYANOBYTE_DRIVER_{{info.title}}_H_

#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>

#define DT_DRV_COMPAT {{info.title.lower()}}

#define {{info.title}}_BUS_I2C DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)

struct i2c_dt_spec i2c;

{% for key,register in registers|dictsort -%}
{% set length = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
typedef int {{info.title.lower()}}_read{{key | camel_to_snake}}(const struct device *dev, {{cpp.numtype(register.length)}}* val);
{% endif %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
typedef int {{info.title.lower()}}_write{{key | camel_to_snake}}(const struct device *dev, {% if register.length > 0 %}{{cpp.numtype(register.length)}} data{% endif %});
{% endif %}
{%- endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Getter #}
typedef int {{info.title.lower()}}_get_{{key.lower()}}(const struct device *dev, {{int_t}}* val);
{% endif -%}
{%- if 'W' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Setter #}
typedef int {{info.title.lower()}}_set_{{key.lower()}}(const struct device *dev, {{int_t}}* data);
{% endif %}
{% endfor %}
{% endif %}

{% if functions %}
{% for key,function in functions|dictsort %}
{% for ckey,compute in function.computed|dictsort %}
{% set int_t = cpp.returnType(compute) %}
typedef void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}(const struct device *dev, {% if 'return' in compute %}{{int_t}}* val{% if 'input' in compute %},{% endif %}{% endif %}{% if 'input' in compute %} {{cpp.params(compute)}}{% endif %});
{% endfor %}
{% endfor %}
{% endif %}

extern const struct {{info.title.lower()}}_bus_io {{info.title.lower()}}_bus_io_i2c;

#endif /* CYANOBYTE_DRIVER_{{info.title}}_H_ */