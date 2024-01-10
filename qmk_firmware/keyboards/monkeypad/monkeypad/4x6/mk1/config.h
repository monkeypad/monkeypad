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
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT 100 // USART driver timeout. default 100
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_DEBUG

/* Module Configuration */
/* Analog Joystick */
#if defined(USE_DEVICE_analog_joystick)
#    define POINTING_DEVICE_TASK_THROTTLE_MS 1
#    define ANALOG_JOYSTICK_SPEED_REGULATOR 20 // Lower Values Create Faster Movement
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
#endif

/* Trackball */
#if defined(USE_DEVICE_pmw3389)
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN GP26
#    define SPI_MISO_PIN GP8
#    define SPI_MOSI_PIN GP27
#    define POINTING_DEVICE_CS_PIN GP9
#    define PMW33XX_CPI 500
#    define PMW33XX_CS_DIVISOR 64
#endif

/* Pointing device direction */
#if defined(POINTING_DEVICE_ENABLE)
// #    define TRACKBALL_SCROLL_REVERSE /* To invert the scrolling direction (_ie._ mimic macOS "natural" scroll direction) */
// #    define JOYSTICK_WHEEL_REVERSE
#endif

/* Pointing device orientation */
#if defined(SPLIT_POINTING_ENABLE)
#    if defined(POINTING_DEVICE_COMBINED)
#        define POINTING_DEVICE_INVERT_Y
#        define POINTING_DEVICE_INVERT_X_RIGHT
#        define POINTING_DEVICE_ROTATION_90
#        define POINTING_DEVICE_ROTATION_90_RIGHT
#    elif defined(POINTING_DEVICE_LEFT)
#        define POINTING_DEVICE_INVERT_Y
#        define POINTING_DEVICE_ROTATION_90
#    elif defined(POINTING_DEVICE_RIGHT)
#        define POINTING_DEVICE_INVERT_X
#        define POINTING_DEVICE_ROTATION_90
#    endif
#endif

/* Encoder */
#if defined(ENCODER_ENABLE)
// left encoder
#    if defined MODULE_DEVICE_LEFT_encoder
#        define ENCODERS_PAD_A { GP27 }
#        define ENCODERS_PAD_B { GP26 }
// right encoder
#    elif defined MODULE_DEVICE_RIGHT_encoder
#        if defined(ENCODERS_PAD_A) || defined(ENCODERS_PAD_B) // it has left encoder
#           define ENCODERS_PAD_A_RIGHT { GP27 }
#           define ENCODERS_PAD_B_RIGHT { GP26 }
#        else // right encoder
#           define ENCODERS_PAD_A       { GP27 }
#           define ENCODERS_PAD_B       { GP26 }
#        endif
#    endif
#endif
