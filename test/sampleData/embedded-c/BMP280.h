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
* Auto-generated file for BMP280 v0.1.0.
* Generated from peripherals/BMP280.yaml using Cyanobyte Codegen v0.1.0
* Class for BMP280
* Bosch Digital Pressure Sensor

*/

#ifndef _BMP280_H_
#define _BMP280_H_



int bmp280_init(int (*connect)(uint8_t));
   
/**
  * Used for Pascals conversion

*/
int bmp280_readDigP1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP3(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP4(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP5(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP6(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP7(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP8(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Pascals conversion

*/
int bmp280_readDigP9(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Celcius conversion

*/
int bmp280_readDigT1(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Celcius conversion

*/
int bmp280_readDigT2(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Used for Celcius conversion

*/
int bmp280_readDigT3(
    uint16_t* val,
    int (*read)(uint8_t, uint8_t, uint16_t*, uint8_t)
);

/**
  * Part 2 of Pressure

*/
int bmp280_readPressureLsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Part 1 of Pressure

*/
int bmp280_readPressureMsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Part 3 of Pressure

*/
int bmp280_readPressureXlsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Part 2 of temperature

*/
int bmp280_readTempLsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Part 1 of temperature

*/
int bmp280_readTempMsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);

/**
  * Final part of temperature

*/
int bmp280_readTempXlsb(
    uint8_t* val,
    int (*read)(uint8_t, uint8_t, uint8_t*, uint8_t)
);


/**
 * Reads the atmospheric pressure

*/
void bmp280_pressure_ashpa(
    float* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Reads the atmospheric pressure

*/
void bmp280_pressure_asraw(
    long* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);

/**
 * Reads the temperature

*/
void bmp280_temperature_ascelsius(
    float* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);
/**
 * Reads the temperature

*/
void bmp280_temperature_asraw(
    long* val,
    int (*read)(uint8_t, uint8_t, int*, uint8_t)
);


#endif