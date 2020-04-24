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
* Auto-generated file for LSM303D v0.1.0.
* Generated from peripherals/LSM303D.yaml using Cyanobyte Codegen v0.1.0
* Class for LSM303D
* STMicroelectronics accelerometer and magnetometer

*/

#ifndef _LSM303D_H_
#define _LSM303D_H_

#include <math.h>


int lsm303d_init(int (*connect)(uint8_t));
   
/**
  * Raw accelerometer data on X plane

*/
int lsm303d_readAccelerometerX_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw accelerometer data on X plane

*/
int lsm303d_readAccelerometerX_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw accelerometer data on Y plane

*/
int lsm303d_readAccelerometerY_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw accelerometer data on Y plane

*/
int lsm303d_readAccelerometerY_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw accelerometer data on Z plane

*/
int lsm303d_readAccelerometerZ_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw accelerometer data on Z plane

*/
int lsm303d_readAccelerometerZ_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on X plane

*/
int lsm303d_readMagnetometerX_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on X plane

*/
int lsm303d_readMagnetometerX_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on Y plane

*/
int lsm303d_readMagnetometerY_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on Y plane

*/
int lsm303d_readMagnetometerY_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on Z plane

*/
int lsm303d_readMagnetometerZ_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Raw magnetometer data on Z plane

*/
int lsm303d_readMagnetometerZ_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);


/**
 * Measures the current acceleration

*/
void lsm303d_acceleration_asg(
    void* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Measures the current acceleration

*/
void lsm303d_acceleration_xplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Measures the current acceleration

*/
void lsm303d_acceleration_yplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Measures the current acceleration

*/
void lsm303d_acceleration_zplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * Reads the magnetic orientation

*/
void lsm303d_orientation_heading(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Reads the magnetic orientation

*/
void lsm303d_orientation_xplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Reads the magnetic orientation

*/
void lsm303d_orientation_yplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Reads the magnetic orientation

*/
void lsm303d_orientation_zplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);


#endif