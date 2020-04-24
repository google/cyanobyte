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
# Auto-generated file for LSM303D v0.1.0.
# Generated from peripherals/LSM303D.yaml using Cyanobyte Codegen v0.1.0
"""
Class for LSM303D
"""

import math
import ustruct
from machine import I2C






class LSM303D:
    """
    STMicroelectronics accelerometer and magnetometer

    """
    device_address = 29
    REGISTER_ACCELEROMETERX_HIGH = 169
    REGISTER_ACCELEROMETERX_LOW = 168
    REGISTER_ACCELEROMETERY_HIGH = 171
    REGISTER_ACCELEROMETERY_LOW = 170
    REGISTER_ACCELEROMETERZ_HIGH = 173
    REGISTER_ACCELEROMETERZ_LOW = 172
    REGISTER_MAGNETOMETERX_HIGH = 137
    REGISTER_MAGNETOMETERX_LOW = 136
    REGISTER_MAGNETOMETERY_HIGH = 139
    REGISTER_MAGNETOMETERY_LOW = 138
    REGISTER_MAGNETOMETERZ_HIGH = 141
    REGISTER_MAGNETOMETERZ_LOW = 140

    def __init__(self, i2c):
        # Initialize connection to peripheral
        self.i2c = i2c

    def get_accelerometerx_high(self):
        """
        Raw accelerometer data on X plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERX_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_accelerometerx_low(self):
        """
        Raw accelerometer data on X plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERX_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_accelerometery_high(self):
        """
        Raw accelerometer data on Y plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERY_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_accelerometery_low(self):
        """
        Raw accelerometer data on Y plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERY_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_accelerometerz_high(self):
        """
        Raw accelerometer data on Z plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERZ_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_accelerometerz_low(self):
        """
        Raw accelerometer data on Z plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_ACCELEROMETERZ_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometerx_high(self):
        """
        Raw magnetometer data on X plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERX_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometerx_low(self):
        """
        Raw magnetometer data on X plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERX_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometery_high(self):
        """
        Raw magnetometer data on Y plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERY_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometery_low(self):
        """
        Raw magnetometer data on Y plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERY_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometerz_high(self):
        """
        Raw magnetometer data on Z plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERZ_HIGH,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val

    def get_magnetometerz_low(self):
        """
        Raw magnetometer data on Z plane

        """
        byte_list = self.i2c.readfrom_mem(
            self.device_address,
            self.REGISTER_MAGNETOMETERZ_LOW,
            1,
            addrsize=8
        )
        val = 0
        val = val << 8 | byte_list[0]
        return val


    def acceleration_asg(self):
        """
        Measures the current acceleration

        """
        acceleration_scale = None # Variable declaration
        value_x = None # Variable declaration
        value_y = None # Variable declaration
        value_z = None # Variable declaration

        acceleration_scale = 2
        value_x = self.acceleration_xplane()
        value_y = self.acceleration_yplane()
        value_z = self.acceleration_zplane()
        value_x = ((value_x/math.pow(2, 15))*acceleration_scale)
        value_y = ((value_y/math.pow(2, 15))*acceleration_scale)
        value_z = ((value_z/math.pow(2, 15))*acceleration_scale)
        return [value_x, value_y, value_z]
    def acceleration_xplane(self):
        """
        Measures the current acceleration

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_accelerometerx_low()
        upper = self.get_accelerometerx_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
    def acceleration_yplane(self):
        """
        Measures the current acceleration

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_accelerometery_low()
        upper = self.get_accelerometery_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
    def acceleration_zplane(self):
        """
        Measures the current acceleration

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_accelerometerz_low()
        upper = self.get_accelerometerz_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
    def orientation_heading(self):
        """
        Reads the magnetic orientation

        """
        dividend = None # Variable declaration
        heading = None # Variable declaration
        value_x = None # Variable declaration
        value_y = None # Variable declaration

        value_x = self.orientation_xplane()
        value_y = self.orientation_yplane()
        dividend = (value_x/value_y)
        heading = math.atan(dividend)
        heading = (heading%(2*3.141592653589793))
        heading = ((heading/3.141592653589793)*180)
        return heading
    def orientation_xplane(self):
        """
        Reads the magnetic orientation

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_magnetometerx_low()
        upper = self.get_magnetometerx_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
    def orientation_yplane(self):
        """
        Reads the magnetic orientation

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_magnetometery_low()
        upper = self.get_magnetometery_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
    def orientation_zplane(self):
        """
        Reads the magnetic orientation

        """
        datum = None # Variable declaration
        lower = None # Variable declaration
        upper = None # Variable declaration

        lower = self.get_magnetometerz_low()
        upper = self.get_magnetometerz_high()
        datum = ((upper << 8)+lower)
        # Convert from a unsigned short to a signed short
        datum = ustruct.unpack("h", ustruct.pack("H", datum))[0]
        return datum
