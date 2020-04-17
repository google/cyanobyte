/*
* Copyright (C) 2020 Google Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Auto-generated file for BH1750FVI v0.1.0.
* Generated from peripherals/BH1750FVI.yaml using Cyanobyte Codegen v0.1.0
* Class for BH1750FVI
* Rohm Light Sensor

*/

#ifndef _BH1750FVI_H_
#define _BH1750FVI_H_


enum deviceAddress {
    I2C_ADDRESS_35 = 35,
    I2C_ADDRESS_92 = 92
};
typedef enum deviceAddress deviceAddress_t;

int bh1750fvi_init(deviceAddress_t address, int (*connect)(uint8_t));
   

/**
 * Start measurement at 0.5lx resolution. Typically 120ms.

 */
int bh1750fvi_writeContinuousHRes2Mode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Start measurement at 1lx resolution. Typically 120ms.

 */
int bh1750fvi_writeContinuousHResMode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Start measurement at 4lx resolution. Typically 16ms.

 */
int bh1750fvi_writeContinuouslyLResMode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Start measurement at 0.5lx resolution. Typically 120ms.
 * Power Down after measurement.

 */
int bh1750fvi_writeOnceHRes2Mode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Start measurement at 1lx resolution. Typically 120ms.
 * Power Down after measurement.

 */
int bh1750fvi_writeOnceHResMode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Start measurement at 4lx resolution. Typically 16ms.
 * Power Down after measurement.

 */
int bh1750fvi_writeOnceLResMode(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * No active state

 */
int bh1750fvi_writePowerDown(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Waiting for measurement command

 */
int bh1750fvi_writePowerOn(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Reset data register value. Not accepted in Power Down mode.

 */
int bh1750fvi_writeReset(
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Sends a POWER ON cmd to device

*/
void bh1750fvi__lifecycle_begin(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * Things you can do to device

*/
void bh1750fvi_command_powerdown(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Things you can do to device

*/
void bh1750fvi_command_reset(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * Read light intensity from device

*/
void bh1750fvi_read_lightintensity(
    uint16_t* val,

);


#endif