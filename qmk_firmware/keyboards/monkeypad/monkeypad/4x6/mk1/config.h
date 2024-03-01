/*
Copyright 2023 ozsan <monkeypad39@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Handedness */
#define SPLIT_HAND_PIN GP6 // Determine Left/Right
#define MATRIX_ROWS 12
#define MATRIX_COLS 7
#define MATRIX_ROWS_MCU 2
#define MATRIX_ROWS_MCP 4

/* Reset */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP7
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* Serial Communication */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_DRIVER SIOD0
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_TIMEOUT 20 // USART driver timeout. default 100
#define SELECT_SOFT_SERIAL_SPEED 1
// #define SERIAL_DEBUG

/* Module Configuration */
/* Analog Joystick */
#if defined(USE_DEVICE_analog_joystick)
#    define ANALOG_JOYSTICK_SPEED_REGULATOR 4 // Lower Values Create Faster Movement
#    define ANALOG_JOYSTICK_AXIS_MIN 0
#    define ANALOG_JOYSTICK_AXIS_MAX 1023
#    undef JOYSTICK_BUTTON_COUNT
#    define JOYSTICK_BUTTON_COUNT 1
#    undef JOYSTICK_AXIS_COUNT
#    define JOYSTICK_AXIS_COUNT 2
#    undef JOYSTICK_AXIS_RESOLUTION
#    define JOYSTICK_AXIS_RESOLUTION 10
#    define ANALOG_JOYSTICK_X_AXIS_PIN GP27
#    define ANALOG_JOYSTICK_Y_AXIS_PIN GP26
// #    define JOYSTICK_WHEEL_REVERSE
#endif

#if defined(USE_DEVICE_pmw3389) || defined(USE_DEVICE_cirque_pinnacle_spi)
/* pointing device via spi (common pin assign) */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN GP26
#    define SPI_MISO_PIN GP8
#    define SPI_MOSI_PIN GP27

/* Trackball */
#    if defined(USE_DEVICE_pmw3389)
#        define POINTING_DEVICE_CS_PIN GP9
#        define PMW33XX_CPI 500
#        define PMW33XX_CS_DIVISOR 64
// #     define TRACKBALL_SCROLL_REVERSE /* To invert the scrolling direction (_ie._ mimic macOS "natural" scroll direction) */
#    endif

/* Trackpad */
#    if defined(USE_DEVICE_cirque_pinnacle_spi)
#        define CIRQUE_PINNACLE_SPI_CS_PIN GP9
// #     define CIRQUE_PINNACLE_TAP_ENABLE
// #     define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#     define TRACKPAD_SCROLL_REVERSE
// #     define TRACKPAD_CURSOR_REVERSE
#    endif
#endif

#if !defined(POINTING_DEVICE_TASK_THROTTLE_MS)
#    define POINTING_DEVICE_TASK_THROTTLE_MS 10 // Cirque Pinnacle in normal operation produces data every 10ms.
#endif
 
/* Pointing device orientation */
#if defined(SPLIT_POINTING_ENABLE)
#    if defined(POINTING_DEVICE_COMBINED)
#        define POINTING_DEVICE_ROTATION_180
#    elif defined(POINTING_DEVICE_LEFT)
#        define POINTING_DEVICE_ROTATION_180
#    endif
#endif

/* Encoder */
#if defined(ENCODER_ENABLE)
// left encode
#    if defined MODULE_DEVICE_LEFT_encoder
#        define ENCODERS_PAD_A { GP27 }
#        define ENCODERS_PAD_B { GP26 }
#       if defined MODULE_DEVICE_RIGHT_encoder
#           define ENCODERS_PAD_A_RIGHT { GP26 }
#           define ENCODERS_PAD_B_RIGHT { GP27 }
#       endif
// right encoder
#    elif defined MODULE_DEVICE_RIGHT_encoder // only right encoder
#           define ENCODERS_PAD_A       { GP26 }
#           define ENCODERS_PAD_B       { GP27 }
#    endif
#endif
// dummy encoder pins configuration for REMAP
#ifndef ENCODERS_PAD_A
#define ENCODERS_PAD_A { GP2 }
#endif
#ifndef ENCODERS_PAD_B
#define ENCODERS_PAD_B { GP3 }
#endif
