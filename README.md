# IoT-Based Smart LED Matrix Display

A multipurpose, modular embedded system built on the ESP32 to drive a 64-bit (8x8) RGB CJMCU LED matrix. The system acts as a smart desktop gadget featuring real-time scrolling text tickers, smooth mathematical fluid-lighting animations, and automated retro micro-arcade games managed entirely via an over-the-air (OTA) Wi-Fi captive web portal.

## 🚀 Features
- **Wi-Fi Web Controller:** Hosts a local web server allowing users to switch system modes and update displayed text dynamically.
- **Dynamic Info Ticker:** Real-time text scrolling engine utilizing pixel-mapping canvas frameworks.
- **Ambient Lighting Generators:** Implements a multi-wave trigonometric plasma interference effect for ultra-smooth ambient lighting.
- **Retro Game Simulation:** Natively compiles standalone game loops for interactive micro-clones of classic *Snake* and *Pong*.

## 🛠️ Hardware Requirements
- **Microcontroller:** ESP32 (NodeMCU Development Board)
- **Display Module:** CJMCU 8x8 WS2812B RGB LED Matrix
- **Power:** 5V via Micro-USB (with software-capped brightness for current safety)

## 🔌 Circuit Pinout Connections
| CJMCU Matrix Pin | ESP32 GPIO Pin | Wire Description |
| ---------------- | -------------- | ---------------- |
| **VCC / 5V**     | VIN / 5V       | Power Supply     |
| **GND**          | GND            | Ground Reference |
| **DIN (Data In)**| GPIO 13        | SPI/Data Link    |

## 📦 Required Libraries
Ensure you have the following open-source dependencies installed in your IDE:
- `Adafruit_GFX` (Core graphics drawing canvas)
- `Adafruit_NeoPixel` (WS2812B protocol driver)
- `Adafruit_NeoMatrix` (Layout mapping for grid coordinates)

## 🔧 Installation & Setup
1. Clone this repository to your local machine.
2. Open `MatrixGadget.ino` inside the Arduino IDE or PlatformIO.
3. Install the required libraries via the Library Manager.
4. Flash the firmware to your connected ESP32 board.
5. On your phone or laptop, connect to the Wi-Fi Access Point network named `ESP32_Matrix_Gadget` (Password: `12345678`).
6. Open your web browser and navigate to `http://192.168.4.1` to access the live dashboard control page.
