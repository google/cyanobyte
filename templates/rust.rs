{% import 'macros.jinja2' as utils %}
{{ utils.pad_string('//! ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
//!
//! This driver was built using [`embedded-hal`] traits.
//! [`embedded-hal`]: https://docs.rs/embedded-hal/~0.2
//!
//! Auto-generated file for {{ info.title }} v{{ info.version }}.
//! Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
//!
//! {{info.title}}
//!
//! {{info.description}}

#![deny(missing_docs)]
#![deny(warnings)]
#![no_std]

extern create embedded_hal as hal;

use hal::blocking::i2c::{Write, WriteRead};

enum Register {
    {% for key,register in registers|dictsort %}
    {{key.upper()}} = {{register.address}},
    {% endfor %}
}

{% if i2c.address is iterable and i2c.address is not string %}
pub enum DeviceAddress {
    {% for address in i2c.address %}
    I2C_ADDRESS_{{address}} = {{address}},
    {% endfor %}
}
{% endif %}

{# Create enums for fields #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if field.enum %}
{# Create enum class #}
pub enum {{key[0].upper()}}{{key[1:]}} {
    {% for ekey,enum in field.enum|dictsort %}
    {{ekey.upper()}} = {{enum.value}} /// {{enum.title}}
    {% endfor %}
{% endif %}
{% endfor %}
{% endif %}

/// {{info.title}} driver
pub struct {{info.title}}<I2C, u8> {
    i2c: I2C,
    address: u8
}

// TODO Endian, swap sign

impl<I2C, E> {{info.title}}<I2C, u8>
where
    I2C: WriteRead<Error = E> + Write<Error = E>,
{
    /// Creates a new driver from an I2C peripheral
    {% if i2c.address is iterable and i2c.address is not string %}
    pub fn new(i2c: I2C, addr: u8) -> Result<Self, E> {
        let mut {{info.title.lower()}} = {{info.title}} { i2c, addr };
    {% else %}
    pub fn new(i2c: I2C) -> Result<Self, E> {
        let mut {{info.title.lower()}} = {{info.title}} { i2c, {{i2c.address}} };
    {% endif %}
        {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
        {{info.title.lower()}}._lifecycle_begin()?;
        {% endif %}

        Ok({{info.title.lower()}})
    }

    {% for key,register in registers|dictsort %}
    {% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
    // TODO u8 or other num types
    fn read_{{key.lower() | camel_to_snake }}(&mut self) -> Result<u8, E> {
        let buffer: &mut [u8] = &mut buffer;
        self.i2c.write_read(
            self.address,
            &[register.address],
            buffer
        )?;
        Ok(buffer[0])
    }
    {% endif %}

    {% endfor %}
}
