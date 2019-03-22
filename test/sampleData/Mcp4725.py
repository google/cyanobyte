# Copyright (C) 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Auto-generated file for Mcp4725 v0.1.0.
# Generated from peripherals/Mcp4725.yaml using Cyanobyte Codegen v0.1.0
"""
Class for Mcp4725
"""

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)

def _swap_endian(val):
    """
    Swap the endianness of a short only
    """
    return val >> 8 | val << 8

class Mcp4725:
    """
    Microchip 4725 Digital-to-Analog Converter

    """
    DEVICE_ADDRESS = 98
    REGISTER_VOUT = 64
    REGISTER_EEPROM = 96

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)


    def get_vout(self):
        """
        VOut = (Vcc * value) / 4096
        The output is a range between 0 and Vcc with
        steps of Vcc/4096.
        In a 3.3v system, each step is 800 microvolts.

        """
        val = self.bus.read_i2c_block_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_VOUT
        )
        val = _swap_endian(val)
        return val

    def set_vout(self, data):
        """
        VOut = (Vcc * value) / 4096
        The output is a range between 0 and Vcc with
        steps of Vcc/4096.
        In a 3.3v system, each step is 800 microvolts.

        """
        data = _swap_endian(data)
        self.bus.write_i2c_block_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_VOUT,
            data
        )

    def get_eeprom(self):
        """
        If EEPROM is set, the saved voltage output will
        be loaded from power-on.

        """
        val = self.bus.read_i2c_block_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_EEPROM
        )
        val = _swap_endian(val)
        return val

    def set_eeprom(self, data):
        """
        If EEPROM is set, the saved voltage output will
        be loaded from power-on.

        """
        data = _swap_endian(data)
        self.bus.write_i2c_block_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_EEPROM,
            data
        )
