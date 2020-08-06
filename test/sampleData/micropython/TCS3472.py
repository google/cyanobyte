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
# Auto-generated file for TCS3472 v0.1.0.
# Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
"""
Class for TCS3472
"""

from machine import I2C

INIT_POWER = 1 # Power
INIT_RGBC = 2 # Color






class TCS3472:
    """
    Color Light-to-Digital Converter with IR Filter

    """
    device_address = 41
    REGISTER_BLUE = 186
    REGISTER_CLEAR = 180
    REGISTER_ENABLE = 128
    REGISTER_GREEN = 184
    REGISTER_RED = 182

    def __init__(self, i2c):
        # Initialize connection to peripheral
        self.i2c = i2c
        self._lifecycle_begin()

    def get_blue(self):
        """
        Blue light as an int. Divide by ambient light to get scaled number.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_BLUE,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def get_clear(self):
        """
        This is the ambient amount of detected light.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_CLEAR,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def get_enable(self):
        """
        Enable specific components of the peripheral

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ENABLE,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def set_enable(self, data):
        """
        Enable specific components of the peripheral

        """
        buffer = []
        buffer[0] = (data >> 0) & 0xFF
        self.i2c.writeto_mem(
            self.device_address,
            self.REGISTER_ENABLE,
            buffer,
            addrsize=8
        )
    def get_green(self):
        """
        Green light as an int. Divide by ambient light to get scaled number.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_GREEN,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def get_red(self):
        """
        Red light as an int. Divide by ambient light to get scaled number.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_RED,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val



    def get_init(self):
        """
        Enable RGBC and Power

        """
        # Read register data
        # '#/registers/enable' > 'enable'
        val = self.get_enable()
        # Mask register value
        val = val & 0b0000000011111111
        return val

    def set_init(self, data):
        """
        Enable RGBC and Power

        """
        # Read current register data
        # '#/registers/enable' > 'enable'
        register_data = self.get_enable()
        register_data = register_data | data
        self.set_enable(register_data)
    def _lifecycle_begin(self):
        """
        Enables features on device

        """
        enables = None # Variable declaration

        enables = (1+2)
        self.set_enable(enables)
