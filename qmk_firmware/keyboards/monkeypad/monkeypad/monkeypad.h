/* Copyright 2023 ozsan <monkeypad39@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    JOYSTICK_MOUSE_MODE   = 0,
    JOYSTICK_WHEEL_MODE   = 1,
    JOYSTICK_ARROW_MODE   = 2,
    JOYSTICK_GAME_MODE    = 3,
    JOYSTICK_CUSTOM_MODE  = 4
} monkeypad_joystick_mode;

typedef enum {
    BALL_MOUSE_MODE  = 0,
    BALL_SCROLL_MODE = 1
} monkeypad_trackball_mode;

typedef struct {
    uint8_t trackball_mode;
    uint8_t trackball_mode_changed;
    uint8_t joystick_mode;
    uint8_t joystick_mode_changed;
} monkeypad_status_t;

typedef union {
    uint8_t raw;
    struct {
        uint8_t dpi_config : 4;
    };
} monkeypad_config_t;

enum monkeypad_keycodes {
    MK_SCROLL = SAFE_RANGE,
    MK_WHEEL,
    MK_ARROW,
    MK_PAD,
    MK_CUSTOM,
    DPI_UP,
    DPI_DN,
    DPI_RST,
    DPI_FINE,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
};

extern monkeypad_config_t keyboard_config;
extern uint16_t          dpi_array[];
uint8_t monkeypad_get_trackball_mode(void);
void    monkeypad_set_trackball_mode(uint8_t mode);
uint8_t monkeypad_get_joystick_mode(void);
void    monkeypad_set_joystick_mode(uint8_t mode);
