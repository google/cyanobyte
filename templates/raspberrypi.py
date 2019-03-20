{% import 'macros.jinja2' as utils %}
{{ utils.pad_string('# ', utils.license('Google Inc.', '2019', info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)

class {{ info.title }}
    """
{{utils.pad_string("    ", info.description)}}
    """
    DEVICE_ADDRESS = {{i2c.address}}
    {% for register in registers %}
    REGISTER_{{utils.object_key(register).upper()}} = {{register.address}}
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

    def get_{{utils.object_key(register).lower()}}():
        """
{{utils.pad_string("        ", register.description)}}
        """
        val = bus.read_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{utils.object_key(register).upper()}}
        )
        {% if i2c.endian == 'little' %}
        val = self._swap_endian(val)
        {% endif %}
        return val

    def set_{{utils.object_key(register).lower()}}(data):
        """
{{utils.pad_string("        ", register.description)}}
        """
        {% if i2c.endian == 'little' %}
        data = self._swap_endian(data)
        {% endif %}
        bus.write_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_{{utils.object_key(register).upper()}},
            data
        )
    {% endfor %}
