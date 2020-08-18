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
# Auto-generated file for ExampleSpiEmboss v0.1.0.
# Generated from peripherals/examplespi-emboss.yaml
# using Cyanobyte Codegen v0.1.0
"""
Class for ExampleSpiEmboss
"""

import smbus
import spidev




class ExampleSpiEmboss:
    """
    Example of a package using SPI with Emboss messages

    """
    device_address = 0
    REGISTER_PLACEHOLDER = 0

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

    @classmethod
    def msg_float_floats(
            cls,
            float_little_endian,
            float_big_endian,
    ): # Put params here
        """
        Encodes float floats data into a buffer
        """
        msg = 0
        msg |= float_little_endian
        msg |= float_big_endian << 32
        return msg # Return the message data structure here

    @classmethod
    def decode_float_floats(cls, msg): # Put params here
        """
        Decodes float floats data from a buffer
        """
        res = []
        float_little_endian = msg
        float_little_endian &= 1 << 4 - 1
        res.append(float_little_endian)

        float_big_endian = msg >> 32
        float_big_endian &= 1 << 4 - 1
        res.append(float_big_endian)

        return res # Return the decoded msg

    def spi_write_float_floats(
            self,
            float_little_endian,
            float_big_endian,
    ): # Put params here
        """
        Writes message float floats on SPI bus
        """
        # Build request msg
        msg = self.msg_float_floats(float_little_endian, float_big_endian)
        result = self.spi.xfer2(msg)
        return result
    @classmethod
    def msg_float_doubles(
            cls,
            double_little_endian,
            double_big_endian,
    ): # Put params here
        """
        Encodes float doubles data into a buffer
        """
        msg = 0
        msg |= double_little_endian
        msg |= double_big_endian << 64
        return msg # Return the message data structure here

    @classmethod
    def decode_float_doubles(cls, msg): # Put params here
        """
        Decodes float doubles data from a buffer
        """
        res = []
        double_little_endian = msg
        double_little_endian &= 1 << 8 - 1
        res.append(double_little_endian)

        double_big_endian = msg >> 64
        double_big_endian &= 1 << 8 - 1
        res.append(double_big_endian)

        return res # Return the decoded msg

    def spi_write_float_doubles(
            self,
            double_little_endian,
            double_big_endian,
    ): # Put params here
        """
        Writes message float doubles on SPI bus
        """
        # Build request msg
        msg = self.msg_float_doubles(double_little_endian, double_big_endian)
        result = self.spi.xfer2(msg)
        return result

    def get_placeholder(self):
        """
        An 8-bit register

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_PLACEHOLDER
        )
        return val

    def set_placeholder(self, data):
        """
        An 8-bit register

        """
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_PLACEHOLDER,
            data
        )
