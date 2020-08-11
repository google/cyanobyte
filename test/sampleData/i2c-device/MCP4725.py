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
# Auto-generated file for MCP4725 v0.1.0.
# Generated from peripherals/MCP4725.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR = 98

EEPROM = Register('EEPROM', 96, fields=(
    BitField('digitalOut', 0b0001111111111111, bitwidth=13, values_in=_byte_swap, values_out=_byte_swap, values_map={
        GND: 0,
        VCC: 4095
    })
), read_only=False, bitwidth=12)
VOUT = Register('VOUT', 64, read_only=False, bitwidth=12)

mcp4725 = Device(I2C_ADDR, registers=(
    EEPROM,
    VOUT
))