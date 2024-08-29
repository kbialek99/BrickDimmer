# Project description

This project was made to make the leds from the CADA brick sets smart, using ESP32 and the light sensor.
It can be built and uploaded to esp device as a standalone program that will check the light intensity, and based on that will turn on/off the LEDs.
Alternatively BrickDimmer.yaml can be uploaded via ESPHome, making it compatibile with the HomeAssistant. Two entities will be added, the switch button and the light sensor.

## Required hardware

- Esp32
- light sensor of choice (BH1750 in this case)
- MOSFET
- USB-A module if used with the CADA bricks or any other port 
- (optional) breadboard

## Hardware connection guide

TBD