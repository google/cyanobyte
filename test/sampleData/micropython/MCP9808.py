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
# Auto-generated file for MCP9808 v0.1.0.
# Generated from peripherals/MCP9808.yaml using Cyanobyte Codegen v0.1.0
"""
Class for MCP9808
"""

from machine import I2C

LIMITHYSTERESIS_TEMP_0C = 0 # 0°C (power-up default)
LIMITHYSTERESIS_TEMP_1C5 = 1 # +1.5°C
LIMITHYSTERESIS_TEMP_3C = 2 # +3.0°C
LIMITHYSTERESIS_TEMP_6C = 3 # +6.0°C

SHUTDOWNMODE_CONTINOUSCONVERSION = 0 # Continuous conversion (power-up default)
SHUTDOWNMODE_SHUTDOWN = 1 # Shutdown (Low-Power mode)

I2C_ADDRESS_24 = 24
I2C_ADDRESS_25 = 25
I2C_ADDRESS_26 = 26
I2C_ADDRESS_27 = 27
I2C_ADDRESS_28 = 28
I2C_ADDRESS_29 = 29
I2C_ADDRESS_30 = 30
I2C_ADDRESS_31 = 31






class MCP9808:
    """
    This is a test description

    """
    REGISTER_CONFIGURATION = 1

    def __init__(self, i2c, address):
        # Initialize connection to peripheral
        self.i2c = i2c
        self.device_address = address

    def get_configuration(self):
        """
        The MCP9808 has a 16-bit Configuration register (CONFIG) that
        allows the user to set various functions for a robust temperature
        monitoring system.
        Bits 10 through 0 are used to select the temperature alert output
        hysteresis, device shutdown or Low-Power mode, temperature boundary
        and critical temperature lock, and temperature Alert output
        enable/disable.
        In addition, Alert output condition (output set for TUPPER and
        TLOWER temperature boundary or TCRIT only), Alert output status
        and Alert output polarity and mode (Comparator Output or Interrupt
        Output mode) are user-configurable.

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_CONFIGURATION,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def set_configuration(self, data):
        """
        The MCP9808 has a 16-bit Configuration register (CONFIG) that
        allows the user to set various functions for a robust temperature
        monitoring system.
        Bits 10 through 0 are used to select the temperature alert output
        hysteresis, device shutdown or Low-Power mode, temperature boundary
        and critical temperature lock, and temperature Alert output
        enable/disable.
        In addition, Alert output condition (output set for TUPPER and
        TLOWER temperature boundary or TCRIT only), Alert output status
        and Alert output polarity and mode (Comparator Output or Interrupt
        Output mode) are user-configurable.

        """
        buffer = []
        buffer[0] = (data >> 8) & 0xFF
        buffer[1] = (data >> 0) & 0xFF
        self.i2c.writeto_mem(
            self.device_address,
            self.REGISTER_CONFIGURATION,
            buffer,
            addrsize=16
        )


    def get_limithysteresis(self):
        """
        This bit can not be altered when either of the Lock bits are set
        (bit 6 and bit 7). This bit can be programmed in Shutdown mode.

        """
        # Read register data
        # '#/registers/configuration' > 'configuration'
        val = self.get_configuration()
        # Mask register value
        val = val & 0b0000011000000000
        # Bitshift value
        val = val >> 9
        return val

    def get_shutdownmode(self):
        """
        In shutdown, all power-consuming activities are disabled, though
        all registers can be written to or read. This bit cannot be set
        to ‘1’ when either of the Lock bits is set (bit 6 and bit 7).
        However, it can be cleared to ‘0’ for continuous conversion while
        locked.

        """
        # Read register data
        # '#/registers/configuration' > 'configuration'
        val = self.get_configuration()
        # Mask register value
        val = val & 0b0000000100000000
        # Bitshift value
        val = val >> 8
        return val
