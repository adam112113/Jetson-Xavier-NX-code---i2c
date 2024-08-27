FIRST: install all the nessecary tools
sudo apt-get install libi2c-dev i2c-tools


COMPILE: without MakeFile
g++ -o led_controller main.cpp pcf8574a_controller.cpp -li2c
sudo ./led_controller

COMPILE: with MakeFile
make

sudo ./led_controller

make clean
