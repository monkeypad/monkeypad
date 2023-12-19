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

#include QMK_KEYBOARD_H

enum monkeypad_keymap_layers {
    _BASE = 0,
};

#define SCROLL_DIVISOR_H 100.0
#define SCROLL_DIVISOR_V 100.0
/* redefine keycode */
#define KC_L_SPC    LT(_LOWER, KC_SPC)
#define KC_L_BS     LT(_LOWER, KC_BSPC)
#define KC_R_ENT    LT(_RAISE, KC_ENT)
#define KC_A_JA     LALT_T(KC_LNG1)
#define KC_A_EN     LALT_T(KC_LNG2)
#define KC_G_TAB    MT(MOD_LGUI, KC_TAB)

/* layers */
// Last row defines the function of the module
// Encoder:         center: button click, left/right: encoder rotation,
// Analog joystick: center: button click, left/right: ignored
// Trackball:       center & left/right: ignored
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
   ┌─────────────────────┐
   │     _BASE/_L0       │                                  ╭╮╭╮╭╮╭╮                       ╭╮╭╮╭╮╭╮╭╮                      ╭╮╭╮╭╮╭╮
   └─────────────────────┘                                  │╰╯╰╯╰╯│                       │╰╯╰╯╰╯╰╯│                      │╰╯╰╯╰╯│
   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐┌─────────────────────────────┐ ┌─────────────────────────────┐┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
   │   ESC   │    W    │    W    │    E    │    R    │    T    ││                             │ │                             ││    Y    │    W    │    U    │    I    │    O    │   BSPC  │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤│                             │ │                             │├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   TAB   │    A    │    S    │    D    │    F    │    G    ││    Left hand main board     │ │   Right hand main board     ││    H    │    J    │    K    │    L    │    ;    │    '    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤│                             │ │                             │├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │  SHIFT  │    Z    │    X    │    C    │    V    │    B    ││      Left hand module       │ │      Right hand module      ││    N    │    M    │    ,    │    .    │    /    │    ;    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭─────────┬─────────┬─────────╮ ╭─────────┬─────────┬─────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   _L4   │  CTRL   │   GUI   │ ALT/EN  │ _L2/ENT │ _L1/SPC ││ KC_WH_D │ KC_BTN3 │ KC_WH_U │ │ KC_WH_D │ KC_BTN3 │ KC_WH_U ││ _L1/SPC │ _L2/ENT │ ALT/JA  │   GUI   │  CTRL   │   _L3   │
   └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘╰─────────┴─────────┴─────────┘ ╰─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
                     Left hand sub board keys                   │    Left hand main keys      / \      Right hand main keys   │                 Right hand sub board keys
                                                                │   ╭─────────┬─────────╮    /   \    ╭─────────┬─────────╮   │
                                                                │   │   ESC   │   TAB   │   /     \   │   ESC   │   TAB   │   │
                                                                │   └─────────┴─────────┘  /       \  └─────────┴─────────┘   │
                                                                ╰─────────────────────────┘         ╰─────────────────────────┘
*/
  [_BASE] = LAYOUT_module(
//  Left hand sub board keys                                                    Right hand sub board keys
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_A,       KC_B,
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_A,       KC_B,
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_A,       KC_B,
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_A,       KC_B,
//                                                  Left hand main keys         Right hand main keys
                                                    KC_C,       KC_D,           KC_E,       KC_F,
//                                                  Left hand module            Right hand module
                                        KC_WH_D,    KC_G,       KC_WH_U,        KC_WH_D,    KC_G,    KC_WH_U
  ),
};

/* Encoder Setting Get keycodes from the last row */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    if (index == 0) { // left encoder
        wait_us(10);
        if (clockwise) {
            key.row = 5, key.col = 5;
        } else {
            key.row = 5, key.col = 4;
        }
        tap_code(keymap_key_to_keycode(layer_switch_get_layer(key), key));
    } else if (index == 1) { // right encoder
        wait_us(10);
        if (clockwise) {
            key.row = 11, key.col = 5;
        } else {
            key.row = 11, key.col = 4;
        }
        tap_code(keymap_key_to_keycode(layer_switch_get_layer(key), key));
    }
    return false;
}
#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL+1);
}
#endif
