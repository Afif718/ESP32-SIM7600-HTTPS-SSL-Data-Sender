# 📡 ESP32 + SIM7600 — Secure HTTPS/SSL Data Sender over 4G

![Platform](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif)
![Modem](https://img.shields.io/badge/Modem-SIM7600%20%7C%20A7670C-red)
![Protocol](https://img.shields.io/badge/Protocol-HTTPS%20%2F%20SSL-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Arduino-00979D?logo=arduino)
![License](https://img.shields.io/badge/License-MIT-green)
![Stars](https://img.shields.io/github/stars/Afif718/ESP32-SIM7600-HTTPS-SSL-Data-Sender?style=social)

> **Send sensor data securely over 4G LTE using ESP32 + SIM7600/A7670C with HTTPS and SSL — no Wi-Fi needed.**

---

## 🔍 Why This Project?

Most ESP32 IoT projects rely on Wi-Fi, which limits deployments to areas with wireless coverage. This project solves that by using a **4G LTE cellular modem (SIM7600 / A7670C)** to send sensor data securely to any HTTPS endpoint — perfect for **remote monitoring**, **field sensors**, and **off-grid IoT deployments**.

---

## ✨ Features

- 📶 **4G GPRS connectivity** via SIM7600 / A7670C modem — no Wi-Fi required
- 🔒 **SSL/TLS encrypted communication** using ESP_SSLClient
- 📦 **JSON payload construction** with ArduinoJson for structured data
- 🔁 **Auto-reconnect logic** for robust network stability
- ⏱️ **Session management** with configurable timeout handling
- ⚠️ **Comprehensive error handling** for modem and network failures
- 🌙 **Deep sleep support** to minimize power consumption in field deployments

---

## 🛠️ Hardware Requirements

| Component | Details |
|---|---|
| Microcontroller | ESP32 development board |
| Cellular Modem | SIM7600 or A7670C (4G LTE) |
| Power Supply | Adequate supply for modem (typically 3.7–4.2V, 2A peak) |
| Wiring | Jumper wires for UART connections |
| SIM Card | Active SIM with data plan |

---

## 💻 Software Requirements

| Library | Purpose | Link |
|---|---|---|
| Arduino IDE | Development environment | [arduino.cc](https://www.arduino.cc) |
| TinyGSM | Modem communication | [vshymanskyy/TinyGSM](https://github.com/vshymanskyy/TinyGSM) |
| ESP_SSLClient | SSL/TLS over TCP | [mobizt/ESP_SSLClient](https://github.com/mobizt/ESP_SSLClient) |
| ArduinoJson | JSON payload building | [arduinojson.org](https://arduinojson.org) |

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/Afif718/ESP32-SIM7600-HTTPS-SSL-Data-Sender.git
cd ESP32-SIM7600-HTTPS-SSL-Data-Sender
```

### 2. Install Libraries

In Arduino IDE, go to **Sketch → Include Library → Manage Libraries** and install:
- `TinyGSM`
- `ESP_SSLClient`
- `ArduinoJson`

### 3. Configure Your Settings

Open `Sim7600_HTTPS_SSL_Final.ino` and update these values:

```cpp
const char APN[]      = "your_apn_here";       // Your carrier's APN
const char SERVER[]   = "your.server.com";      // Your HTTPS endpoint
const char RESOURCE[] = "/api/data";            // API path
const int  PORT       = 443;                    // HTTPS port
```

### 4. Wire Up the Hardware

```
ESP32 TX  →  SIM7600 RX
ESP32 RX  →  SIM7600 TX
ESP32 GND →  SIM7600 GND
SIM7600 Power → Dedicated 4.2V / 2A supply
```

> ⚠️ **Do not power the SIM7600 from the ESP32's 3.3V pin** — the modem draws up to 2A during transmission peaks.

### 5. Upload & Monitor

Flash the sketch and open the Serial Monitor at **115200 baud** to observe connection logs and data transmission status.

---

## 📊 How It Works

```
[ESP32 Wakes Up]
      │
      ▼
[Initialize SIM7600 over UART]
      │
      ▼
[Connect to GPRS / 4G Network]
      │
      ▼
[Establish SSL Session with Server]
      │
      ▼
[Build JSON Payload from Sensor Data]
      │
      ▼
[Send HTTPS POST Request]
      │
      ▼
[Handle Response / Errors]
      │
      ▼
[Enter Deep Sleep to Save Power]
```

---

## 🌍 Use Cases

- 🌾 **Remote agricultural sensors** — soil, weather, irrigation monitoring
- 🏗️ **Construction site monitoring** — structural sensors, equipment tracking
- 🚗 **Vehicle telematics** — GPS + sensor data over cellular
- 🔋 **Off-grid IoT nodes** — battery-powered, no Wi-Fi needed
- 🏭 **Industrial field devices** — factory floor to cloud data pipelines

---

## 🔮 Future Improvements

- [ ] Add GPS integration for location-tagged data payloads
- [ ] Support MQTT over SSL as an alternative protocol
- [ ] OTA firmware update via cellular
- [ ] Low-power optimization with modem sleep modes
- [ ] Support for additional modems (SIM800, SIM900, EC21)

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!
Feel free to open an [issue](https://github.com/Afif718/ESP32-SIM7600-HTTPS-SSL-Data-Sender/issues) or submit a pull request.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 👤 Author

**M. H. A. Afif** — [@Afif718](https://github.com/Afif718)

> *Built for engineers who need reliable, secure data transmission beyond Wi-Fi range.* 📡
