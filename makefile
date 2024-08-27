# Makefile for the PCF8574A LED Controller project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Libraries to link
LIBS = -li2c

# Source files
SRCS = main.cpp pcf8574a_controller.cpp

# Header files
HEADERS = pcf8574a_controller.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = led_controller

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
