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
from i2cdevice import Device, Register, BitField

I2C_ADDR = 119

CONTROL = Register('CONTROL', 244, read_only=False, bitwidth=8)
PRESSURECALAC1 = Register('PRESSURECALAC1', 170, read_only=True, bitwidth=16)
PRESSURECALAC2 = Register('PRESSURECALAC2', 172, read_only=True, bitwidth=16)
PRESSURECALVB1 = Register('PRESSURECALVB1', 182, read_only=True, bitwidth=16)
PRESSURECALVB2 = Register('PRESSURECALVB2', 184, read_only=True, bitwidth=16)
RESULT = Register('RESULT', 246, read_only=True, bitwidth=16)
TEMPCAL3 = Register('TEMPCAL3', 174, read_only=True, bitwidth=16)
TEMPCAL4 = Register('TEMPCAL4', 176, read_only=True, bitwidth=16)
TEMPCAL5 = Register('TEMPCAL5', 178, read_only=True, bitwidth=16)
TEMPCAL6 = Register('TEMPCAL6', 180, read_only=True, bitwidth=16)
TEMPCALMC = Register('TEMPCALMC', 188, read_only=True, bitwidth=16)
TEMPCALMD = Register('TEMPCALMD', 190, read_only=True, bitwidth=16)

bmp180 = Device(I2C_ADDR, registers=(
    CONTROL,
    PRESSURECALAC1,
    PRESSURECALAC2,
    PRESSURECALVB1,
    PRESSURECALVB2,
    RESULT,
    TEMPCAL3,
    TEMPCAL4,
    TEMPCAL5,
    TEMPCAL6,
    TEMPCALMC,
    TEMPCALMD
))