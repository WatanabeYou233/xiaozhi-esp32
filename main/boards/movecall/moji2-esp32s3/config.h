#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

// Movecall Moji 2 (ESP32-S3) configuration
//
// ESP32-S3-WROOM-1 (N16R8: 16MB flash + 8MB Octal PSRAM) pin budget:
//   - GPIO26-37: reserved (internal flash & Octal PSRAM, GPIO35-37 are
//     connected to the Octal SPI PSRAM on R8 modules)
//   - GPIO19/20: reserved (USB D-/D+)
//   - GPIO43/44: reserved (UART0 TXD0/RXD0, flashing & logs)
//   - GPIO3/45/46: strapping pins, keep unused
//   - GPIO39-42: left free for JTAG debugging

#include <driver/gpio.h>

enum PowerSupply {
    kDeviceTypecSupply,
    kDeviceBatterySupply,
};

#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_I2S_GPIO_MCLK         GPIO_NUM_14
#define AUDIO_I2S_GPIO_WS           GPIO_NUM_16
#define AUDIO_I2S_GPIO_BCLK         GPIO_NUM_15
#define AUDIO_I2S_GPIO_DIN          GPIO_NUM_18
#define AUDIO_I2S_GPIO_DOUT         GPIO_NUM_17

#define AUDIO_CODEC_PA_PIN          GPIO_NUM_5
#define AUDIO_CODEC_I2C_SDA_PIN     GPIO_NUM_1
#define AUDIO_CODEC_I2C_SCL_PIN     GPIO_NUM_2
#define AUDIO_CODEC_ES8311_ADDR     ES8311_CODEC_DEFAULT_ADDR

#define BUILTIN_LED_GPIO            GPIO_NUM_21
#define BOOT_BUTTON_GPIO            GPIO_NUM_0

#define DISPLAY_WIDTH               360
#define DISPLAY_HEIGHT              360
#define DISPLAY_MIRROR_X            false
#define DISPLAY_MIRROR_Y            false
#define DISPLAY_SWAP_XY             false

#define DISPLAY_OFFSET_X            0
#define DISPLAY_OFFSET_Y            0

#define DISPLAY_BACKLIGHT_PIN       GPIO_NUM_13
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT false

#define DISPLAY_QSPI_H_RES           (360)
#define DISPLAY_QSPI_V_RES           (360)
#define DISPLAY_QSPI_BIT_PER_PIXEL   (16)

#define DISPLAY_QSPI_HOST           SPI2_HOST
#define DISPLAY_QSPI_SCLK_PIN       GPIO_NUM_12
#define DISPLAY_QSPI_RESET_PIN      GPIO_NUM_11
#define DISPLAY_QSPI_D0_PIN         GPIO_NUM_9
#define DISPLAY_QSPI_D1_PIN         GPIO_NUM_8
#define DISPLAY_QSPI_D2_PIN         GPIO_NUM_7
#define DISPLAY_QSPI_D3_PIN         GPIO_NUM_6
#define DISPLAY_QSPI_CS_PIN         GPIO_NUM_10


#define DISPLAY_SPI_SCLK_HZ         (40 * 1000 * 1000)

#define MOJI2_ST77916_PANEL_BUS_QSPI_CONFIG(sclk, d0, d1, d2, d3, max_trans_sz) \
    {                                                                             \
        .data0_io_num = d0,                                                       \
        .data1_io_num = d1,                                                       \
        .sclk_io_num = sclk,                                                      \
        .data2_io_num = d2,                                                       \
        .data3_io_num = d3,                                                       \
        .max_transfer_sz = max_trans_sz,                                          \
    }

#endif // _BOARD_CONFIG_H_
