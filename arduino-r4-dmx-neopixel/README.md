# Arduino R4 DMX NeoPixel Project

This project implements a DMX slave device using the Arduino R4, which controls a NeoPixel light strip based on DMX input signals.

## Overview

The Arduino R4 acts as a DMX slave, receiving DMX data and using it to manipulate a NeoPixel light strip. The project is structured to separate concerns, with dedicated files for DMX communication and NeoPixel control.

## Project Structure

- **platformio.ini**: Configuration file for PlatformIO, specifying environment settings and libraries.
- **src/**: Contains the main application code.
  - **main.cpp**: Entry point of the application, initializes DMX and NeoPixel.
  - **config.h**: Configuration constants and settings.
  - **dmx_slave.cpp**: Implements DMX slave functionality.
  - **dmx_slave.h**: Header file for DMXSlave class.
  - **neopixel_driver.cpp**: Implements NeoPixel control functionality.
  - **neopixel_driver.h**: Header file for NeoPixelDriver class.
- **include/**: Contains additional header files.
  - **board_pins.h**: Defines pin assignments for the Arduino R4.
- **lib/**: Contains external libraries.
  - **DMXReceiver/**: Library for handling DMX communication.
  - **Adafruit_NeoPixel/**: Library for controlling NeoPixel light strips.
- **test/**: Contains unit tests for the project.
  - **unit_tests.cpp**: Unit tests for DMX and NeoPixel functionalities.
- **README.md**: Project documentation.

## Setup Instructions

1. **Clone the Repository**: 
   ```
   git clone <repository-url>
   cd arduino-r4-dmx-neopixel
   ```

2. **Install PlatformIO**: Follow the instructions on the [PlatformIO website](https://platformio.org/install) to install PlatformIO.

3. **Open the Project**: Open the project in your preferred IDE that supports PlatformIO.

4. **Build the Project**: Use the PlatformIO build command to compile the project.

5. **Upload to Arduino R4**: Connect your Arduino R4 and upload the code using PlatformIO.

## Usage

Once uploaded, the Arduino R4 will start receiving DMX signals. The NeoPixel light strip will respond to the DMX input, allowing for dynamic lighting control.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and contributions are welcome!

## License

This project is licensed under the MIT License. See the LICENSE file for more details.