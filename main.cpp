#include "pcf8574a_controller.h"
#include <iostream>
#include <thread>
#include <chrono>

//void turnOnLed(PCF8574AController& controller, int numLed) {
//   for (int i = 0; i < numLeds; ++i) {
//        controller.setLedState(numLED, 0);  // Turn on LED
//        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
//    }
//}

// Create an instance of the controller for each setup
    PCF8574AController controller1(0);
    PCF8574AController controller2(1);
    PCF8574AController controller3(2);
    PCF8574AController controller4(3);

 // Initialize all controllers
// controller1.initialize();
   // controller2.initialize();
    //controller3.initialize();
    //controller4.initialize();

void turnOnLED(PCF8574AController& controller, int ledIndex, int state) {
    // The ledIndex parameter corresponds to the pin on the PCF8574A (0-3 for each controller)
    // The state parameter is either 1 (turn LED on) or 0 (turn LED off)

    // Call the setLedState method on the controller object
    controller.setLedState(ledIndex, state);
}


void input_percentage(int percentage) {
    int totalLEDs = 16;                       // Total number of LEDs
    int ledsOn = (percentage * totalLEDs) / 100; // Number of LEDs that should be on

    // Loop through all LEDs and turn them on based on the calculated number
    for (int i = 0; i < totalLEDs; i++) {
        int ledState = (i < ledsOn) ? 1 : 0; // Turn on LEDs if within the range, else turn off
        //int ledState;
        //if (i < ledsOn) {
        //ledState = 1;  // Turn on the LED
        //} else {
        //ledState = 0;  // Turn off the LED
        //}

        if (i < 4) {
            // First LED strip (controller1)
            turnOnLED(controller1, i, ledState);
        } else if (i < 8) {
            // Second LED strip (controller2)
            turnOnLED(controller2, i - 4, ledState);
        } else if (i < 12) {
            // Third LED strip (controller3)
            turnOnLED(controller3, i - 8, ledState);
        } else if (i < 16) {
            // Fourth LED strip (controller4)
            turnOnLED(controller4, i - 12, ledState);
        }
    }
}


int main() {
    
    

   

    for(int i = 0; i <= 100; i++)
    {
        input_percentage(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    return 0;
}
