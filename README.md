# Smart LED Control with ESP32 and Home Assistant

## Project Description

This project enables smart control of LEDs from CADA brick sets using an ESP32 and a light sensor. 
The program can be:

1. Built and uploaded to the ESP32 as a standalone program that monitors light intensity and controls the LEDs accordingly.
2. Integrated with Home Assistant by uploading the `BrickDimmer.yaml` configuration via ESPHome. This setup creates two entities in Home Assistant:
   - A switch to control the LEDs.
   - A light sensor to monitor ambient light levels.

## Features

- Automatic LED control based on ambient light intensity.
- Seamless integration with Home Assistant for manual and automated control.

## Required Hardware

- **ESP32**
- **Light Sensor** (e.g., BH1750)
- **MOSFET**
- **USB-A Module** (for use with CADA bricks or other compatible ports)
- *(Optional)* Breadboard and jumper wires for prototyping

## Hardware Connection Guide

Follow these steps to connect the hardware components:

1. **ESP32 to Light Sensor:**
   - Connect the sensor's power (VCC) and ground (GND) pins to the ESP32's 3.3V and GND pins, respectively.
   - Connect the sensor's data (SDA) pin to the ESP32's GPIO21.
   - Connect the sensor's clock (SCL) pin to the ESP32's GPIO22.

2. **ESP32 to LEDs via MOSFET:**
   - Connect the MOSFET's source (S) to GND.
   - Connect the MOSFET's drain (D) to the LED's negative terminal.
   - Connect the LED's positive terminal to a 5V power source.
   - Connect the MOSFET's gate (G) to a GPIO pin on the ESP32 (e.g., GPIO23).

3. **Power Supply:**
   - Ensure the ESP32 and LEDs have an adequate and stable power source. Use a USB-A module or other suitable power supply if needed.

## Software Setup

### Standalone Program

1. Install the Arduino IDE and set up the ESP32 development environment.
2. Clone this repository and open the standalone program file.
3. Update the code with your specific GPIO pin connections if needed.
4. Compile and upload the code to the ESP32.

### ESPHome Integration with Home Assistant

1. Ensure Home Assistant and ESPHome are installed and configured.
2. Copy the `BrickDimmer.yaml` file to your ESPHome configuration folder.
3. Edit the `BrickDimmer.yaml` file to match your hardware setup (e.g., GPIO pins).
4. Flash the configuration to your ESP32 using ESPHome.
5. Restart Home Assistant and add the new ESPHome device. The light sensor and switch entities will be automatically added.

## Usage

- **Standalone Mode:** LEDs will automatically turn on/off based on ambient light intensity.
- **Home Assistant Mode:** Use the switch entity to manually control the LEDs, and the light sensor entity for automation rules.

## Troubleshooting

- Ensure all connections are secure and components are functioning correctly.
- Double-check the GPIO pin mappings in the code or YAML file.
- Verify that the ESP32 is receiving adequate power.
