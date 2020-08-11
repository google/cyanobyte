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
# Auto-generated file for MCP9808 v0.1.0.
# Generated from peripherals/MCP9808.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR_24 = 24
I2C_ADDR_25 = 25
I2C_ADDR_26 = 26
I2C_ADDR_27 = 27
I2C_ADDR_28 = 28
I2C_ADDR_29 = 29
I2C_ADDR_30 = 30
I2C_ADDR_31 = 31
I2C_ADDR = [I2C_ADDR_24, I2C_ADDR_25, I2C_ADDR_26, I2C_ADDR_27, I2C_ADDR_28, I2C_ADDR_29, I2C_ADDR_30, I2C_ADDR_31]

CONFIGURATION = Register('CONFIGURATION', 1, fields=(
    BitField('limitHysteresis', 0b0000011000000000, bitwidth=2, values_map={
        Temp_0C: 0,
        Temp_1C5: 1,
        Temp_3C: 2,
        Temp_6C: 3
    }),
    BitField('shutdownMode', 0b0000000100000000, bitwidth=1, values_map={
        continousConversion: 0,
        shutdown: 1
    })
), read_only=False, bitwidth=16)

mcp9808 = Device(I2C_ADDR, registers=(
    CONFIGURATION
))