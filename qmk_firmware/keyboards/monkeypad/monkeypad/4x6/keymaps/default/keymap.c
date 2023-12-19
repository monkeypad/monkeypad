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
    _LOWER,
    _RAISE,
    _FUNC,
    _GAME
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
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,           KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    KC_G_TAB,   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,           KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
    TG(_GAME),  KC_LCTL,    KC_LGUI,    KC_A_EN,    KC_R_ENT,   KC_L_SPC,       KC_L_SPC,   KC_R_ENT,   KC_A_JA,    KC_RALT,    KC_RCTL,    TG(_FUNC),
//                                                  Left hand main keys         Right hand main keys
                                                    KC_BTN1,    KC_BTN2,        KC_BTN1,    KC_BTN2,
//                                                  Left hand module            Right hand module
                                        KC_WH_D,    KC_BTN3,    KC_WH_U,        KC_WH_D,    KC_BTN3,    KC_WH_U
  ),
  [_LOWER] = LAYOUT_module(
    KC_DEL,     KC_HOME,    KC_UP,      KC_PGUP,    KC_LBRC,    KC_RBRC,        _______,    KC_7,       KC_8,       KC_9,       KC_PPLS,    KC_MINS,
    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_LCBR,    KC_RCBR,        _______,    KC_4,       KC_5,       KC_6,       KC_PAST,    KC_PENT,
    _______,    KC_END,     KC_BTN3,    KC_PGDN,    KC_LPRN,    KC_RPRN,        _______,    KC_1,       KC_2,       KC_3,       KC_SLSH,    KC_PEQL,
    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    KC_0,       KC_DOT,     _______,    _______,
                                                    _______,    _______,        _______,    _______,
                                        KC_DOWN,    _______,    KC_UP,          KC_DOWN,    _______,    KC_UP
  ),
  [_RAISE] = LAYOUT_module(
    KC_GRV,     _______,    KC_WH_U,    _______,    _______,    _______,        _______,    KC_AMPR,    KC_ASTR,    KC_LPRN,    _______,    KC_UNDS,
    KC_TILD,    KC_WH_L,    KC_WH_D,    KC_WH_R,    KC_FIND,    _______,        _______,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_COLN,    KC_DQUO,
    _______,    KC_UNDO,    KC_CUT,     KC_COPY,    KC_PSTE,    _______,        _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_QUES,    KC_BSLS,
    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    KC_RPRN,    KC_LABK,    KC_RABK,    KC_PIPE,
                                                    _______,    _______,        _______,    _______,
                                        KC_LEFT,    _______,    KC_RGHT,        KC_LEFT,    _______,    KC_RGHT
  ),
  [_FUNC] = LAYOUT_module(
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,          KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    KC_BRIU,    KC_MNXT,    KC_VOLU,    XXXXXXX,    DPI_UP,     XXXXXXX,        RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,    RGB_TOG,
    KC_BRID,    KC_MPLY,    KC_VOLD,    XXXXXXX,    DPI_DN,     XXXXXXX,        RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,    XXXXXXX,
    XXXXXXX,    KC_MPRV,    KC_MUTE,    XXXXXXX,    DPI_RST,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TRNS,
                                                    KC_BTN1,    KC_BTN2,        KC_BTN1,    KC_BTN2,
                                        KC_VOLD,    KC_MUTE,    KC_VOLU,        KC_VOLD,    KC_MUTE,    KC_VOLU
  ),
  [_GAME] = LAYOUT_module(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    KC_TRNS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                                                    KC_BTN1,    KC_BTN2,        KC_BTN1,    KC_BTN2,
                                        XXXXXXX,    KC_SPC,     XXXXXXX,        XXXXXXX,    KC_SPC,     XXXXXXX
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

const rgblight_segment_t PROGMEM        base_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_TURQUOISE});
const rgblight_segment_t PROGMEM        lower_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM        raise_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_ORANGE});
const rgblight_segment_t PROGMEM        func_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GREEN});
const rgblight_segment_t PROGMEM        game_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED});
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(base_layer, lower_layer, raise_layer, func_layer, game_layer);

void  keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

/* Change the function of the pointing device for each layer */
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    // If` joystick change mode is used, USB need to be connected to a joystick side.
        case _LOWER:
            monkeypad_set_joystick_mode(JOYSTICK_WHEEL_MODE);
            monkeypad_set_trackball_mode(BALL_SCROLL_MODE);
            break;
        case _RAISE:
            monkeypad_set_joystick_mode(JOYSTICK_ARROW_MODE);
            monkeypad_set_trackball_mode(BALL_MOUSE_MODE);
            break;
        case _GAME:
            monkeypad_set_joystick_mode(JOYSTICK_GAMEPAD_MODE);
            monkeypad_set_trackball_mode(BALL_MOUSE_MODE);
            break;
        default: //  for any other layers, or the default layer
        case _FUNC:
            monkeypad_set_joystick_mode(JOYSTICK_MOUSE_MODE);
            monkeypad_set_trackball_mode(BALL_MOUSE_MODE);
            break;
    }

    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(4, layer_state_cmp(state, _GAME));

    return state;
}

