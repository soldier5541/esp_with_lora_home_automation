# 📡 LoRa Home Automation System

A long-range wireless home automation system built using **ESP32-WROOM** and **LoRa (SX1278 433MHz)** modules. This project demonstrates reliable long-distance control of electrical appliances without relying on Wi-Fi or the Internet.

The system consists of two ESP32-based nodes:

- **Transmitter Node** – Reads the state of physical push buttons and transmits commands over LoRa.
- **Receiver Node** – Receives the commands and controls relay modules connected to electrical loads.

---

## 🚀 Features

- 📶 Long-range communication using LoRa (433 MHz)
- 🎛️ Four independent appliance controls
- 💡 LED indicators for switch status
- 🔌 Relay-controlled outputs for appliances
- 📺 OLED display for communication status
- 📡 Bidirectional communication support
- ⚡ Low latency communication
- 🌐 Does not require Wi-Fi, Bluetooth, or Internet connectivity
- 🔒 Suitable for remote areas where network infrastructure is unavailable

---

## 🛠 Hardware Used

### Transmitter

- ESP32-WROOM
- LoRa SX1278 (433 MHz)
- 4 Push Buttons
- 4 LED Indicators
- 0.96" OLED Display (SSD1306 I2C)
- Power Supply

### Receiver

- ESP32-WROOM
- LoRa SX1278 (433 MHz)
- 4-Channel Relay Module
- Power Supply

---

## 📖 Working Principle

1. The transmitter continuously monitors four push buttons.
2. Every button state is converted into a comma-separated data string.

Example:

```
1,0,1,0
```

where:

| Value | Meaning |
|--------|---------|
| 1 | Button Released |
| 0 | Button Pressed |

3. The data packet is transmitted using LoRa.
4. The receiver decodes the received packet.
5. Each relay is updated according to its corresponding button state.
6. The receiver can send acknowledgement/status messages back to the transmitter.
7. The transmitter displays the received status on the OLED display.

---

## 📡 Communication Protocol

Each LoRa packet contains:

| Field | Description |
|--------|-------------|
| Destination Address | Receiver Address |
| Sender Address | Transmitter Address |
| Message ID | Packet Counter |
| Payload Length | Length of Message |
| Payload | Button States |

Example Payload:

```
0,1,1,0
```

---

## 📟 OLED Display

The transmitter uses a 128×64 SSD1306 OLED display to show:

- Receiver status
- Relay status
- Incoming acknowledgement
- Communication information

---

## 📏 Range Test

### Real-world Test Results

- **Frequency:** 433 MHz
- **Antenna:** Standard Laptop LoRa Antennas
- **Environment:** Outdoor
- **Condition:** Clear Line of Sight (No obstacles)
- **Achieved Distance:** **~1 Kilometer**

The communication remained stable throughout the entire test without packet loss under line-of-sight conditions.

> Actual range depends on antenna quality, transmission power, terrain, buildings, trees, and environmental interference.

---

## 🔌 Pin Connections

### LoRa Module

| ESP32  | LoRa |
|--------|------|
| GPIO5  | NSS (CS) |
| GPIO34 | RESET |
| GPIO2  | DIO0 |
| SPI    | SCK, MOSI, MISO |

### Buttons

| Button | GPIO |
|---------|------|
| Switch 1 | GPIO33 |
| Switch 2 | GPIO13 |
| Switch 3 | GPIO14 |
| Switch 4 | GPIO26 |

---

## 📚 Libraries Used

Install the following libraries from the Arduino Library Manager:

- LoRa
- SPI
- Adafruit GFX
- Adafruit SSD1306

---

## ⚙ How the Transmitter Code Works

The transmitter firmware performs the following operations:

- Initializes the LoRa module and OLED display.
- Configures four GPIO pins as button inputs using internal pull-up resistors.
- Reads the state of each button periodically.
- Combines the button states into a comma-separated string.
- Packages the data with source and destination addresses.
- Sends the packet via LoRa.
- Listens for acknowledgement packets from the receiver.
- Displays received information on the OLED display.
- Prints RSSI and SNR values to the Serial Monitor for debugging and signal quality analysis.

---

## 🎯 Applications

- Home Automation
- Farm Automation
- Remote Lighting Control
- Warehouse Automation
- Industrial Machine Control
- Smart Irrigation Systems
- Rural Automation
- IoT Research Projects
- Disaster Recovery Communication
- Long-Range Wireless Switching

---

## 🔮 Future Improvements

- AES Encryption for secure communication
- Battery-powered portable transmitter
- OLED menu interface
- Sensor integration (Temperature, Humidity, Motion)
- Mobile app gateway using ESP32 + Wi-Fi
- MQTT/Cloud integration
- Acknowledgement retries and packet retransmission
- Multiple receiver support
- Mesh networking
- OTA firmware updates

---

## 🤝 Contributions

Contributions, suggestions, and improvements are welcome.

Feel free to fork this repository and submit a pull request.

---

## 📜 License

This project is open-source and available under the **MIT License**.

---

## 👨‍💻 Author

Developed as a long-range wireless home automation project using **ESP32** and **LoRa** technology.
