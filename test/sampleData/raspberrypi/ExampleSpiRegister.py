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
# Auto-generated file for ExampleSpi v0.1.0.
# Generated from peripherals/examplespi.yaml using Cyanobyte Codegen v0.1.0
"""
Class for ExampleSpi
"""

import smbus
import spidev




class ExampleSpiRegister:
    """
    Example of a package using SPI

    """
    device_address = 0
    REGISTER_REGISTERW = 0
    REGISTER_REGISTERX = 1
    REGISTER_REGISTERY = 2
    REGISTER_REGISTERZ = 3

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
        self.spi = spidev.SpiDev()
        self.device_address = 0
        bus = 0 # Only SPI bus 0 is available
        device = 1 # Chip select, 0 / 1 depending on connection
        self.spi.open(bus, device)
        self.spi.max_speed_hz = 16000
        self.spi.bits_per_word = 8
        self.spi.mode = 0b10

    def get_registerw(self):
        """
        An 8-bit register

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_REGISTERW
        )
        return val

    def set_registerw(self, data):
        """
        An 8-bit register

        """
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_REGISTERW,
            data
        )
    def get_registerx(self):
        """
        A 16-bit register

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_REGISTERX
        )
        return val

    def set_registerx(self, data):
        """
        A 16-bit register

        """
        self.bus.write_word_data(
            self.device_address,
            self.REGISTER_REGISTERX,
            data
        )
    def get_registery(self):
        """
        A 32-bit register

        """
        byte_list = self.bus.read_i2c_block_data(
            self.device_address,
            self.REGISTER_REGISTERY,
            4
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        val = val << 8 | byte_list[2]
        val = val << 8 | byte_list[3]
        return val

    def set_registery(self, data):
        """
        A 32-bit register

        """
        buffer = []
        buffer[0] = (data >> 24) & 0xFF
        buffer[1] = (data >> 16) & 0xFF
        buffer[2] = (data >> 8) & 0xFF
        buffer[3] = (data >> 0) & 0xFF
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_REGISTERY,
            buffer
        )
    def get_registerz(self):
        """
        A dummy register that has no data

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_REGISTERZ
        )
        return val

    def set_registerz(self):
        """
        A dummy register that has no data

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_REGISTERZ,
            []
        )

    def spi_read_registerw(self):
        """
        An 8-bit register

        """
        # Simple read request msg
        msg = [self.device_address, self.REGISTER_REGISTERW]
        result = self.spi.xfer2(msg)
        return result
    def spi_write_registerw(self, data):
        """
        An 8-bit register

        """
        # Build request msg
        msg = [self.device_address, self.REGISTER_REGISTERW]
        msg = msg + data
        result = self.spi.xfer2(msg)
        return result
    def spi_read_registerx(self):
        """
        A 16-bit register

        """
        # Simple read request msg
        msg = [self.device_address, self.REGISTER_REGISTERX]
        result = self.spi.xfer2(msg)
        return result
    def spi_write_registerx(self, data):
        """
        A 16-bit register

        """
        # Build request msg
        msg = [self.device_address, self.REGISTER_REGISTERX]
        msg = msg + data
        result = self.spi.xfer2(msg)
        return result
    def spi_read_registery(self):
        """
        A 32-bit register

        """
        # Simple read request msg
        msg = [self.device_address, self.REGISTER_REGISTERY]
        result = self.spi.xfer2(msg)
        return result
    def spi_write_registery(self, data):
        """
        A 32-bit register

        """
        # Build request msg
        msg = [self.device_address, self.REGISTER_REGISTERY]
        msg = msg + data
        result = self.spi.xfer2(msg)
        return result
    def spi_read_registerz(self):
        """
        A dummy register that has no data

        """
        # Simple read request msg
        msg = [self.device_address, self.REGISTER_REGISTERZ]
        result = self.spi.xfer2(msg)
        return result
    def spi_write_registerz(self):
        """
        A dummy register that has no data

        """
        # Build request msg
        msg = [self.device_address, self.REGISTER_REGISTERZ]
        result = self.spi.xfer2(msg)
        return result
