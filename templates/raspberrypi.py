# Copyright (C) 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}

{% macro objectKey(yamlObject) %}
{% for prop, val in yamlObject.items() %}
{% if val == None -%}
{{prop}}
{%- endif %}
{% endfor %}
{% endmacro %}

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)

class {{ info.title }}
    """
    {{ info.description }}
    """
    DEVICE_ADDRESS = {{i2c.address}}
    {% for register in registers %}
    REGISTER_{{objectKey(register).upper()}} = {{register.address}}
    {% endfor %}

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    {% if i2c.endian == 'little' %}
    def _swap_endian(val):
        # short data type only
        return val >> 8 | val << 8
    {% endif %}

    {% for register in registers %}

    def get{{objectKey(register)}}():
        """
        {{register.description}}
        """
        val = bus.read_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{objectKey(register).upper()}}
        )
        {% if i2c.endian == 'little' %}
        val = self._swap_endian(val)
        {% endif %}
        return val

    def set{{objectKey(register)}}(data):
        """
        {{register.description}}
        """
        {% if i2c.endian == 'little' %}
        data = self._swap_endian(data)
        {% endif %}
        bus.write_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{objectKey(register).upper()}},
            data
        )
    {% endfor %}
