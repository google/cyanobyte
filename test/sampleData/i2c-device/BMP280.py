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
from i2cdevice import Device, Register, BitField

I2C_ADDR = 119

DIGP1 = Register('DIGP1', 142, read_only=True, bitwidth=16)
DIGP2 = Register('DIGP2', 144, read_only=True, bitwidth=16)
DIGP3 = Register('DIGP3', 146, read_only=True, bitwidth=16)
DIGP4 = Register('DIGP4', 148, read_only=True, bitwidth=16)
DIGP5 = Register('DIGP5', 150, read_only=True, bitwidth=16)
DIGP6 = Register('DIGP6', 152, read_only=True, bitwidth=16)
DIGP7 = Register('DIGP7', 154, read_only=True, bitwidth=16)
DIGP8 = Register('DIGP8', 156, read_only=True, bitwidth=16)
DIGP9 = Register('DIGP9', 158, read_only=True, bitwidth=16)
DIGT1 = Register('DIGT1', 136, read_only=True, bitwidth=16)
DIGT2 = Register('DIGT2', 138, read_only=True, bitwidth=16)
DIGT3 = Register('DIGT3', 140, read_only=True, bitwidth=16)
PRESSURELSB = Register('PRESSURELSB', 248, read_only=True, bitwidth=8)
PRESSUREMSB = Register('PRESSUREMSB', 247, read_only=True, bitwidth=8)
PRESSUREXLSB = Register('PRESSUREXLSB', 249, read_only=True, bitwidth=8)
TEMPLSB = Register('TEMPLSB', 251, read_only=True, bitwidth=8)
TEMPMSB = Register('TEMPMSB', 250, read_only=True, bitwidth=8)
TEMPXLSB = Register('TEMPXLSB', 252, read_only=True, bitwidth=8)

bmp280 = Device(I2C_ADDR, registers=(
    DIGP1,
    DIGP2,
    DIGP3,
    DIGP4,
    DIGP5,
    DIGP6,
    DIGP7,
    DIGP8,
    DIGP9,
    DIGT1,
    DIGT2,
    DIGT3,
    PRESSURELSB,
    PRESSUREMSB,
    PRESSUREXLSB,
    TEMPLSB,
    TEMPMSB,
    TEMPXLSB
))