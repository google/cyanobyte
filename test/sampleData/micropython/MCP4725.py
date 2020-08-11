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

from machine import I2C

DIGITALOUT_GND = 0 # Ground
DIGITALOUT_VCC = 4095 # Vcc (full power)


def _swap_endian(val, length):
    """
    Swap the endianness of a number
    """
    if length <= 8:
        return val
    if length <= 16:
        return (val & 0xFF00) >> 8 | (val & 0xFF) << 8
    if length <= 32:
        return ((val & 0xFF000000) >> 24 |
                (val & 0x00FF0000) >> 8 |
                (val & 0x0000FF00) << 8 |
                (val & 0x000000FF) << 24)
    raise Exception('Cannot swap endianness for length ' + length)




class MCP4725:
    """
    Microchip 4725 Digital-to-Analog Converter

    """
    device_address = 98
    REGISTER_EEPROM = 96
    REGISTER_VOUT = 64

    def __init__(self, i2c):
        # Initialize connection to peripheral
        self.i2c = i2c

    def get_eeprom(self):
        """
        If EEPROM is set, the saved voltage output will
        be loaded from power-on.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_EEPROM,
            1,
            addrsize=12
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = _swap_endian(val, 12)
        return val

    def set_eeprom(self, data):
        """
        If EEPROM is set, the saved voltage output will
        be loaded from power-on.

        """
        data = _swap_endian(data, 12)
        buffer = []
        buffer[0] = (data >> 0) & 0xFF
        self.i2c.writeto_mem(
            self.device_address,
            self.REGISTER_EEPROM,
            buffer,
            addrsize=12
        )
    def get_vout(self):
        """
        VOut = (Vcc * value) / 4096
        The output is a range between 0 and Vcc with
        steps of Vcc/4096.
        In a 3.3v system, each step is 800 microvolts.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_VOUT,
            1,
            addrsize=12
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = _swap_endian(val, 12)
        return val

    def set_vout(self, data):
        """
        VOut = (Vcc * value) / 4096
        The output is a range between 0 and Vcc with
        steps of Vcc/4096.
        In a 3.3v system, each step is 800 microvolts.

        """
        data = _swap_endian(data, 12)
        buffer = []
        buffer[0] = (data >> 0) & 0xFF
        self.i2c.writeto_mem(
            self.device_address,
            self.REGISTER_VOUT,
            buffer,
            addrsize=12
        )


    def get_digitalout(self):
        """
        Only allows you to send fully on or off

        """
        # Read register data
        # '#/registers/EEPROM' > 'EEPROM'
        val = self.get_eeprom()
        # Mask register value
        val = val & 0b0001111111111111
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
    def getvout_asvoltage(self, vcc):
        """
        get vout

        """
        voltage = None # Variable declaration

        # Read value of register into a variable
        value = self.get_eeprom()
        voltage = value / 4096 * vcc
        return voltage
    def setvout_asvoltage(self, output, vcc):
        """
        set vout

        """

        output = output / vcc * 4096
        self.set_eeprom(output)
