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
# Auto-generated file for {{ name }}.
# Generated from {{ fileName }} using PROJECT_NAME v{{ version }}

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)

class {{ name }}
    DEVICE_ADDRESS = {{address}}
    {% for register in registers %}
    REGISTER_{{register.name.upper()}} = {{register.address}}
    {% endfor %}

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    {% if little_endian %}
    def _swap_endian(val):
        # short data type only
        return val >> 8 | val << 8
    {% endif %}
    
    {% for register in registers %}
    {% if register.getter %}

    def get{{register.name}}():
        """
        {{register.description}}
        """
        val = bus.read_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{register.name.upper()}}
        )
        {% if little_endian %}
        val = self._swap_endian(val)
        {% endif %}
        return val
    {% endif %}
    {% if register.setter %}

    def set{{register.name}}(data):
        """
        {{register.description}}
        """
        {% if little_endian %}
        data = self._swap_endian(data)
        {% endif %}
        bus.write_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{register.name.upper()}},
            data
        )
    {% endif %}
    {% endfor %}
