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
# Auto-generated file for ADS1015 v0.1.0.
# Generated from peripherals/ADS1015.yaml using Cyanobyte Codegen v0.1.0
from i2cdevice import Device, Register, BitField

I2C_ADDR = 73

CONFIG = Register('CONFIG', 1, fields=(
    BitField('Channel', 0b0111000000000000, bitwidth=3, values_in=_byte_swap, values_out=_byte_swap, values_map={
        CHANNEL_1: 0,
        CHANNEL_2: 1,
        CHANNEL_3: 2,
        CHANNEL_4: 3
    }),
    BitField('DeviceOperatingMode', 0b0000000100000000, bitwidth=1, values_in=_byte_swap, values_out=_byte_swap, values_map={
        CONTINUOUS_CONVERSION: 0,
        SINGLE_SHOT: 1
    }),
    BitField('ProgrammableGain', 0b0000111000000000, bitwidth=3, values_in=_byte_swap, values_out=_byte_swap, values_map={
        PGA0_256: 5,
        PGA0_512: 4,
        PGA1_024V: 3,
        PGA2_048V: 2,
        PGA4_096V: 1,
        PGA6_144V: 0
    }),
    BitField('SampleRate', 0b0000000011100000, bitwidth=3, values_in=_byte_swap, values_out=_byte_swap, values_map={
        HZ128: 0,
        HZ1600: 4,
        HZ2400: 5,
        HZ250: 1,
        HZ3300: 6,
        HZ490: 2,
        HZ920: 3
    })
), read_only=False, bitwidth=16)
CONVERSION = Register('CONVERSION', 0, read_only=True, bitwidth=16)

ads1015 = Device(I2C_ADDR, registers=(
    CONFIG,
    CONVERSION
))