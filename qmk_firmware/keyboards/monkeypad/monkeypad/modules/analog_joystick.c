/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2023 ozsan <monkeypad39@gmail.com>
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


#include QMK_KEYBOARD_H
#include "analog.h"
#include "quantum.h"
#include "analog_joystick.h"

#if defined(USE_DEVICE_analog_joystick)

// This key codes are supposed to be changed by the user.
#define JOY_UP KC_1
#define JOY_DOWN KC_2
#define JOY_LEFT KC_3
#define JOY_RIGHT KC_4

// Set Parameters
uint16_t minAxisValue   = ANALOG_JOYSTICK_AXIS_MIN;
uint16_t maxAxisValue   = ANALOG_JOYSTICK_AXIS_MAX;
uint8_t  maxCursorSpeed = ANALOG_JOYSTICK_SPEED_MAX;
uint8_t  speedRegulator = ANALOG_JOYSTICK_SPEED_REGULATOR; // Lower Values Create Faster Movement
int16_t  xOrigin, yOrigin;
uint16_t lastCursor = 0;
extern monkeypad_status_t monkeypad_status;

int16_t axisCoordinate(pin_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed) {
    int16_t      coordinate = axisCoordinate(pin, origin);
    if (coordinate != 0) {
        float percent = (float)coordinate / 100;
        return percent * maxCursorSpeed * (abs(coordinate) / speedRegulator);
    } else {
        return 0;
    }
}

int16_t ajustCoordinate(int16_t coordinate) {
    if (!is_keyboard_left()) { // if right
        return (-coordinate);
    } else {
        return (coordinate);
    }
}

void axisToWheelComponent(uint8_t pin, int16_t origin, bool xy) {
    int16_t      coordinate = axisCoordinate(pin, origin);
                 coordinate = ajustCoordinate(coordinate);
#    ifdef JOYSTICK_WHEEL_REVERSE
                 coordinate = - coordinate;
#    endif
    float        percent    = (float)coordinate / 100;
    static float threshold  = 0.5;
    static bool  arrows[4];
    if (xy == 0) // x coordinate
    {
        if (percent > threshold) {
            if (!arrows[0]) {
                arrows[0] = true;
                register_code16(KC_WH_R);
            }
        } else {
            if (arrows[0]) {
                arrows[0] = false;
            }
            unregister_code16(KC_WH_R);
        }
        if (percent < -threshold) {
            if (!arrows[1]) {
                arrows[1] = true;
                register_code16(KC_WH_L);
            }
        } else {
            if (arrows[1]) {
                arrows[1] = false;
            }
            unregister_code16(KC_WH_L);
        }
    } else { // y coordinate
        if (percent > threshold) {
            if (!arrows[2]) {
                arrows[2] = true;
                register_code16(KC_WH_U);
            }
        } else {
            if (arrows[2]) {
                arrows[2] = false;
            }
            unregister_code16(KC_WH_U);
        }
        if (percent < -threshold) {
            if (!arrows[3]) {
                arrows[3] = true;
                register_code16(KC_WH_D);
            }
        } else {
            if (arrows[3]) {
                arrows[3] = false;
            }
            unregister_code16(KC_WH_D);
        }
    }
}

void axisToArrowComponent(uint8_t pin, int16_t origin, bool xy) {
    int16_t      coordinate = axisCoordinate(pin, origin);
                 coordinate = ajustCoordinate(coordinate);
    float        percent    = (float)coordinate / 100;
    static float threshold  = 0.5;
    static bool  arrows[4];
    if (xy == 0) // x coordinate
    {
        if (percent > threshold) {
            if (!arrows[0]) {
                arrows[0] = true;
                register_code16(KC_RIGHT);
            }
        } else {
            if (arrows[0]) {
                arrows[0] = false;
            }
            unregister_code16(KC_RIGHT);
        }
        if (percent < -threshold) {
            if (!arrows[1]) {
                arrows[1] = true;
                register_code16(KC_LEFT);
            }
        } else {
            if (arrows[1]) {
                arrows[1] = false;
            }
            unregister_code16(KC_LEFT);
        }
    } else { // y coordinate
        if (percent > threshold) {
            if (!arrows[2]) {
                arrows[2] = true;
                register_code16(KC_UP);
            }
        } else {
            if (arrows[2]) {
                arrows[2] = false;
            }
            unregister_code16(KC_UP);
        }
        if (percent < -threshold) {
            if (!arrows[3]) {
                arrows[3] = true;
                register_code16(KC_DOWN);
            }
        } else {
            if (arrows[3]) {
                arrows[3] = false;
            }
            unregister_code16(KC_DOWN);
        }
    }
}

void axisToGamePadComponent(uint8_t pin, int16_t origin, bool xy) {
    int          coordinate = axisCoordinate(pin, origin);
                 coordinate = ajustCoordinate(coordinate);
    float        percent    = (float)coordinate / 100;
    static float threshold  = 0.5;
    static bool  arrows[4];
    if (xy == 0) // x coordinate
    {
        if (percent > threshold) {
            if (!arrows[0]) {
                arrows[0] = true;
                register_code16(KC_D);
            }
        } else {
            if (arrows[0]) {
                arrows[0] = false;
            }
            unregister_code16(KC_D);
        }
        if (percent < -threshold) {
            if (!arrows[1]) {
                arrows[1] = true;
                register_code16(KC_A);
            }
        } else {
            if (arrows[1]) {
                arrows[1] = false;
            }
            unregister_code16(KC_A);
        }
    } else { // y coordinate
        if (percent > threshold) {
            if (!arrows[2]) {
                arrows[2] = true;
                register_code16(KC_W);
            }
        } else {
            if (arrows[2]) {
                arrows[2] = false;
            }
            unregister_code16(KC_W);
        }
        if (percent < -threshold) {
            if (!arrows[3]) {
                arrows[3] = true;
                register_code16(KC_S);
            }
        } else {
            if (arrows[3]) {
                arrows[3] = false;
            }
            unregister_code16(KC_S);
        }
    }
}

void axisToCustomKeycodes(uint8_t pin, int16_t origin, bool xy) {
    int16_t      coordinate = axisCoordinate(pin, origin);
                 coordinate = ajustCoordinate(coordinate);
    float        percent    = (float)coordinate / 100;
    static float threshold  = 0.5;
    static bool  arrows[4];
    if (xy == 0) // x coordinate
    {
        if (percent > threshold) {
            if (!arrows[0]) {
                arrows[0] = true;
                register_code16(JOY_RIGHT);
            }
        } else {
            if (arrows[0]) {
                arrows[0] = false;
            }
            unregister_code16(JOY_RIGHT);
        }
        if (percent < -threshold) {
            if (!arrows[1]) {
                arrows[1] = true;
                register_code16(JOY_LEFT);
            }
        } else {
            if (arrows[1]) {
                arrows[1] = false;
            }
            unregister_code16(JOY_LEFT);
        }
    } else { // y coordinate
        if (percent > threshold) {
            if (!arrows[2]) {
                arrows[2] = true;
                register_code16(JOY_UP);
            }
        } else {
            if (arrows[2]) {
                arrows[2] = false;
            }
            unregister_code16(JOY_UP);
        }
        if (percent < -threshold) {
            if (!arrows[3]) {
                arrows[3] = true;
                register_code16(JOY_DOWN);
            }
        } else {
            if (arrows[3]) {
                arrows[3] = false;
            }
            unregister_code16(JOY_DOWN);
        }
    }
}

report_analog_joystick_t analog_joystick_read(void) {
    static report_analog_joystick_t report = {0};
    switch (monkeypad_status.joystick_mode) {
        case JOYSTICK_MOUSE_MODE:
            if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
                lastCursor = timer_read();
                report.x   = axisToMouseComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, maxCursorSpeed);
                report.y   = axisToMouseComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, maxCursorSpeed);
            }
            break;
        case JOYSTICK_WHEEL_MODE:
            // arrows
            if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
                lastCursor = timer_read();
                axisToWheelComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, 0);
                axisToWheelComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, 1);
            }
            break;
        case JOYSTICK_ARROW_MODE:
            // arrows
            if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
                lastCursor = timer_read();
                axisToArrowComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, 0);
                axisToArrowComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, 1);
            }
            break;
        case JOYSTICK_GAME_MODE: // gamepad
            if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
                lastCursor = timer_read();
                axisToGamePadComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, 0);
                axisToGamePadComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, 1);
            }
            break;
        case JOYSTICK_CUSTOM_MODE: // gamepad
            if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
                lastCursor = timer_read();
                axisToCustomKeycodes(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, 0);
                axisToCustomKeycodes(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, 1);
            }
            break;
    }
#    ifdef ANALOG_JOYSTICK_CLICK_PIN
    report.button = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
#    endif
    return report;
}

void analog_joystick_init(void) {
#    ifdef ANALOG_JOYSTICK_CLICK_PIN
    setPinInputHigh(ANALOG_JOYSTICK_CLICK_PIN);
#    endif
    // Account for drift
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
}

report_mouse_t analog_joystick_get_report(report_mouse_t mouse_report) {
    report_analog_joystick_t data = analog_joystick_read();

    mouse_report.x = - data.x;
    mouse_report.y = data.y;

    mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, data.button, POINTING_DEVICE_BUTTON1);
    return mouse_report;
}

#endif
