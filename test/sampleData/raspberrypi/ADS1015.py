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
# Auto-generated file for ADS1015 v0.1.0.
# Generated from peripherals/ADS1015.yaml using Cyanobyte Codegen v0.1.0
"""
Class for ADS1015
"""

from enum import Enum
import smbus

class ChannelValues(Enum):
    """
    Valid values for Set the channel to read

    """
    CHANNEL_1 = 0 # Channel 1
    CHANNEL_2 = 1 # Channel 2
    CHANNEL_3 = 2 # Channel 3
    CHANNEL_4 = 3 # Channel 4
class DeviceOperatingModeValues(Enum):
    """
    Valid values for Set the operating mode

    """
    CONTINUOUS_CONVERSION = 0 # Continuous Conversion
    SINGLE_SHOT = 1 # Single-shot or power-down state
class ProgrammableGainValues(Enum):
    """
    Valid values for Setup programmable gain

    """
    PGA0_256 = 5 # Plus/minus 0.256V
    PGA0_512 = 4 # Plus/minus 0.512V
    PGA1_024V = 3 # Plus/minus 1.024V
    PGA2_048V = 2 # Plus/minus 2.048V
    PGA4_096V = 1 # Plus/minus 4.096V
    PGA6_144V = 0 # Plus/minus 6.144V
class SampleRateValues(Enum):
    """
    Valid values for Setup sample rate for reading analog voltage

    """
    HZ128 = 0 # 128 samples/second
    HZ1600 = 4 # 1600 samples/second
    HZ2400 = 5 # 2400 samples/second
    HZ250 = 1 # 250 samples/second
    HZ3300 = 6 # 3300 samples/second
    HZ490 = 2 # 490 samples/second
    HZ920 = 3 # 920 samples/second

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


class ADS1015:
    """
    Texas Instruments Analog-Digital Converter

    """
    device_address = 73
    REGISTER_CONFIG = 1
    REGISTER_CONVERSION = 0

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    def get_config(self):
        """
        Describes the specifics of the sensing implementation

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_CONFIG
        )
        val = _swap_endian(val, 16)
        return val

    def set_config(self, data):
        """
        Describes the specifics of the sensing implementation

        """
        data = _swap_endian(data, 16)
        self.bus.write_word_data(
            self.device_address,
            self.REGISTER_CONFIG,
            data
        )
    def get_conversion(self):
        """
        Conversion register contains the result of the last conversion

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_CONVERSION
        )
        val = _swap_endian(val, 16)
        return val



    def set_deviceoperatingmode(self, data):
        """
        This bit controls the operating mode

        """
        # Bitshift value
        data = data << 8
        # Read current register data
        # '#/registers/Config' > 'Config'
        register_data = self.get_config()
        register_data = register_data | data
        self.set_config(register_data)

    def set_programmablegain(self, data):
        """
        This sets the programmable gain for reading analog voltage

        """
        # Bitshift value
        data = data << 9
        # Read current register data
        # '#/registers/Config' > 'Config'
        register_data = self.get_config()
        register_data = register_data | data
        self.set_config(register_data)

    def set_samplerate(self, data):
        """
        This sets the samples-per-second value

        """
        # Bitshift value
        data = data << 5
        # Read current register data
        # '#/registers/Config' > 'Config'
        register_data = self.get_config()
        register_data = register_data | data
        self.set_config(register_data)
    def analog_read(self, channel):
        """
        Reads the analog voltage in Volts

        """
        config = None # Variable declaration
        datum_a = None # Variable declaration
        datum_b = None # Variable declaration
        processed = None # Variable declaration
        programmable_gain = None # Variable declaration
        raw = None # Variable declaration

        config = self.get_config()
        config = (config|(channel << 12))
        config = (config|32768)
        self.set_config(config)
        raw = self.get_conversion()
        datum_a = (raw&65280)
        datum_a = (datum_a >> 8)
        datum_b = (raw&255)
        processed = ((datum_a << 4)|(datum_b >> 4))
        programmable_gain = 6144
        processed = ((processed/2047/1000)*programmable_gain)
        return processed
