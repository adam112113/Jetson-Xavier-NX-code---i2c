#include "pcf8574a_controller.h"
#include <iostream>
#include <thread>
#include <chrono>

void turnOnLedsSequentially(PCF8574AController& controller, int numLeds) {
    for (int i = 0; i < numLeds; ++i) {
        controller.setLedState(i, 0);  // Turn on LED
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void turnOffLedsSequentially(PCF8574AController& controller, int numLeds) {
    for (int i = 0; i < numLeds; ++i) {
        controller.setLedState(i, 1);  // Turn off LED
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    const int numLeds = 4;

    // Create an instance of the controller for each setup
    PCF8574AController controller1(0);
    PCF8574AController controller2(1);
    PCF8574AController controller3(2);
    PCF8574AController controller4(3);

    // Initialize all controllers
    controller1.initialize();
    controller2.initialize();
    controller3.initialize();
    controller4.initialize();

    // Turn on LEDs sequentially for each controller
    turnOnLedsSequentially(controller1, numLeds);
    turnOnLedsSequentially(controller2, numLeds);
    turnOnLedsSequentially(controller3, numLeds);
    turnOnLedsSequentially(controller4, numLeds);

    // Turn off LEDs sequentially for each controller
    turnOffLedsSequentially(controller4, numLeds);
    turnOffLedsSequentially(controller3, numLeds);
    turnOffLedsSequentially(controller2, numLeds);
    turnOffLedsSequentially(controller1, numLeds);

    return 0;
}
