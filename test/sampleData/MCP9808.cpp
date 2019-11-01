/*
*
* Auto-generated file for MCP9808 v0.1.0.
* Generated from peripherals/MCP9808.yaml using Cyanobyte Codegen v0.1.0
* Class for MCP9808
* This is a test description

*/




#include "MCP9808.h"
#define DEVICE_ADDRESS 24

#define REGISTER_CONFIGURATION 1

MCP9808::MCP9808(TwoWire& wire) :
    _wire(&wire)
{
}

void MCP9808::begin() {
    _wire->begin();
}

void MCP9808::end() {
    _wire->end();
}

uint16_t MCP9808::readconfiguration() {
    uint8_t datum;
    uint16_t value;
    _wire->beginTransmission(DEVICE_ADDRESS);
    _wire->write(REGISTER_CONFIGURATION);
    if (_wire->endTransmission(false) != 0) {
        return -1;
    }

    if (_wire->requestFrom(DEVICE_ADDRESS, 16) != 16) {
        return 0;
    }

    datum = wire->read();
    value = value << 8 | datum;
    datum = wire->read();
    value = value << 8 | datum;

    return value;
}

int MCP9808::writeconfiguration(uint16_t data) {
    _wire->beginTransmission(DEVICE_ADDRESS);
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIGURATION };
    uint8_t buffer[1] = (data >> 8) & 0xFF;
    uint8_t buffer[2] = (data >> 0) & 0xFF;
    _wire->write(buffer, 3);
    if (_wire->endTransmission() != 0) {
        return 0;
    }
    return 1;
}


uint16_t MCP9808::getlimitHysteresis() {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    uint8_t val = readconfiguration()
    // Mask register value
    val = val & 0b0000001100000000
    // Bitshift value
    val = val >> 9
    return val
}

uint16_t MCP9808::getshutdownMode() {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    uint8_t val = readconfiguration()
    // Mask register value
    val = val & 0b0000000010000000
    // Bitshift value
    val = val >> 8
    return val
}

