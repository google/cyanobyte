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
# Auto-generated file for Bmp280 v0.1.0.
# Generated from peripherals/Bmp280.yaml using Cyanobyte Codegen v0.1.0
"""
Class for Bmp280
"""





import sys
try:
    import smbus
except ImportError:
    print("Fatal error! Make sure to install smbus!")
    sys.exit(1)



def _sign(val, length):
    """
    Convert unsigned integer to signed integer
    """
    if val & (1 << (length - 1)):
        return val - (1 << length)
    return val

class Bmp280:
    """
    Bosch Digital Pressure Sensor

    """
    DEVICE_ADDRESS = 119
    REGISTER_TEMPMSB = 250
    REGISTER_TEMPLSB = 251
    REGISTER_TEMPXLSB = 252
    REGISTER_DIGT1 = 136
    REGISTER_DIGT2 = 138
    REGISTER_DIGT3 = 140

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)

    def get_tempmsb(self):
        """
        Part 1 of temperature

        """
        val = self.bus.read_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPMSB
        )
        return val

    def set_tempmsb(self, data):
        """
        Part 1 of temperature

        """
        self.bus.write_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPMSB,
            data
        )
    def get_templsb(self):
        """
        Part 2 of temperature

        """
        val = self.bus.read_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPLSB
        )
        return val

    def set_templsb(self, data):
        """
        Part 2 of temperature

        """
        self.bus.write_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPLSB,
            data
        )
    def get_tempxlsb(self):
        """
        Final part of temperature

        """
        val = self.bus.read_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPXLSB
        )
        return val

    def set_tempxlsb(self, data):
        """
        Final part of temperature

        """
        self.bus.write_byte_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_TEMPXLSB,
            data
        )
    def get_digt1(self):
        """
        Used for Celcius conversion

        """
        val = self.bus.read_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT1
        )
        return val

    def set_digt1(self, data):
        """
        Used for Celcius conversion

        """
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT1,
            data
        )
    def get_digt2(self):
        """
        Used for Celcius conversion

        """
        val = self.bus.read_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT2
        )
        return val

    def set_digt2(self, data):
        """
        Used for Celcius conversion

        """
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT2,
            data
        )
    def get_digt3(self):
        """
        Used for Celcius conversion

        """
        val = self.bus.read_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT3
        )
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def set_digt3(self, data):
        """
        Used for Celcius conversion

        """
        self.bus.write_word_data(
            self.DEVICE_ADDRESS,
            self.REGISTER_DIGT3,
            data
        )

    def temperature_asraw(self):
        """
        Reads the temperature

        """
        value_msb = None # Variable declaration
        value_lsb = None # Variable declaration
        value_xlsb = None # Variable declaration
        output = None # Variable declaration




        value_msb = self.get_tempmsb()


        value_lsb = self.get_templsb()


        value_xlsb = self.get_tempxlsb()


        output = ((value_msb << 12)+(value_lsb << 4)+(value_xlsb >> 4))


        return output
    def temperature_ascelsius(self):
        """
        Reads the temperature

        """
        value_msb = None # Variable declaration
        value_lsb = None # Variable declaration
        value_xlsb = None # Variable declaration
        value_d_t1 = None # Variable declaration
        value_d_t2 = None # Variable declaration
        value_d_t3 = None # Variable declaration
        raw_temp = None # Variable declaration
        raw_comp1 = None # Variable declaration
        raw_comp2 = None # Variable declaration
        raw_comp3 = None # Variable declaration
        celsius = None # Variable declaration




        value_msb = self.get_tempmsb()


        value_lsb = self.get_templsb()


        value_xlsb = self.get_tempxlsb()


        value_d_t1 = self.get_digt1()


        value_d_t2 = self.get_digt2()


        value_d_t3 = self.get_digt3()


        raw_temp = ((value_msb << 12)+(value_lsb << 4)+(value_xlsb >> 4))


        raw_comp1 = (((raw_temp/16384.0)-(value_d_t1/1024.0))*value_d_t2)


        raw_comp3 = ((raw_temp/131072.0)-(value_d_t1/8192.0))


        raw_comp2 = (raw_comp3*raw_comp3*value_d_t3)


        celsius = ((raw_comp1+raw_comp2)/5120.0)


        return celsius
