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
# Auto-generated file for BH1750FVI v0.1.0.
# Generated from peripherals/BH1750FVI.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR_35 = 35
I2C_ADDR_92 = 92
I2C_ADDR = [I2C_ADDR_35, I2C_ADDR_92]

CONTINUOUSHRES2MODE = Register('CONTINUOUSHRES2MODE', 17, read_only=False, bitwidth=0)
CONTINUOUSHRESMODE = Register('CONTINUOUSHRESMODE', 16, read_only=False, bitwidth=0)
CONTINUOUSLYLRESMODE = Register('CONTINUOUSLYLRESMODE', 19, read_only=False, bitwidth=0)
ONCEHRES2MODE = Register('ONCEHRES2MODE', 33, read_only=False, bitwidth=0)
ONCEHRESMODE = Register('ONCEHRESMODE', 32, read_only=False, bitwidth=0)
ONCELRESMODE = Register('ONCELRESMODE', 35, read_only=False, bitwidth=0)
POWERDOWN = Register('POWERDOWN', 0, read_only=False, bitwidth=0)
POWERON = Register('POWERON', 1, read_only=False, bitwidth=0)
RESET = Register('RESET', 7, read_only=False, bitwidth=0)

bh1750fvi = Device(I2C_ADDR, registers=(
    CONTINUOUSHRES2MODE,
    CONTINUOUSHRESMODE,
    CONTINUOUSLYLRESMODE,
    ONCEHRES2MODE,
    ONCEHRESMODE,
    ONCELRESMODE,
    POWERDOWN,
    POWERON,
    RESET
))