# Copyright (C) 2020 Google Inc.
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
# Auto-generated file for BH1750FVI v0.1.0.
# Generated from peripherals/BH1750FVI.yaml using Cyanobyte Codegen v0.1.0
"""
Class for BH1750FVI
"""

from enum import Enum
import smbus

class DeviceAddressValues(Enum):
    """
    Valid device addresses
    """
    I2C_ADDRESS_35 = 35
    I2C_ADDRESS_92 = 92



class BH1750FVI:
    """
    Rohm Light Sensor

    """
    REGISTER_CONTINUOUSHRES2MODE = 17
    REGISTER_CONTINUOUSHRESMODE = 16
    REGISTER_CONTINUOUSLYLRESMODE = 19
    REGISTER_ONCEHRES2MODE = 33
    REGISTER_ONCEHRESMODE = 32
    REGISTER_ONCELRESMODE = 35
    REGISTER_POWERDOWN = 0
    REGISTER_POWERON = 1
    REGISTER_RESET = 7

    def __init__(self, address):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
        self.device_address = address
        self._lifecycle_begin()


    def set_continuoushres2mode(self):
        """
        Start measurement at 0.5lx resolution. Typically 120ms.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_CONTINUOUSHRES2MODE,
            []
        )

    def set_continuoushresmode(self):
        """
        Start measurement at 1lx resolution. Typically 120ms.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_CONTINUOUSHRESMODE,
            []
        )

    def set_continuouslylresmode(self):
        """
        Start measurement at 4lx resolution. Typically 16ms.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_CONTINUOUSLYLRESMODE,
            []
        )

    def set_oncehres2mode(self):
        """
        Start measurement at 0.5lx resolution. Typically 120ms.
        Power Down after measurement.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_ONCEHRES2MODE,
            []
        )

    def set_oncehresmode(self):
        """
        Start measurement at 1lx resolution. Typically 120ms.
        Power Down after measurement.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_ONCEHRESMODE,
            []
        )

    def set_oncelresmode(self):
        """
        Start measurement at 4lx resolution. Typically 16ms.
        Power Down after measurement.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_ONCELRESMODE,
            []
        )

    def set_powerdown(self):
        """
        No active state

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_POWERDOWN,
            []
        )

    def set_poweron(self):
        """
        Waiting for measurement command

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_POWERON,
            []
        )

    def set_reset(self):
        """
        Reset data register value. Not accepted in Power Down mode.

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_RESET,
            []
        )

    def _lifecycle_begin(self):
        """
        Sends a POWER ON cmd to device

        """

        self.set_poweron()
    def command_powerdown(self):
        """
        Things you can do to device

        """

        self.set_powerdown()
    def command_reset(self):
        """
        Things you can do to device

        """

        self.set_poweron()
        self.set_reset()
    def read_lightintensity(self):
        """
        Read light intensity from device

        """
        intensity = None # Variable declaration

        intensity = 0
        _datum = self.bus.read_byte(self.device_address)
        intensity = intensity << 8 | _datum
        _datum = self.bus.read_byte(self.device_address)
        intensity = intensity << 8 | _datum
        return intensity
