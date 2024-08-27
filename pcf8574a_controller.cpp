#include "pcf8574a_controller.h"
#include <fcntl.h>           // For open() function
#include <sys/ioctl.h>       // For ioctl() function
#include <linux/i2c-dev.h>   // For I2C-specific definitions
#include <unistd.h>          // For close(), read(), and write() functions
#include <iostream>          // For standard input/output operations

// Base I2C address for the PCF8574A devices
constexpr int BASE_ADDR = 0x38;

// Address offsets for each PCF8574A device
constexpr int ADDR_OFFSETS[] = {0, 1, 2, 3};

// I2C bus path, typically i2c-1 on Jetson Xavier NX
constexpr const char* I2C_BUS = "/dev/i2c-8";

// Constructor for the PCF8574AController class
PCF8574AController::PCF8574AController(int setup) : setup(setup) {
    // Calculate the specific I2C address for this PCF8574A based on the base address and the offset
    address = BASE_ADDR + ADDR_OFFSETS[setup];

    // Open the I2C bus for communication
    if ((i2cFile = open(I2C_BUS, O_RDWR)) < 0) {
        // If the bus fails to open, print an error message and return
        std::cerr << "Failed to open the I2C bus" << std::endl;
        return;
    }

    // Set the I2C address for the communication with the specific PCF8574A device
    // If fails, print an error message and close the file descriptor
    if (ioctl(i2cFile, I2C_SLAVE, address) < 0) {
        
        std::cerr << "Failed to acquire bus access and/or talk to the slave device" << std::endl;
        close(i2cFile);
        i2cFile = -1;
    }
}

// Destructor for the PCF8574AController class
// If valid, close the I2C connection
PCF8574AController::~PCF8574AController() {
    
    if (i2cFile >= 0) {
        close(i2cFile);
    }
}

// Initialize the PCF8574A device
void PCF8574AController::initialize() {
    // If invalid, do nothing
    if (i2cFile < 0) return;

    // Turn all LEDs off (PCF8574A pins high)
    char buffer[1] = {0xFF}; // 0xFF means all pins are high
    if (write(i2cFile, buffer, 1) != 1) {
        // If fails, print an error message
        std::cerr << "Failed to initialize the PCF8574A device" << std::endl;
    }
}

// Set the state of a specific LED
void PCF8574AController::setLedState(int led, int state) {
    // If the I2C file descriptor is invalid, do nothing
    if (i2cFile < 0) return;
    
    // Read the current state of the PCF8574A port
    char buffer[1];
    if (read(i2cFile, buffer, 1) != 1) {
        // If the read operation fails, print an error message
        std::cerr << "Failed to read from the I2C device" << std::endl;
        return;
    }

    // Modify the specific bit corresponding to the LED
    if (state) {
        // If state is 1, turn the LED on by clearing the corresponding bit
        // Note: LEDs connected to PCF8574A are typically active-low, so setting a bit to 0 turns the LED on
        buffer[0] &= ~(1 << led);
    } else {
        // If state is 0, turn the LED off by setting the corresponding bit to 1
        buffer[0] |= (1 << led);
    }

    // Write the updated state back
    if (write(i2cFile, buffer, 1) != 1) {
        // If write operation fails, print an error message
        std::cerr << "Failed to write to the I2C device" << std::endl;
    }
}

