{% import 'macros.jinja2' as utils %}
{% import 'base.c.jinja2' as cpp %}
/* {{info.title}}.c - Driver for {{info.description}} */

/*
 * SPDX-License-Identifier: {{info.license.name}}
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/init.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/pm/device.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/__assert.h>

#include <zephyr/logging/log.h>

#include "{{info.title}}.h"
{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{% if step[key] is mapping and 'rawRead' in step[key] %}
    {% set length = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
    k_i2c_read(i2c_bus, DEVICE_ADDRESS, {{key}}, {{length}});
    {% break %}
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == '$cmdWrite' %}
    {% if 'value' in step[key] %}
    {{info.title.lower()}}_write{{step[key].register[12:]}}(&{{step[key].value}});
    {% else %}
    {{info.title.lower()}}_write{{step[key].register[12:]}}();
    {% endif %}
    {% break %}
{% endif %}
{% if key == "$delay" %}
    nanosleep(0, {{ step[key].for * 1000 }})
{{ logic(step[key].after, function) }}
    {% break %}
{% endif %}
{# Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
    {{key}} {{step[key]}}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
    {{info.title.lower()}}_write{{function.register[12:]}}(dev, &{{step[key]}});
{% endif %}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
    {{info.title.lower()}}_read{{step[key][12:] | camel_to_snake}}(dev, &{{key}});
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

LOG_MODULE_REGISTER({{info.title}}, CONFIG_SENSOR_LOG_LEVEL);

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "{{info.title}} driver enabled without any devices"
#endif

{% if i2c.address is number %}
#define DEVICE_ADDRESS {{i2c.address}}
{% endif %}

struct {{info.title.lower()}}_data {
{% for key,register in registers|dictsort %}
  {{cpp.numtype(register.length)}} {{key | camel_to_snake}};
{% endfor %}
}

static inline int bme280_bus_check(const struct device *dev)
{
	const struct bme280_config *cfg = dev->config;

	return cfg->bus_io->check(&cfg->bus);
}

{% for key,register in registers|dictsort -%}
{% set length = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
int {{info.title.lower()}}_read{{key | camel_to_snake}}(const struct device *dev, {{cpp.numtype(register.length)}}* val) {
  const struct bme280_config *cfg = dev->config;
  return cfg->bus_io->read(&cfg->bus, {{register.address}}, val, {{length}});
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
int {{info.title.lower()}}_write{{key | camel_to_snake}}(const struct device *dev, {% if register.length > 0 %}{{cpp.numtype(register.length)}} data{% endif %}) {
  const struct bme280_config *cfg = dev->config;
 // FIXME params

  return cfg->bus_io->write(&cfg->bus, {{register.address}}, data);
}{% endif %}

{%- endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{% set int_t = cpp.registerSize(registers, field.register[12:]) %}
{# Getter #}
int {{info.title.lower()}}_get_{{key.lower()}}(const struct device *dev, {{int_t}}* val) {
    // Read register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(dev, val);
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

int {{info.title.lower()}}_set_{{key.lower()}}(const struct device *dev, {{int_t}}* data) {
    {% if field.bitEnd %}
    // Bitshift value
    data = data << {{field.bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    {{int_t}} register_data;
    int result = {{info.title.lower()}}_read{{field.register[12:]}}(dev, &register_data);
    if (result != 0) {
        return -1;
    }
    register_data = register_data | data;
    result = {{info.title.lower()}}_write{{field.register[12:]}}(dev, &register_data);
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
void {{info.title.lower()}}_{{key.lower()}}_{{ckey.lower()}}(const struct device *dev, {% if 'return' in compute %}{{int_t}}* val{% if 'input' in compute %},{% endif %}{% endif %}{% if 'input' in compute %} {{cpp.params(compute)}}{% endif %}) {
    {# Declare our variables #}
{{ cpp.variables(compute.variables) }}

    {# Read `value` if applicable #}
    {% if 'input' in compute %}
    {%- for vkey,variable in compute.input|dictsort %}
    {% if vkey == 'value' %}
    // Read value of register into a variable
    value = {{info.title.lower()}}_get_{{function.register[12:]}}(dev, val);
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

/* Do a measurement and fetch the data from the sensor */
static int {{info.title.lower()}}_sample_fetch(const struct device *dev,
			       enum sensor_channel chan)
{
	LOG_DBG("Fetching sample from {{info.title}}");
	LOG_ERR("TODO: Link values with samples");
	return -EINVAL;
}

/* Get the measurement data */
static int {{info.title.lower()}}_channel_get(const struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct {{info.title.lower()}}_data *data = dev->data;
	return -EINVAL;
}

static const struct sensor_driver_api {{info.title.lower()}}_api_funcs = {
	.sample_fetch = {{info.title.lower()}}_sample_fetch,
	.channel_get = {{info.title.lower()}}_channel_get,
};

static int {{info.title.lower()}}_chip_init(const struct device *dev)
{
	struct {{info.title.lower()}}_data *data = dev->data;
	int err;

	{% for key,register in registers|dictsort %}
	{% set length = (register.length / 8) | round(1, 'ceil') | int %}
	err = {{info.title.lower()}}_read{{key | camel_to_snake}}(dev, {{length}});
	if (err < 0) {
		LOG_DBG("ID read failed for {{key}}: %d", err);
		return err;
	}
	{% endfor %}

	// TODO: What happens when the device address is a list?
	if (data->chip_id == DEVICE_ADDRESS) {
		LOG_DBG("ID OK");
	} else {
		LOG_DBG("bad chip id 0x%x", data->chip_id);
		return -ENOTSUP;
	}

	/* Wait for the sensor to be ready */
	k_sleep(K_MSEC(1));

	LOG_DBG("\"%s\" OK", dev->name);
	return 0;
}

/* Initializes a struct bme280_config for an instance on an I2C bus. */
#define {{info.title}}_CONFIG_I2C(inst)			       \
	{					       \
		.bus.i2c = I2C_DT_SPEC_INST_GET(inst), \
		.bus_io = &{{info.title.lower()}}_bus_io_i2c,	       \
	}

/*
 * Main instantiation macro, which selects the correct bus-specific
 * instantiation macros for the instance.
 */
#define {{info.title}}_DEFINE(inst)						\
	static struct {{info.title.lower()}}_data {{info.title.lower()}}_data_##inst;			\
	static const struct {{info.title.lower()}}_cfg {{info.title.lower()}}_cfg_##inst = {				\
		.i2c = I2C_DT_SPEC_INST_GET(inst),					\
	};										\
									\
	SENSOR_DEVICE_DT_INST_DEFINE(inst, {{info.title.lower()}}_init, NULL,				\
			      &{{info.title.lower()}}_data_##inst, &{{info.title.lower()}}_cfg_##inst, POST_KERNEL,	\
			      CONFIG_SENSOR_INIT_PRIORITY, &{{info.title.lower()}}_api_funcs);		\

/* Create the struct device for every status "okay" node in the devicetree. */
DT_INST_FOREACH_STATUS_OKAY({{info.title}}_DEFINE)
