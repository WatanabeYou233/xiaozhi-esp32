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

## 📌 引脚分配（ESP32-S3-WROOM-1，N16R8）

| 功能 | ESP32-C5 原引脚 | ESP32-S3 引脚 | 说明 |
|---|---|---|---|
| BOOT 按键 | GPIO28 | **GPIO0** | Strapping 引脚，标准 BOOT 键，支持深睡唤醒（RTC） |
| 电池电压 ADC | GPIO4（ADC1_CH3） | **GPIO4（ADC1_CH3）** | 两颗芯片通道一致，软件无需改动 |
| 音频功放 PA 使能 | GPIO5 | **GPIO5** | 沿用同号 |
| 屏 QSPI D3 | GPIO6 | **GPIO6** | 沿用同号 |
| 屏 QSPI D2 | GPIO7 | **GPIO7** | 沿用同号 |
| 屏 QSPI D1 | GPIO8 | **GPIO8** | 沿用同号 |
| 屏 QSPI D0 | GPIO9 | **GPIO9** | 沿用同号 |
| 屏 QSPI CS | GPIO3 | **GPIO10** | GPIO3 在 S3 上为 Strapping，重新分配 |
| 屏 QSPI 复位 | GPIO1 | **GPIO11** | 重新分配 |
| 屏 QSPI 时钟 | GPIO0 | **GPIO12** | GPIO0 在 S3 上留给 BOOT，重新分配 |
| 屏背光（PWM） | GPIO2 | **GPIO13** | 重新分配 |
| I2S MCLK | GPIO25 | **GPIO14** | 重新分配 |
| I2S BCLK | GPIO11 | **GPIO15** | 重新分配 |
| I2S WS（LRCK） | GPIO24 | **GPIO16** | 重新分配 |
| I2S DOUT（→ES8311） | GPIO23 | **GPIO17** | 重新分配 |
| I2S DIN（←ES8311） | GPIO12 | **GPIO18** | 重新分配 |
| I2C SDA（ES8311） | GPIO26 | **GPIO1** | 内部上拉，建议硬件加 4.7kΩ 外部上拉 |
| I2C SCL（ES8311） | GPIO27 | **GPIO2** | 内部上拉，建议硬件加 4.7kΩ 外部上拉 |
| 状态 LED | GPIO10 | **GPIO21** | 重新分配 |

保留引脚（请勿接其他外设）：
*   **GPIO19/20**：USB D-/D+
*   **GPIO26–37**：内部 Flash（26–32）与 Octal PSRAM（33–37，R8 模组 IO35/36/37 已接八线 PSRAM）
*   **GPIO43/44（TXD0/RXD0）**：UART0 下载/日志口
*   **GPIO3/45/46**：Strapping 引脚
*   **GPIO38–42/47/48**：空闲；39–42 为默认 JTAG 引脚，预留调试

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
