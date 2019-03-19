# Copyright (C) 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Auto-generated file for Mcp4725.
# Generated from peripherals/Mcp4725.yaml using PROJECT_NAME v0.1.0

import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)

class Mcp4725
    DEVICE_ADDRESS = 98
    REGISTER_VOUT = 64
    REGISTER_EEPROM = 96

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    def _swap_endian(val):
        # short data type only
        return val >> 8 | val << 8
    

    def setVOut(data):
        """
        VOut = (Vcc * value) / 4096
The output is a range between 0 and Vcc with
steps of Vcc/4096.
In a 3.3v system, each step is 800 microvolts.

        """
        data = self._swap_endian(data)
        bus.write_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_VOUT,
            data
        )

    def getEEPROM():
        """
        If EEPROM is set, the saved voltage output will
be loaded from power-on.

        """
        val = bus.read_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_EEPROM
        )
        val = self._swap_endian(val)
        return val

    def setEEPROM(data):
        """
        If EEPROM is set, the saved voltage output will
be loaded from power-on.

        """
        data = self._swap_endian(data)
        bus.write_i2c_block_data(
            DEVICE_ADDRESS,
            REGISTER_EEPROM,
            data
        )
