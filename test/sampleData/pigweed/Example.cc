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
* Auto-generated file for Example v0.1.0.
* Generated from peripherals/example.yaml using Cyanobyte Codegen v0.0.2
* Class for Example
* Example of a package

*/




#include "Example.h"


#define REGISTER_REGISTERA 0
#define REGISTER_REGISTERB 1
#define REGISTER_REGISTERC 2
#define REGISTER_REGISTERD 3

Example::Example(pw::i2c::Initiator& initiator, pw::i2c::Address address): RegisterDevice(initiator, address),
          std::endian::big,
        pw::i2c::RegisterAddressSize::k1Byte)
    {
        DEVICE_ADDRESS ( address )
    }

pw::Result<uint8_t> Example::readRegisterA() {
  // Hard-coded timeout of 1s.
  return ReadRegister8(REGISTER_REGISTERA, std::chrono::seconds(1));
}

pw::Status Example::writeRegisterA(uint8_t data) {
  // Hard-coded timeout of 1s.
  return WriteRegister8(REGISTER_REGISTERA, data, std::chrono::seconds(1));
}

pw::Result<uint16_t> Example::readRegisterB() {
  // Hard-coded timeout of 1s.
  return ReadRegister16(REGISTER_REGISTERB, std::chrono::seconds(1));
}

pw::Status Example::writeRegisterB(uint16_t data) {
  // Hard-coded timeout of 1s.
  return WriteRegister16(REGISTER_REGISTERB, data, std::chrono::seconds(1));
}

pw::Result<uint32_t> Example::readRegisterC() {
  // Hard-coded timeout of 1s.
  return ReadRegister32(REGISTER_REGISTERC, std::chrono::seconds(1));
}

pw::Status Example::writeRegisterC(uint32_t data) {
  // Hard-coded timeout of 1s.
  return WriteRegister32(REGISTER_REGISTERC, data, std::chrono::seconds(1));
}

pw::Result<uint8_t> Example::readRegisterD() {
  // Hard-coded timeout of 1s.
  return ReadRegister8(REGISTER_REGISTERD, std::chrono::seconds(1));
}

pw::Status Example::writeRegisterD() {
  // Hard-coded timeout of 1s.
  return WriteRegister8(REGISTER_REGISTERD, 0 /* No data */, std::chrono::seconds(1));
}


pw::Result<uint8_t> Example::getFieldA() {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    Result<uint8_t> res = readRegisterA();
    uint8_t val = res.value();
    // Mask register value
    val = val & 0b0000000011110000;
    // Bitshift value
    val = val >> 4;
    // Rewrap in a Result
    Result<uint8_t> result = new Result(val);
    return result;
}

pw::Status Example::setFieldB(uint8_t data) {
    // Bitshift value
    data = data << 2;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    Result<uint8_t> res = readRegisterA();
    uint8_t register_data = res.value()
    register_data = register_data | data;
    return writeRegisterA(register_data);
}
pw::Result<uint8_t> Example::getFieldC() {
    // Read register data
    // '#/registers/RegisterA' > 'RegisterA'
    Result<uint8_t> res = readRegisterA();
    uint8_t val = res.value();
    // Mask register value
    val = val & 0b0000000000000010;
    // Bitshift value
    val = val >> 1;
    // Rewrap in a Result
    Result<uint8_t> result = new Result(val);
    return result;
}

pw::Status Example::setFieldC(uint8_t data) {
    // Bitshift value
    data = data << 1;
    // Read current register data
    // '#/registers/RegisterA' > 'RegisterA'
    Result<uint8_t> res = readRegisterA();
    uint8_t register_data = res.value()
    register_data = register_data | data;
    return writeRegisterA(register_data);
}

char Example::_lifecycleBegin() {
    char output; // Variable declaration


    output = 1;
    writeRegisterA(output);


    return output;
}

char Example::_lifecycleEnd() {
    char output; // Variable declaration


    output = 1;
    writeRegisterA(output);


    return output;
}

void Example::ReturnArray(short * returnArray) {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


    returnArray[0] = summation;
    returnArray[1] = summation;
}

short Example::ReturnNumber() {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


    return summation;
}

void Example::ReturnVoid() {
    short summation; // Variable declaration


    summation = (1024+1024);
    writeRegisterA(summation);


}

