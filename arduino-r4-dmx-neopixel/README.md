# Arduino R4 DMX NeoPixel Project

This project implements a DMX slave device using the Arduino R4, which controls a NeoPixel light strip based on DMX input signals.

In current iteration this project takes a serial monitor input rather than a DMX input, and only output to the matrix display onboard. This will be updated when my new hardware arrives.

## Overview

The Arduino R4 acts as a DMX slave, receiving DMX data and using it to manipulate a NeoPixel light strip. The project is structured to separate concerns, with dedicated files for DMX communication and NeoPixel control.

## Project Structure

- **platformio.ini**: Configuration file for PlatformIO, specifying environment settings and libraries.
- **src/**: Contains the main application code.
  - **main.cpp**: Entry point of the application, initializes DMX and NeoPixel.
  - **config.h**: Configuration constants and settings.
- **include/**: Contains additional header files.
  - **board_pins.h**: Defines pin assignments for the Arduino R4.
- **lib/**: Contains external libraries.
  - **DMXReceiver/**: Library for handling DMX communication.
  - **Adafruit_NeoPixel/**: Library for controlling NeoPixel light strips.
  - **Arduino_LED_Matrix/**: Library for controlling the Matrix display onboard the R4, included in the R4 libraries.
- **README.md**: Project documentation.

## Environment

1. This project uses platformio, the vscode extension, to install software to the arduino. The `arduino-r4-dmx-neopixel` folder must be open as the root folder in vscode for the project to compile and install.