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

from enum import Enum
import smbus

class InitValues(Enum):
    """
    Valid values for Setup the device configuration

    """
    POWER = 1 # Power
    RGBC = 2 # Color



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

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
        self._lifecycle_begin()

    def get_blue(self):
        """
        Blue light as an int. Divide by ambient light to get scaled number.

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_BLUE
        )
        return val

    def get_clear(self):
        """
        This is the ambient amount of detected light.

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_CLEAR
        )
        return val

    def get_enable(self):
        """
        Enable specific components of the peripheral

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_ENABLE
        )
        return val

    def set_enable(self, data):
        """
        Enable specific components of the peripheral

        """
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_ENABLE,
            data
        )
    def get_green(self):
        """
        Green light as an int. Divide by ambient light to get scaled number.

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_GREEN
        )
        return val

    def get_red(self):
        """
        Red light as an int. Divide by ambient light to get scaled number.

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_RED
        )
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
