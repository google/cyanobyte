//! Copyright (C) 2019 Google Inc.
//!
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//!
//! http://www.apache.org/licenses/LICENSE-2.0
//!
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!
//! This driver was built using [`embedded-hal`] traits.
//! [`embedded-hal`]: https://docs.rs/embedded-hal/~0.2
//!
//! Auto-generated file for Example v0.1.0.
//! Generated from peripherals/example.yaml using Cyanobyte Codegen v0.1.0
//!
//! Example
//!
//! Example of a package

#![deny(missing_docs)]
#![deny(warnings)]
#![no_std]

extern create embedded_hal as hal;

use hal::blocking::i2c::{Write, WriteRead};

enum Register {
    REGISTERA = 0,
    REGISTERB = 1,
    REGISTERC = 2,
    REGISTERD = 3,
}

pub enum DeviceAddress {
    I2C_ADDRESS_16 = 16,
    I2C_ADDRESS_32 = 32,
    I2C_ADDRESS_48 = 48,
}

pub enum FieldB {
    VAL_1 = 1 /// Value 1
    VAL_2 = 2 /// Value 2
    VAL_3 = 4 /// Value 3
    VAL_4 = 8 /// Value 4

/// Example driver
pub struct Example<I2C, u8> {
    i2c: I2C,
    address: u8
}

// TODO Endian, swap sign

impl<I2C, E> Example<I2C, u8>
where
    I2C: WriteRead<Error = E> + Write<Error = E>,
{
    /// Creates a new driver from an I2C peripheral
    pub fn new(i2c: I2C, addr: u8) -> Result<Self, E> {
        let mut example = Example { i2c, addr };
        example._lifecycle_begin()?;

        Ok(example)
    }

    // TODO u8 or other num types
    fn read_registera(&mut self) -> Result<u8, E> {
        let buffer: &mut [u8] = &mut buffer;
        self.i2c.write_read(
            self.address,
            &[register.address],
            buffer
        )?;
        Ok(buffer[0])
    }

    // TODO u8 or other num types
    fn read_registerb(&mut self) -> Result<u8, E> {
        let buffer: &mut [u8] = &mut buffer;
        self.i2c.write_read(
            self.address,
            &[register.address],
            buffer
        )?;
        Ok(buffer[0])
    }

    // TODO u8 or other num types
    fn read_registerc(&mut self) -> Result<u8, E> {
        let buffer: &mut [u8] = &mut buffer;
        self.i2c.write_read(
            self.address,
            &[register.address],
            buffer
        )?;
        Ok(buffer[0])
    }

    // TODO u8 or other num types
    fn read_registerd(&mut self) -> Result<u8, E> {
        let buffer: &mut [u8] = &mut buffer;
        self.i2c.write_read(
            self.address,
            &[register.address],
            buffer
        )?;
        Ok(buffer[0])
    }

}