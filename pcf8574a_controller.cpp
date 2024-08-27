#include "pcf8574a_controller.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <iostream>

constexpr int BASE_ADDR = 0x38;
constexpr int ADDR_OFFSETS[] = {0, 1, 2, 3};
constexpr const char* I2C_BUS = "/dev/i2c-1";  // Use the appropriate I2C bus, typically i2c-1 on Jetson

PCF8574AController::PCF8574AController(int setup) : setup(setup) {
    // Calculate the address
    address = BASE_ADDR + ADDR_OFFSETS[setup];

    // Open the I2C bus
    if ((i2cFile = open(I2C_BUS, O_RDWR)) < 0) {
        std::cerr << "Failed to open the I2C bus" << std::endl;
        return;
    }

    // Set the I2C address
    if (ioctl(i2cFile, I2C_SLAVE, address) < 0) {
        std::cerr << "Failed to acquire bus access and/or talk to the slave device" << std::endl;
        close(i2cFile);
        i2cFile = -1;
    }
}

PCF8574AController::~PCF8574AController() {
    // Close the I2C connection
    if (i2cFile >= 0) {
        close(i2cFile);
    }
}

void PCF8574AController::initialize() {
    if (i2cFile < 0) return;
    // Optionally, you can set an initial state for the LEDs here
    // For example, turn all LEDs off:
    char buffer[1] = {0xFF};
    if (write(i2cFile, buffer, 1) != 1) {
        std::cerr << "Failed to initialize the PCF8574A device" << std::endl;
    }
}

void PCF8574AController::setLedState(int led, int state) {
    if (i2cFile < 0) return;
    
    // Read the current state of the PCF8574A port
    char buffer[1];
    if (read(i2cFile, buffer, 1) != 1) {
        std::cerr << "Failed to read from the I2C device" << std::endl;
        return;
    }

    // Modify the specific bit for the LED
    if (state) {
        // Set the specific LED bit to 1 (turn off the LED)
        buffer[0] &= ~(1 << led);
    } else {
        // Set the specific LED bit to 0 (turn on the LED)
        buffer[0] |= (1 << led);
    }

    // Write the new state back to the PCF8574A port
    if (write(i2cFile, buffer, 1) != 1) {
        std::cerr << "Failed to write to the I2C device" << std::endl;
    }
}
