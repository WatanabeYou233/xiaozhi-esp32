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

## 📌 Pin Mapping (Physical-Pad-Aligned)

The pin assignment keeps the **same PCB trace** wherever possible.  
C5 PIN1~14 = S3 PIN1~14 (same physical position).  
C5 PIN15~29 = S3 PIN27~41 (S3 has extra PIN15~26).

**16 of 19 signals keep the same trace; only 3 need rerouting** (PA, Battery ADC, I2C SCL) due to Octal PSRAM occupying GPIO35~37 on R8 modules.

### ES8311 Codec Connections

| S3 GPIO | S3 PIN | Signal | → | ES8311 PIN | ES8311 Pin Name |
|---------|--------|--------|---|------------|-----------------|
| GPIO40 | 33 | **DOUT** (ESP→Codec) | → | PIN9 | **DSDIN** |
| GPIO44 | 36 | **DIN** (ESP←Codec) | ← | PIN7 | **ASDOUT** |
| GPIO43 | 37 | **BCLK** | → | PIN6 | SCLK |
| GPIO42 | 35 | **WS** (LRCK) | → | PIN8 | LRCK |
| GPIO2 | 38 | **MCLK** | → | PIN2 | MCLK |
| GPIO1 | 39 | **I2C SDA** | ↔ | PIN19 | CDATA |
| GPIO39 | 32 | **I2C SCL** | ↔ | PIN1 | CCLK |

> ⚠️ **Note:** GPIO43 is also UART0 TXD0. Boot ROM briefly outputs text on this pin at startup, but ES8311 SCLK is high-Z before I2S config → **harmless**. UART debug is not used on this board.

### Full Pin Table

| # | Function | C5 PIN | C5 GPIO | S3 PIN | S3 GPIO | Trace | Notes |
|---|---|---|---|---|---|---|---|
| 1 | LCD backlight (PWM) | 4 | GPIO2 | 4 | **GPIO4** | Same ✓ | |
| 2 | LCD QSPI CS | 5 | GPIO3 | 5 | **GPIO5** | Same ✓ | |
| 3 | LCD QSPI SCLK | 6 | GPIO0 | 6 | **GPIO6** | Same ✓ | |
| 4 | LCD QSPI RESET | 7 | GPIO1 | 7 | **GPIO7** | Same ✓ | |
| 5 | LCD QSPI D3 | 8 | GPIO6 | 8 | **GPIO15** | Same ✓ | |
| 6 | LCD QSPI D2 | 9 | GPIO7 | 9 | **GPIO16** | Same ✓ | |
| 7 | LCD QSPI D1 | 10 | GPIO8 | 10 | **GPIO17** | Same ✓ | |
| 8 | LCD QSPI D0 | 11 | GPIO9 | 11 | **GPIO18** | Same ✓ | |
| 9 | Status LED | 12 | GPIO10 | 12 | **GPIO8** | Same ✓ | |
| 10 | BOOT button | 15 | GPIO28 | 27 | **GPIO0** | Same ✓ | S3 standard BOOT pin, Deep-sleep wake |
| 11 | Audio PA (EN) | 16 | GPIO5 | **17** | **GPIO9** | **Reroute** 🔄 | C5 pin16→S3 pin28(IO35) PSRAM → moved to free pin17 |
| 12 | Battery ADC | 17 | GPIO4 (ADC1_CH3) | **18** | **GPIO10 (ADC1_CH9)** | **Reroute** 🔄 | C5 pin17→S3 pin29(IO36) PSRAM → moved to free pin18, code: CH3→CH9 |
| 13 | I2C SCL (ES8311) | 18 | GPIO27 | **32** | **GPIO39** | **Reroute** 🔄 | C5 pin18→S3 pin30(IO37) PSRAM → moved to pin32, near SDA at pin39 |
| 14 | I2S DOUT (ESP→Codec) | 21 | GPIO23 | 33 | **GPIO40** | Same ✓ | Connects to ES8311 PIN9 DSDIN |
| 15 | I2S WS (LRCK) | 23 | GPIO24 | 35 | **GPIO42** | Same ✓ | |
| 16 | I2S DIN (ESP←Codec) | 24 | GPIO12 (RX0) | **36** | **GPIO44 (RXD0)** | Same ✓ | Connects to ES8311 PIN7 ASDOUT |
| 17 | I2S BCLK | 25 | GPIO11 (TX0) | **37** | **GPIO43 (TXD0)** | Same ✓ | |
| 18 | I2S MCLK | 26 | GPIO25 | 38 | **GPIO2** | Same ✓ | |
| 19 | I2C SDA (ES8311) | 27 | GPIO26 | 39 | **GPIO1** | Same ✓ | Internal pull-up, external 4.7kΩ recommended |

Reserved pins (do not connect any other peripherals):
*   **GPIO19/20**: USB D-/D+
*   **GPIO26–37**: Internal Flash (26–32) and Octal PSRAM (33–37, on R8 modules IO35/36/37 are connected to the Octal SPI PSRAM)
*   **GPIO45/46**: Strapping pins
*   **GPIO40–42/47/48**: Free, of which 40–42 are default JTAG pins

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