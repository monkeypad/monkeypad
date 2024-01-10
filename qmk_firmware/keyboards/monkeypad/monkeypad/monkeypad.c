/*
 * Copyright 2023 ozsan <monkeypad39@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include QMK_KEYBOARD_H

#if defined(USE_DEVICE_analog_joystick)
#    include "modules/analog_joystick.h"
#endif

monkeypad_status_t monkeypad_status = {
    .trackball_mode = BALL_MOUSE_MODE,
    .joystick_mode  = JOYSTICK_MOUSE_MODE
};

#ifdef POINTING_DEVICE_ENABLE
static monkeypad_config_t monkeypad_config = {0};
#endif

#ifndef SCROLL_DIVISOR_H
#    define SCROLL_DIVISOR_H 100.0
#endif
#ifndef SCROLL_DIVISOR_V
#    define SCROLL_DIVISOR_V 50.0
#endif

#ifndef DPI_OPTIONS
#    define DPI_OPTIONS \
        { 100, 200, 300, 400, 500, 600, 800, 1000, 1500, 2000 } //pmw3389
        // { 200, 400, 600, 800, 1000, 1600, 2000, 3000, 4000 } //pmw3360
#    define DPI_DEFAULT 4
#endif

uint16_t dpi_array[] = DPI_OPTIONS;
#define DPI_OPTION_SIZE ARRAY_SIZE(dpi_array)

uint8_t monkeypad_get_trackball_mode(void) {
    return monkeypad_status.trackball_mode;
}

void monkeypad_set_trackball_mode(uint8_t mode) {
    if (mode != monkeypad_status.trackball_mode) {
        monkeypad_status.trackball_mode_changed = timer_read32();
    }
    monkeypad_status.trackball_mode = mode;
}

uint8_t monkeypad_get_joystick_mode(void) {
    return monkeypad_status.joystick_mode;
}

void monkeypad_set_joystick_mode(uint8_t mode) {
    if (mode != monkeypad_status.joystick_mode) {
        monkeypad_status.joystick_mode_changed = timer_read32();
    }
    monkeypad_status.joystick_mode = mode;
}

void keyboard_post_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    monkeypad_config.dpi_config = DPI_DEFAULT;

    pointing_device_set_cpi(dpi_array[monkeypad_config.dpi_config]);
#endif
    keyboard_post_init_user();
}

void pointing_device_driver_init(void) {
#ifdef USE_DEVICE_analog_joystick
    analog_joystick_init();
#endif
}

/* Analog joystick function */
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
#ifdef USE_DEVICE_analog_joystick
    /* Align orientation with other pointing devices */
    mouse_report        = analog_joystick_get_report(mouse_report);
    mouse_xy_report_t x = mouse_report.x;
    mouse_xy_report_t y = mouse_report.y;
    mouse_report.x      = -y;
    mouse_report.y      = x;
#endif
    return (mouse_report);
}

/*  do nothing when analog_joystick used */
uint16_t pointing_device_driver_get_cpi(void) {
    uint16_t cpi = 0;
    return (cpi);
}
void pointing_device_driver_set_cpi(uint16_t cpi) {}

void pointing_device_set_split_cpi(uint16_t cpi) {
// Redundant description because "pointing_device_set_cpi_on_side()" in pointing_device.c does not work properly when it has a pointing device on the right side
#if defined(SPLIT_POINTING_ENABLE)
#    if defined(MODULE_DEVICE_LEFT_pmw3389) && defined(MODULE_DEVICE_RIGHT_pmw3389)
    pointing_device_set_cpi(cpi);
    pointing_device_set_cpi_on_side(true, cpi);
#    elif defined(MODULE_DEVICE_LEFT_pmw3389)
    if (is_keyboard_left()) { // if left
        pointing_device_set_cpi(cpi);
    } else {
#if defined(POINTING_DEVICE_COMBINED)
        pointing_device_set_cpi_on_side(true, cpi);
#else
        pointing_device_set_cpi(cpi);
#endif
    }
#    elif defined(MODULE_DEVICE_RIGHT_pmw3389)
    if (!is_keyboard_left()) { // if right
        pointing_device_set_cpi(cpi);
    } else {
#if defined(POINTING_DEVICE_COMBINED)
        pointing_device_set_cpi_on_side(false, cpi);
#else
        pointing_device_set_cpi(cpi);
#endif
    }
#    endif
#endif
    return;
}

/* Trackball function */
#if defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)
// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t convert_mouse_to_scroll(report_mouse_t mouse_report) {
    // Calculate and accumulate scroll values based on mouse movement and divisors
    scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
    scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR_V;

    // Assign integer parts of accumulated scroll values to the mouse report
#    ifdef TRACKBALL_SCROLL_REVERSE
    mouse_report.h = -(int8_t)scroll_accumulated_h;
    mouse_report.v = -(int8_t)scroll_accumulated_v;
#    else
    mouse_report.h = (int8_t)scroll_accumulated_h;
    mouse_report.v = (int8_t)scroll_accumulated_v;
#    endif

    // Update accumulated scroll values by subtracting the integer parts
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

    // Clear the X and Y values of the mouse report
    mouse_report.x = 0;
    mouse_report.y = 0;

    return mouse_report;
}

#    if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
#        if defined(MODULE_DEVICE_LEFT_pmw3389) || defined(MODULE_DEVICE_RIGHT_pmw3389)
    // Check if drag scrolling is active
    if (monkeypad_get_trackball_mode() == BALL_SCROLL_MODE) {
#            if defined(MODULE_DEVICE_LEFT_pmw3389)
        left_report = convert_mouse_to_scroll(left_report);
#            endif
#            if defined(MODULE_DEVICE_RIGHT_pmw3389)
        right_report = convert_mouse_to_scroll(right_report);
#            endif
    }
#        endif

    return pointing_device_task_combined_user(left_report, right_report);
}

#    elif defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
#        if defined(MODULE_DEVICE_LEFT_pmw3389) || defined(MODULE_DEVICE_RIGHT_pmw3389)
    if (monkeypad_get_trackball_mode() == BALL_SCROLL_MODE) {
        mouse_report = convert_mouse_to_scroll(mouse_report);
    }
#        endif

    return pointing_device_task_user(mouse_report);
}
#    endif
#endif

/* Custom keycodes */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MK_SCROLL:
            if (record->event.pressed) {
                monkeypad_set_trackball_mode(BALL_SCROLL_MODE);
            } else {
                monkeypad_set_trackball_mode(BALL_MOUSE_MODE);
            }
            break;
        case MK_WHEEL:
            if (record->event.pressed) {
                monkeypad_set_joystick_mode(JOYSTICK_WHEEL_MODE);
            } else {
                monkeypad_set_joystick_mode(JOYSTICK_MOUSE_MODE);
            }
            break;
        case MK_ARROW:
            if (record->event.pressed) {
                monkeypad_set_joystick_mode(JOYSTICK_ARROW_MODE);
            } else {
                monkeypad_set_joystick_mode(JOYSTICK_MOUSE_MODE);
            }
            break;
        case MK_PAD:
            if (record->event.pressed) {
                monkeypad_set_joystick_mode(JOYSTICK_GAMEPAD_MODE);
            } else {
                monkeypad_set_joystick_mode(JOYSTICK_MOUSE_MODE);
            }
            break;
#ifdef POINTING_DEVICE_ENABLE
        case DPI_UP:
            if (record->event.pressed) {
                monkeypad_config.dpi_config = (monkeypad_config.dpi_config + 1) < DPI_OPTION_SIZE ? (monkeypad_config.dpi_config + 1) : (DPI_OPTION_SIZE - 1);
                pointing_device_set_split_cpi(dpi_array[monkeypad_config.dpi_config]);
                printf("DPI:%d\n",dpi_array[monkeypad_config.dpi_config]);
            }
            break;
        case DPI_DN:
            if (record->event.pressed) {
                monkeypad_config.dpi_config = (monkeypad_config.dpi_config - 1) < 0 ? 0 : (monkeypad_config.dpi_config - 1);
                pointing_device_set_split_cpi(dpi_array[monkeypad_config.dpi_config]);
                printf("DPI:%d\n",dpi_array[monkeypad_config.dpi_config]);
            }
            break;
        case DPI_RST:
            if (record->event.pressed) {
                monkeypad_config.dpi_config = DPI_DEFAULT;
                pointing_device_set_split_cpi(dpi_array[monkeypad_config.dpi_config]);
                printf("DPI:%d\n",dpi_array[monkeypad_config.dpi_config]);
            }
            break;
        case DPI_FINE:
            // Runs at the slowest speed while the DPI_FINE key is held down.
            if (record->event.pressed) {
                pointing_device_set_cpi(dpi_array[0]);
            } else {
                pointing_device_set_cpi(dpi_array[monkeypad_config.dpi_config]);
            }
            break;
#endif
    }
    return process_record_user(keycode, record);
}
