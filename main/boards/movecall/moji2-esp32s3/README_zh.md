# 编译配置指南

本文档介绍了如何为 **Movecall Moji2.0 ESP32-S3 版（小智AI衍生版）** 配置和编译固件。

## 🛠 环境要求
*   **ESP-IDF 版本**: v6.0.2（v5.5+ 亦可）
*   **芯片型号**: ESP32-S3
*   **模组**: ESP32-S3-WROOM-1 **N16R8**（16MB Flash + 8MB Octal PSRAM）

## 🔗 硬件开源信息
本项目为 Moji 2.0 开源硬件的 ESP32-S3 版本，外设与 ESP32-C5 版（[moji2-esp32c5](../moji2-esp32c5)）完全一致：
*   **立创开源硬件平台**: [https://oshwhub.com/movecall/moji2](https://oshwhub.com/movecall/moji2)

---

## 📌 引脚分配（同焊盘对齐）

分配原则：**尽量保持 PCB 走线不变**。
C5 PIN1~14 = S3 PIN1~14（相同物理位置）。  
C5 PIN15~29 = S3 PIN27~41（S3 多出 PIN15~26）。

**19 个信号中 16 个同焊盘，仅 3 个需改飞线**（PA、电池ADC、I2C SCL），原因是 R8 模组的 Octal PSRAM 占用了 GPIO35~37。

### ES8311 Codec 连接

| S3 GPIO | S3 PIN | 信号 | → | ES8311 PIN | ES8311 脚名 |
|---------|--------|------|---|------------|------------|
| GPIO40 | 33 | **DOUT** (ESP→Codec) | → | PIN9 | **DSDIN** |
| GPIO44 | 36 | **DIN** (ESP←Codec) | ← | PIN7 | **ASDOUT** |
| GPIO43 | 37 | **BCLK** | → | PIN6 | SCLK |
| GPIO42 | 35 | **WS** (LRCK) | → | PIN8 | LRCK |
| GPIO2 | 38 | **MCLK** | → | PIN2 | MCLK |
| GPIO1 | 39 | **I2C SDA** | ↔ | PIN19 | CDATA |
| GPIO39 | 32 | **I2C SCL** | ↔ | PIN1 | CCLK |

> ⚠️ **注意：** GPIO43 同时也是 UART0 TXD0。Boot ROM 启动时会在该脚短暂输出日志，但此时 ES8311 的 SCLK 为高阻态→**完全无害**。本板不使用 UART 调试。

### 完整引脚表

| # | 功能 | C5 PIN | C5 GPIO | S3 PIN | S3 GPIO | 走线 | 说明 |
|---|---|---|---|---|---|---|---|
| 1 | 屏背光 PWM | 4 | GPIO2 | 4 | **GPIO4** | 同焊盘 ✓ | |
| 2 | 屏 QSPI CS | 5 | GPIO3 | 5 | **GPIO5** | 同焊盘 ✓ | |
| 3 | 屏 QSPI 时钟 | 6 | GPIO0 | 6 | **GPIO6** | 同焊盘 ✓ | |
| 4 | 屏 QSPI 复位 | 7 | GPIO1 | 7 | **GPIO7** | 同焊盘 ✓ | |
| 5 | 屏 QSPI D3 | 8 | GPIO6 | 8 | **GPIO15** | 同焊盘 ✓ | |
| 6 | 屏 QSPI D2 | 9 | GPIO7 | 9 | **GPIO16** | 同焊盘 ✓ | |
| 7 | 屏 QSPI D1 | 10 | GPIO8 | 10 | **GPIO17** | 同焊盘 ✓ | |
| 8 | 屏 QSPI D0 | 11 | GPIO9 | 11 | **GPIO18** | 同焊盘 ✓ | |
| 9 | 状态 LED | 12 | GPIO10 | 12 | **GPIO8** | 同焊盘 ✓ | |
| 10 | BOOT 按键 | 15 | GPIO28 | 27 | **GPIO0** | 同焊盘 ✓ | S3 标准 BOOT 脚 |
| 11 | 功放 PA | 16 | GPIO5 | **17** | **GPIO9** | **改飞线** 🔄 | C5 pin16→S3 pin28(IO35) PSRAM → 改到 PIN17 |
| 12 | 电池 ADC | 17 | GPIO4 (ADC1_CH3) | **18** | **GPIO10 (ADC1_CH9)** | **改飞线** 🔄 | C5 pin17→S3 pin29(IO36) PSRAM → 改到 PIN18，代码改 CH3→CH9 |
| 13 | I2C SCL | 18 | GPIO27 | **32** | **GPIO39** | **改飞线** 🔄 | C5 pin18→S3 pin30(IO37) PSRAM → 改到 PIN32 |
| 14 | I2S DOUT (ESP→Codec) | 21 | GPIO23 | 33 | **GPIO40** | 同焊盘 ✓ | 接 ES8311 PIN9 DSDIN |
| 15 | I2S WS (LRCK) | 23 | GPIO24 | 35 | **GPIO42** | 同焊盘 ✓ | |
| 16 | I2S DIN (ESP←Codec) | 24 | GPIO12 (RX0) | **36** | **GPIO44 (RXD0)** | 同焊盘 ✓ | 接 ES8311 PIN7 ASDOUT |
| 17 | I2S BCLK | 25 | GPIO11 (TX0) | **37** | **GPIO43 (TXD0)** | 同焊盘 ✓ | |
| 18 | I2S MCLK | 26 | GPIO25 | 38 | **GPIO2** | 同焊盘 ✓ | |
| 19 | I2C SDA | 27 | GPIO26 | 39 | **GPIO1** | 同焊盘 ✓ | 内部上拉，建议硬件加 4.7kΩ 外部上拉 |

保留引脚（请勿接其他外设）：
*   **GPIO19/20**：USB D-/D+
*   **GPIO26–37**：内部 Flash（26–32）与 Octal PSRAM（33–37，R8 模组 IO35/36/37 已接八线 PSRAM）
*   **GPIO45/46**：Strapping 引脚
*   **GPIO40–42/47/48**：空闲；40–42 为默认 JTAG 引脚，预留调试

---

## 🚀 编译步骤

### 1. 设置编译目标
首先，将项目目标芯片设置为 ESP32-S3：
```bash
idf.py set-target esp32s3
```

### 2. 配置开发板型号
运行以下命令打开配置菜单进行板型选择：
```bash
idf.py menuconfig
```

**请在菜单中按照以下路径进行操作：**
> **Xiaozhi Assistant** -> **Board Type** -> **Movecall Moji 2.0 (ESP32-S3)**

*操作提示：配置完成后，按 **S** 保存并按回车确认，按 **Q** 退出。*

### 3. 执行编译
运行以下命令开始构建项目：
```bash
idf.py build
```

---

## 🔧 常用维护命令

**清理编译缓存 (遇到报错建议执行)：**
```bash
idf.py fullclean
```

**烧录固件：**
```bash
idf.py flash
```

**查看串口日志：**
```bash
idf.py monitor
```