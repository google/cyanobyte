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
# Auto-generated file for BMP180 v0.1.0.
# Generated from peripherals/BMP180.yaml using Cyanobyte Codegen v0.1.0
"""
Class for BMP180
"""

import math
import smbus




class BMP180:
    """
    Bosch Digital Temperature / Pressure Sensor

    """
    device_address = 119
    REGISTER_CONTROL = 244
    REGISTER_PRESSURECALAC1 = 170
    REGISTER_PRESSURECALAC2 = 172
    REGISTER_PRESSURECALVB1 = 182
    REGISTER_PRESSURECALVB2 = 184
    REGISTER_RESULT = 246
    REGISTER_TEMPCAL3 = 174
    REGISTER_TEMPCAL4 = 176
    REGISTER_TEMPCAL5 = 178
    REGISTER_TEMPCAL6 = 180
    REGISTER_TEMPCALMC = 188
    REGISTER_TEMPCALMD = 190

    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)


    def set_control(self, data):
        """
        Register stores what the measurement type should be

        """
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_CONTROL,
            data
        )
    def get_pressurecalac1(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_PRESSURECALAC1
        )
        return val

    def get_pressurecalac2(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_PRESSURECALAC2
        )
        return val

    def get_pressurecalvb1(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_PRESSURECALVB1
        )
        return val

    def get_pressurecalvb2(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_PRESSURECALVB2
        )
        return val

    def get_result(self):
        """
        Register stores most recent measurement result

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_RESULT
        )
        return val

    def get_tempcal3(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCAL3
        )
        return val

    def get_tempcal4(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCAL4
        )
        return val

    def get_tempcal5(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCAL5
        )
        return val

    def get_tempcal6(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCAL6
        )
        return val

    def get_tempcalmc(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCALMC
        )
        return val

    def get_tempcalmd(self):
        """
        For calibration

        """
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_TEMPCALMD
        )
        return val


    def temperature_ascelsius(self):
        """
        Reads the temperature

        """
        raw_comp = None # Variable declaration
        raw_mc = None # Variable declaration
        raw_md = None # Variable declaration
        temperature = None # Variable declaration
        var_ac5 = None # Variable declaration
        var_ac6 = None # Variable declaration
        var_c5 = None # Variable declaration
        var_mc = None # Variable declaration
        var_md = None # Variable declaration

        self.set_control(46)
        temperature = self.get_result()
        var_ac5 = self.get_tempcal5()
        var_ac6 = self.get_tempcal6()
        var_c5 = ((math.pow(2, -15)/160)*var_ac5)
        raw_comp = (var_c5*(temperature-var_ac6))
        raw_mc = self.get_tempcalmc()
        var_mc = ((math.pow(2, 11)/math.pow(160, 2))*raw_mc)
        raw_md = self.get_tempcalmd()
        var_md = (raw_md/160)
        temperature = (raw_comp+(var_mc/(raw_comp+var_md)))
        return temperature
