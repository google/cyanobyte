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
# Auto-generated file for TCS3472 v0.1.0.
# Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR = 41

BLUE = Register('BLUE', 186, read_only=True, bitwidth=16)
CLEAR = Register('CLEAR', 180, read_only=True, bitwidth=16)
ENABLE = Register('ENABLE', 128, fields=(
    BitField('init', 0b0000000011111111, bitwidth=8, values_map={
        Power: 1,
        RGBC: 2
    })
), read_only=False, bitwidth=8)
GREEN = Register('GREEN', 184, read_only=True, bitwidth=16)
RED = Register('RED', 182, read_only=True, bitwidth=16)

tcs3472 = Device(I2C_ADDR, registers=(
    BLUE,
    CLEAR,
    ENABLE,
    GREEN,
    RED
))