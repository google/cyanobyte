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
# Auto-generated file for Example v0.1.0.
# Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR_16 = 16
I2C_ADDR_32 = 32
I2C_ADDR_48 = 48
I2C_ADDR = [I2C_ADDR_16, I2C_ADDR_32, I2C_ADDR_48]

REGISTERA = Register('REGISTERA', 0, fields=(
    BitField('FieldA', 0b0000000011110000, bitwidth=4),
    BitField('FieldB', 0b0000000000001100, bitwidth=2, values_map={
        VAL_1: 1,
        VAL_2: 2,
        VAL_3: 4,
        VAL_4: 8
    }),
    BitField('FieldC', 0b0000000000000010, bitwidth=1),
    BitField('FieldD', 0b0000000000000001, bitwidth=1)
), read_only=False, bitwidth=8)
REGISTERB = Register('REGISTERB', 1, read_only=False, bitwidth=16)
REGISTERC = Register('REGISTERC', 2, read_only=False, bitwidth=32)
REGISTERD = Register('REGISTERD', 3, read_only=False, bitwidth=0)

example = Device(I2C_ADDR, registers=(
    REGISTERA,
    REGISTERB,
    REGISTERC,
    REGISTERD
))