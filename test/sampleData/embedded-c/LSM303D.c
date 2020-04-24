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




#include "LSM303D.h"
#define DEVICE_ADDRESS 29

#define REGISTER_ACCELEROMETERX_HIGH 169
#define REGISTER_ACCELEROMETERX_LOW 168
#define REGISTER_ACCELEROMETERY_HIGH 171
#define REGISTER_ACCELEROMETERY_LOW 170
#define REGISTER_ACCELEROMETERZ_HIGH 173
#define REGISTER_ACCELEROMETERZ_LOW 172
#define REGISTER_MAGNETOMETERX_HIGH 137
#define REGISTER_MAGNETOMETERX_LOW 136
#define REGISTER_MAGNETOMETERY_HIGH 139
#define REGISTER_MAGNETOMETERY_LOW 138
#define REGISTER_MAGNETOMETERZ_HIGH 141
#define REGISTER_MAGNETOMETERZ_LOW 140

// Provide an I2C connect function, return status
int lsm303d_init(int (*connect)(uint8_t)) {
    // Initialize bus
    if (connect(DEVICE_ADDRESS) != 0) {
        return -1;
    }
}

int lsm303d_readAccelerometerX_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERX_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readAccelerometerX_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERX_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readAccelerometerY_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERY_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readAccelerometerY_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERY_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readAccelerometerZ_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERZ_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readAccelerometerZ_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_ACCELEROMETERZ_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerX_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERX_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerX_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERX_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerY_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERY_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerY_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERY_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerZ_High(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERZ_HIGH, val, 1) != 0) {
        return -2;
    }
    return 0;
}

int lsm303d_readMagnetometerZ_Low(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (read(DEVICE_ADDRESS, REGISTER_MAGNETOMETERZ_LOW, val, 1) != 0) {
        return -2;
    }
    return 0;
}



void lsm303d_acceleration_asg(
    void* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    char accelerationScale; // Variable declaration
    short valueX; // Variable declaration
    short valueY; // Variable declaration
    short valueZ; // Variable declaration


    accelerationScale = 2
    lsm303d_acceleration_xplane(&valueX, read);
    lsm303d_acceleration_yplane(&valueY, read);
    lsm303d_acceleration_zplane(&valueZ, read);
    valueX = ((valueX/pow(2, 15))*accelerationScale);
    valueY = ((valueY/pow(2, 15))*accelerationScale);
    valueZ = ((valueZ/pow(2, 15))*accelerationScale);


    *val = [value_x, value_y, value_z];
}

void lsm303d_acceleration_xplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readAccelerometerX_Low(&lower, read);
    lsm303d_readAccelerometerX_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

void lsm303d_acceleration_yplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readAccelerometerY_Low(&lower, read);
    lsm303d_readAccelerometerY_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

void lsm303d_acceleration_zplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readAccelerometerZ_Low(&lower, read);
    lsm303d_readAccelerometerZ_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

void lsm303d_orientation_heading(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short dividend; // Variable declaration
    short heading; // Variable declaration
    short valueX; // Variable declaration
    short valueY; // Variable declaration


    lsm303d_orientation_xplane(&valueX, read);
    lsm303d_orientation_yplane(&valueY, read);
    dividend = (valueX/valueY);
    heading = atan(dividend);
    heading = ((int) heading%(int) (2*3.141592653589793));
    heading = ((heading/3.141592653589793)*180);


    *val = heading;
}

void lsm303d_orientation_xplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readMagnetometerX_Low(&lower, read);
    lsm303d_readMagnetometerX_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

void lsm303d_orientation_yplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readMagnetometerY_Low(&lower, read);
    lsm303d_readMagnetometerY_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

void lsm303d_orientation_zplane(
    short* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
) {
    short datum; // Variable declaration
    char lower; // Variable declaration
    char upper; // Variable declaration


    lsm303d_readMagnetometerZ_Low(&lower, read);
    lsm303d_readMagnetometerZ_High(&upper, read);
    datum = ((upper << 8)+lower);


    *val = datum;
}

