/*
* Copyright (C) 2019 Google Inc.
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
* Auto-generated file for TCS3472 v0.1.0.
* Generated from peripherals/TCS3472.yaml using Cyanobyte Codegen v0.1.0
* Class for TCS3472
* Color Light-to-Digital Converter with IR Filter

*/

#ifndef _TCS3472_H_
#define _TCS3472_H_


/*
 * Valid values for Setup the device configuration

 */
enum init {
    INIT_POWER = 1, // Power
    INIT_RGBC = 2 // Color
};
typedef enum init init_t;

int tcs3472_init(int (*connect)(uint8_t));
   
/**
  * Blue light as an int. Divide by ambient light to get scaled number.

*/
int tcs3472_readblue(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * This is the ambient amount of detected light.

*/
int tcs3472_readclear(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Enable specific components of the peripheral

*/
int tcs3472_readenable(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
 * Enable specific components of the peripheral

 */
int tcs3472_writeenable(
    uint8_t* data,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t),
    int (*write)(uint8_t, uint8_t, uint8_t*, uint8_t)
);
/**
  * Green light as an int. Divide by ambient light to get scaled number.

*/
int tcs3472_readgreen(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Red light as an int. Divide by ambient light to get scaled number.

*/
int tcs3472_readred(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
 * Enable RGBC and Power

 */
int tcs3472_get_init(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Enable RGBC and Power

 */
int tcs3472_set_init(
    uint8_t* data,
    int (*read)(uint8_t, uint8_t, int*, uint8_t),
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * Enables features on device

*/
void tcs3472__lifecycle_begin(
    int (*write)(uint8_t, uint8_t, int*, uint8_t)
);


#endif