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

static int i2c_bus = 0; // Pointer to bus

// Provide `bus_name` based on application specifics.
// For example, you may pass in bus name "/dev/i2c-1"
int mcp9808_init(char* bus_name) {
    // Initialize bus
    if (k_i2c_init(&bus_name, &i2c_bus) != I2C_OK) {
        return -1;
    }
}

void mcp9808_terminate() {
    k_i2c_terminate(&i2c_bus);
}

int mcp9808_readconfiguration(uint16_t* val) {
    if (val == NULL) {
        return -1; // Need to provide a valid value pointer
    }
    if (k_i2c_read(i2c_bus, DEVICE_ADDRESS, val, 2) != I2C_OK) {
        return -2;
    }
    return 0;
}

int mcp9808_writeconfiguration(uint16_t* data) {
    // Put our data into uint8_t buffer
    uint8_t buffer[3] = { (uint8_t) REGISTER_CONFIGURATION };
    uint8_t buffer[1] = (data >> 16) & 0xFF;
    uint8_t buffer[2] = (data >> 8) & 0xFF;
    // First write our register address
    if (k_i2c_write(i2c_bus, DEVICE_ADDRESS, buffer, 3) != I2C_OK) {
        return -1;
    }
    return 0;
}


int mcp9808_get_limithysteresis(uint16_t* val) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000001100000000;
    // Bitshift value
    val = val >> 9;
    return 0;
}
int mcp9808_get_shutdownmode(uint16_t* val) {
    // Read register data
    // '#/registers/configuration' > 'configuration'
    int result = mcp9808_readconfiguration(val);
    if (result != 0) {
        return result;
    }
    // Mask register value
    val = val & 0b0000000010000000;
    // Bitshift value
    val = val >> 8;
    return 0;
}

