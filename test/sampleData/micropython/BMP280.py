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
# Auto-generated file for BMP280 v0.1.0.
# Generated from peripherals/BMP280.yaml using Cyanobyte Codegen v0.1.0
"""
Class for BMP280
"""

from machine import I2C




def _sign(val, length):
    """
    Convert unsigned integer to signed integer
    """
    if val & (1 << (length - 1)):
        return val - (1 << length)
    return val


class BMP280:
    """
    Bosch Digital Pressure Sensor

    """
    device_address = 119
    REGISTER_DIGP1 = 142
    REGISTER_DIGP2 = 144
    REGISTER_DIGP3 = 146
    REGISTER_DIGP4 = 148
    REGISTER_DIGP5 = 150
    REGISTER_DIGP6 = 152
    REGISTER_DIGP7 = 154
    REGISTER_DIGP8 = 156
    REGISTER_DIGP9 = 158
    REGISTER_DIGT1 = 136
    REGISTER_DIGT2 = 138
    REGISTER_DIGT3 = 140
    REGISTER_PRESSURELSB = 248
    REGISTER_PRESSUREMSB = 247
    REGISTER_PRESSUREXLSB = 249
    REGISTER_TEMPLSB = 251
    REGISTER_TEMPMSB = 250
    REGISTER_TEMPXLSB = 252

    def __init__(self, i2c):
        # Initialize connection to peripheral
        self.i2c = i2c

    def get_digp1(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP1,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def get_digp2(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP2,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp3(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP3,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp4(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP4,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp5(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP5,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp6(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP6,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp7(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP7,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp8(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP8,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digp9(self):
        """
        Used for Pascals conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGP9,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digt1(self):
        """
        Used for Celcius conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGT1,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        return val

    def get_digt2(self):
        """
        Used for Celcius conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGT2,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_digt3(self):
        """
        Used for Celcius conversion

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_DIGT3,
            2,
            addrsize=16
        )
        val = 0
        val = val << 8 | byte_list[0]
        val = val << 8 | byte_list[1]
        # Unsigned > Signed integer
        val = _sign(val, 16)
        return val

    def get_pressurelsb(self):
        """
        Part 2 of Pressure

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_PRESSURELSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_pressuremsb(self):
        """
        Part 1 of Pressure

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_PRESSUREMSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_pressurexlsb(self):
        """
        Part 3 of Pressure

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_PRESSUREXLSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_templsb(self):
        """
        Part 2 of temperature

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_TEMPLSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_tempmsb(self):
        """
        Part 1 of temperature

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_TEMPMSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_tempxlsb(self):
        """
        Final part of temperature

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_TEMPXLSB,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val


    def pressure_ashpa(self):
        """
        Reads the atmospheric pressure

        """
        hpa = None # Variable declaration
        raw_comp1 = None # Variable declaration
        raw_comp2 = None # Variable declaration
        raw_comp3 = None # Variable declaration
        raw_pressure = None # Variable declaration
        raw_temperature = None # Variable declaration
        value_d_p1 = None # Variable declaration
        value_d_p2 = None # Variable declaration
        value_d_p3 = None # Variable declaration
        value_d_p4 = None # Variable declaration
        value_d_p5 = None # Variable declaration
        value_d_p6 = None # Variable declaration
        value_d_p7 = None # Variable declaration
        value_d_p8 = None # Variable declaration
        value_d_p9 = None # Variable declaration
        value_lsb = None # Variable declaration
        value_msb = None # Variable declaration
        value_xlsb = None # Variable declaration

        value_msb = self.get_pressuremsb()
        value_lsb = self.get_pressurelsb()
        value_xlsb = self.get_pressurexlsb()
        value_d_p1 = self.get_digp1()
        value_d_p2 = self.get_digp2()
        value_d_p3 = self.get_digp3()
        value_d_p4 = self.get_digp4()
        value_d_p5 = self.get_digp5()
        value_d_p6 = self.get_digp6()
        value_d_p7 = self.get_digp7()
        value_d_p8 = self.get_digp8()
        value_d_p9 = self.get_digp9()
        raw_temperature = self.temperature_ascelsius()
        raw_temperature = (raw_temperature*5120.0)
        raw_pressure = ((value_msb << 12)+(value_lsb << 4)+(value_xlsb >> 4))
        raw_comp1 = ((raw_temperature/2)-64000.0)
        raw_comp2 = ((raw_comp1*raw_comp1*value_d_p6)/32768.0)
        raw_comp2 = (raw_comp2+(raw_comp1*value_d_p5*2.0))
        raw_comp2 = ((raw_comp2/4.0)+(value_d_p4*65536.0))
        raw_comp3 = (value_d_p3*raw_comp1*raw_comp1)
        raw_comp1 = (((raw_comp3/524288.0)+(value_d_p2*raw_comp1))/524288.0)
        raw_comp1 = ((1.0+(raw_comp1/32768.0))*value_d_p1)
        hpa = (1048576.0-raw_pressure)
        hpa = ((hpa-(raw_comp2/4096.0))*(6250.0/raw_comp1))
        raw_comp1 = ((value_d_p9*hpa*hpa)/2147483648.0)
        raw_comp2 = ((hpa*value_d_p8)/32768.0)
        hpa = (hpa+((raw_comp1+raw_comp2+value_d_p7)/16.0))
        hpa = (hpa/100.0)
        return hpa
    def pressure_asraw(self):
        """
        Reads the atmospheric pressure

        """
        output = None # Variable declaration
        value_lsb = None # Variable declaration
        value_msb = None # Variable declaration
        value_xlsb = None # Variable declaration

        value_msb = self.get_pressuremsb()
        value_lsb = self.get_pressurelsb()
        value_xlsb = self.get_pressurexlsb()
        output = ((value_msb << 12)+(value_lsb << 4)+(value_xlsb >> 4))
        return output
    def temperature_ascelsius(self):
        """
        Reads the temperature

        """
        celsius = None # Variable declaration
        raw_comp1 = None # Variable declaration
        raw_comp2 = None # Variable declaration
        raw_comp3 = None # Variable declaration
        raw_temp = None # Variable declaration
        value_d_t1 = None # Variable declaration
        value_d_t2 = None # Variable declaration
        value_d_t3 = None # Variable declaration
        value_lsb = None # Variable declaration
        value_msb = None # Variable declaration
        value_xlsb = None # Variable declaration

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
    def temperature_asraw(self):
        """
        Reads the temperature

        """
        output = None # Variable declaration
        value_lsb = None # Variable declaration
        value_msb = None # Variable declaration
        value_xlsb = None # Variable declaration

        value_msb = self.get_tempmsb()
        value_lsb = self.get_templsb()
        value_xlsb = self.get_tempxlsb()
        output = ((value_msb << 12)+(value_lsb << 4)+(value_xlsb >> 4))
        return output
