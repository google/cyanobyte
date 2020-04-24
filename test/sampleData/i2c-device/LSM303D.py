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
from i2cdevice import Device, Register, BitField

I2C_ADDR = 29

ACCELEROMETERX_HIGH = Register('ACCELEROMETERX_HIGH', 169, read_only=True, bitwidth=8)
ACCELEROMETERX_LOW = Register('ACCELEROMETERX_LOW', 168, read_only=True, bitwidth=8)
ACCELEROMETERY_HIGH = Register('ACCELEROMETERY_HIGH', 171, read_only=True, bitwidth=8)
ACCELEROMETERY_LOW = Register('ACCELEROMETERY_LOW', 170, read_only=True, bitwidth=8)
ACCELEROMETERZ_HIGH = Register('ACCELEROMETERZ_HIGH', 173, read_only=True, bitwidth=8)
ACCELEROMETERZ_LOW = Register('ACCELEROMETERZ_LOW', 172, read_only=True, bitwidth=8)
MAGNETOMETERX_HIGH = Register('MAGNETOMETERX_HIGH', 137, read_only=True, bitwidth=8)
MAGNETOMETERX_LOW = Register('MAGNETOMETERX_LOW', 136, read_only=True, bitwidth=8)
MAGNETOMETERY_HIGH = Register('MAGNETOMETERY_HIGH', 139, read_only=True, bitwidth=8)
MAGNETOMETERY_LOW = Register('MAGNETOMETERY_LOW', 138, read_only=True, bitwidth=8)
MAGNETOMETERZ_HIGH = Register('MAGNETOMETERZ_HIGH', 141, read_only=True, bitwidth=8)
MAGNETOMETERZ_LOW = Register('MAGNETOMETERZ_LOW', 140, read_only=True, bitwidth=8)

lsm303d = Device(I2C_ADDR, registers=(
    ACCELEROMETERX_HIGH,
    ACCELEROMETERX_LOW,
    ACCELEROMETERY_HIGH,
    ACCELEROMETERY_LOW,
    ACCELEROMETERZ_HIGH,
    ACCELEROMETERZ_LOW,
    MAGNETOMETERX_HIGH,
    MAGNETOMETERX_LOW,
    MAGNETOMETERY_HIGH,
    MAGNETOMETERY_LOW,
    MAGNETOMETERZ_HIGH,
    MAGNETOMETERZ_LOW
))