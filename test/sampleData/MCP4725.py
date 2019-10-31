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
# Auto-generated file for MCP4725 v0.1.0.
# Generated from peripherals/MCP4725.yaml using Cyanobyte Codegen v0.1.0
"""
Class for MCP4725
"""

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)
from enum import Enum


class DigitalOutValues(Enum):
    """
    Valid values for Digital (binary) output

    """
    VCC = 4095 # Vcc (full power)
    GND = 0 # Ground

def _swap_endian(val):
    """
    Swap the endianness of a short only
    """
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8


class MCP4725:
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
        val = self.bus.read_word_data(
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
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_VOUT,
            data
        )
    def get_eeprom(self):
        """
        If EEPROM is set, the saved voltage output will
        be loaded from power-on.

        """
        val = self.bus.read_word_data(
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
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_EEPROM,
            data
        )


    def get_digitalout(self):
        """
        Only allows you to send fully on or off

        """
        # Read register data
        # '#/registers/EEPROM' > 'EEPROM'
        val = self.get_eeprom()
        # Mask register value
        val = val & 0b0000111111111111
        return val

    def set_digitalout(self, data):
        """
        Only allows you to send fully on or off

        """
        # Read current register data
        # '#/registers/EEPROM' > 'EEPROM'
        register_data = self.get_eeprom()
        register_data = register_data | data
        self.set_eeprom(register_data)

    def set_setvout(self, data):
        """
        set vout

        """
        # Read current register data
        # '#/registers/EEPROM' > 'EEPROM'
        register_data = self.get_eeprom()
        register_data = register_data | data
        self.set_eeprom(register_data)
    def setvout_asvoltage(self, vcc, output):
        """
        set vout

        """

        output = output / vcc * 4096
        self.set_eeprom(output)

        return []

    def get_getvout(self):
        """
        get vout

        """
        # Read register data
        # '#/registers/EEPROM' > 'EEPROM'
        val = self.get_eeprom()
        # Mask register value
        val = val & 0b0000111111111111
        return val
    def getvout_asvoltage(self, vcc):
        """
        get vout

        """
        voltage = None # Variable declaration

        # Read value of register into a variable
        value = self.get_eeprom()
        voltage = value / 4096 * vcc

        return voltage
