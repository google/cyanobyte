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
# Auto-generated file for Example v0.1.0.
# Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
"""
Class for Example
"""

from enum import Enum
import smbus

class FieldBValues(Enum):
    """
    Valid values for Write-only fields for RegisterA

    """
    VAL_1 = 1 # Value 1
    VAL_2 = 2 # Value 2
    VAL_3 = 4 # Value 3
    VAL_4 = 8 # Value 4
class DeviceAddressValues(Enum):
    """
    Valid device addresses
    """
    I2C_ADDRESS_16 = 16
    I2C_ADDRESS_32 = 32
    I2C_ADDRESS_48 = 48



class Example:
    """
    Example of a package

    """
    REGISTER_REGISTERA = 0
    REGISTER_REGISTERB = 1
    REGISTER_REGISTERC = 2
    REGISTER_REGISTERD = 3

    def __init__(self, address):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
        self.device_address = address
        self._lifecycle_begin()

    def get_registera(self):
        """
        An 8-bit register

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_REGISTERA
        )
        return val

    def set_registera(self, data):
        """
        An 8-bit register

        """
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_REGISTERA,
            data
        )
    def get_registerb(self):
        """
        A 16-bit register

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_REGISTERB
        )
        return val

    def set_registerb(self, data):
        """
        A 16-bit register

        """
        self.bus.write_word_data(
            self.device_address,
            self.REGISTER_REGISTERB,
            data
        )
    def get_registerc(self):
        """
        A 32-bit register

        """
        byte_list = self.bus.read_i2c_block_data(
            self.device_address,
            self.REGISTER_REGISTERC,
            4
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        val = val << 8 | byte_list[2]
        val = val << 8 | byte_list[3]
        return val

    def set_registerc(self, data):
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
            self.REGISTER_REGISTERC,
            buffer
        )
    def get_registerd(self):
        """
        A dummy register that has no data

        """
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_REGISTERD
        )
        return val

    def set_registerd(self):
        """
        A dummy register that has no data

        """
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_REGISTERD,
            []
        )


    def get_fielda(self):
        """
        This is a few bits

        """
        # Read register data
        # '#/registers/RegisterA' > 'RegisterA'
        val = self.get_registera()
        # Mask register value
        val = val & 0b0000000011110000
        # Bitshift value
        val = val >> 4
        return val

    def set_fieldb(self, data):
        """
        This is fewer bits

        """
        # Bitshift value
        data = data << 2
        # Read current register data
        # '#/registers/RegisterA' > 'RegisterA'
        register_data = self.get_registera()
        register_data = register_data | data
        self.set_registera(register_data)

    def get_fieldc(self):
        """
        A single-bit

        """
        # Read register data
        # '#/registers/RegisterA' > 'RegisterA'
        val = self.get_registera()
        # Mask register value
        val = val & 0b0000000000000010
        # Bitshift value
        val = val >> 1
        return val

    def set_fieldc(self, data):
        """
        A single-bit

        """
        # Bitshift value
        data = data << 1
        # Read current register data
        # '#/registers/RegisterA' > 'RegisterA'
        register_data = self.get_registera()
        register_data = register_data | data
        self.set_registera(register_data)
    def _lifecycle_begin(self):
        """
        Enables features on device

        """
        output = None # Variable declaration

        output = 1
        self.set_registera(output)
        return output
    def _lifecycle_end(self):
        """
        Enables features on device

        """
        output = None # Variable declaration

        output = 1
        self.set_registera(output)
        return output
    def return_array(self):
        """
        Computes and returns

        """
        summation = None # Variable declaration

        summation = (1024+1024)
        self.set_registera(summation)
        return [summation, summation]
    def return_number(self):
        """
        Computes and returns

        """
        summation = None # Variable declaration

        summation = (1024+1024)
        self.set_registera(summation)
        return summation
    def return_void(self):
        """
        Computes and returns

        """
        summation = None # Variable declaration

        summation = (1024+1024)
        self.set_registera(summation)
