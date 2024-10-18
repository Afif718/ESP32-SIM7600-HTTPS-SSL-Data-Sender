# SIM7600 Data Sender (HTTPS & SSL)

## Description
This project demonstrates how to send sensor data using the 4G SIM7600 (A7670C) module over GPRS securely with HTTPS and SSL. It includes error handling, session management, and a deep sleep feature to conserve power.

## Features
- GPRS connection using the SIM7600 4G modem
- JSON payload creation for sensor data
- SSL communication with a remote server
- Session management with timeout handling
- Reconnection logic for network stability
- Efficient error handling

## Hardware Requirements
- ESP32 development board
- SIM7600 modem (A7670C)
- Necessary power supply for the modem
- Jumper wires for connections

## Software Requirements
- Arduino IDE
- TinyGSM library -> https://github.com/vshymanskyy/TinyGSM
- ESP_SSLClient library -> https://github.com/mobizt/ESP_SSLClient
- ArduinoJson library
