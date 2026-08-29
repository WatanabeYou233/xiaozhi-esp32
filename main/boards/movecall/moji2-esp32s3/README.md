# Build and Configuration Guide

This document provides instructions on how to configure and build the firmware for **Movecall Moji2.0 ESP32-S3 (Xiaozhi AI Edition)**.

## 🛠 Prerequisites
*   **ESP-IDF Version**: v6.0.2 (v5.5+ also works)
*   **Target Chip**: ESP32-S3
*   **Module**: ESP32-S3-WROOM-1 **N16R8** (16MB flash + 8MB Octal PSRAM)

## 🔗 Hardware Information
This is the ESP32-S3 variant of the Moji 2.0 open-source hardware. Peripherals are identical to the ESP32-C5 version ([moji2-esp32c5](../moji2-esp32c5)):
*   **OSHWHub Link**: [https://oshwhub.com/movecall/moji2](https://oshwhub.com/movecall/moji2)

---

## 📌 Pin Mapping (ESP32-S3-WROOM-1, N16R8)

| Function | ESP32-C5 pin (original) | ESP32-S3 pin | Notes |
|---|---|---|---|
| BOOT button | GPIO28 | **GPIO0** | Strapping pin, standard BOOT key, supports Deep-sleep wake-up (RTC) |
| Battery ADC | GPIO4 (ADC1_CH3) | **GPIO4 (ADC1_CH3)** | Channel is the same on both chips, no code changes needed |
| Audio PA (EN) | GPIO5 | **GPIO5** | Reuses the same number |
| LCD QSPI D3 | GPIO6 | **GPIO6** | Reuses the same number |
| LCD QSPI D2 | GPIO7 | **GPIO7** | Reuses the same number |
| LCD QSPI D1 | GPIO8 | **GPIO8** | Reuses the same number |
| LCD QSPI D0 | GPIO9 | **GPIO9** | Reuses the same number |
| LCD QSPI CS | GPIO3 | **GPIO10** | GPIO3 is a strapping pin on S3, reassigned |
| LCD QSPI RESET | GPIO1 | **GPIO11** | Reassigned |
| LCD QSPI SCLK | GPIO0 | **GPIO12** | GPIO0 is reserved for BOOT on S3, reassigned |
| LCD backlight (PWM) | GPIO2 | **GPIO13** | Reassigned |
| I2S MCLK | GPIO25 | **GPIO14** | Reassigned |
| I2S BCLK | GPIO11 | **GPIO15** | Reassigned |
| I2S WS (LRCK) | GPIO24 | **GPIO16** | Reassigned |
| I2S DOUT (→ES8311 DIN) | GPIO23 | **GPIO17** | Reassigned |
| I2S DIN (←ES8311 DOUT) | GPIO12 | **GPIO18** | Reassigned |
| I2C SDA (ES8311) | GPIO26 | **GPIO1** | Internal pull-up, external 4.7kΩ pull-up resistor is recommended |
| I2C SCL (ES8311) | GPIO27 | **GPIO2** | Internal pull-up, external 4.7kΩ pull-up resistor is recommended |
| Status LED | GPIO10 | **GPIO21** | Reassigned |

Reserved pins (do not connect any other peripherals):
*   **GPIO19/20**: USB D-/D+
*   **GPIO26–37**: Internal Flash (26–32) and Octal PSRAM (33–37, on R8 modules IO35/36/37 are connected to the Octal SPI PSRAM)
*   **GPIO43/44 (TXD0/RXD0)**: UART0 download/log port
*   **GPIO3/45/46**: Strapping pins
*   **GPIO38–42/47/48**: Free, of which 39–42 are default JTAG pins

---

## 🚀 Build Steps

### 1. Set the Build Target
Initialize the project to target the ESP32-S3 chip:
```bash
idf.py set-target esp32s3
```

### 2. Configure the Board Type
Open the graphical configuration menu:
```bash
idf.py menuconfig
```

**Navigate to the following path to select your board:**
> **Xiaozhi Assistant** -> **Board Type** -> **Movecall Moji 2.0 (ESP32-S3)**

*Note: After selecting, press **S** to save (then Enter to confirm) and press **Q** to exit.*

### 3. Build the Project
Run the following command to start the compilation:
```bash
idf.py build
```

---

## 🔧 Useful Commands

**Clean Build Files (Recommended if you encounter errors):**
```bash
idf.py fullclean
```

**Flash Firmware to Device:**
```bash
idf.py flash
```

**Monitor Serial Output:**
```bash
idf.py monitor
```
