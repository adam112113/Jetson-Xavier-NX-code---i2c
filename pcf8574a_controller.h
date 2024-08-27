#ifndef PCF8574A_CONTROLLER_H
#define PCF8574A_CONTROLLER_H

class PCF8574AController {
public:
    PCF8574AController(int setup);
    ~PCF8574AController();

    void initialize();
    void setLedState(int led, int state);

private:
    int i2cFile;
    int setup;
    int address;
};

#endif // PCF8574A_CONTROLLER_H
