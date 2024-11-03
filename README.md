# Monkeypad

![Monkeypad](./build_guide/standard/images/01/monkeypad_1_00.jpeg)

Monkeypad is a customizable mechanical keyboard designed for enthusiasts seeking a personalized typing experience. This repository contains the QMK firmware for Monkeypad, a split keyboard featuring a detachable modular trackball, analog joystick, and encoder. It has a tenting structure and can be angled to fit your hand.

## Where to Buy

[Yushakobo](https://shop.yushakobo.jp/products/8411)
[Booth](https://monkeypad.booth.pm/)


## Build Guide

*   Monkeypad(4x6):
    [日本語/Japanese](./build_guide/standard/01_ビルドガイド.md)

    English version is being prepared.

## Firmware

See [document for firmware source code](./qmk_firmware/keyboards/monkeypad/monkeypad/4x6/readme.md).

### Pre-compiled Firmwares

The file name means the following:

{No}_{keyboard}_{model}_{left_module}_{right_module}_{LEFT HAND or RIGH HAND}_{keymap}.uf2

For the following combinations, flash the same firmware for both sides.

|No.|LEFT|RIGHT| *.uf2 |
|:----|:----|:----|:----|
|1|Trackball|Trackball|[1_mp_mk1_trackball_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/1_mp_mk1_trackball_via.uf2)|
|2|Analog Joystick|Analog Joystick|[2_mp_mk1_joystick_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/2_mp_mk1_joystick_via.uf2)|
|3|Encoder|Encoder|[3_mp_mk1_encoder_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/3_mp_mk1_encoder_via.uf2)|
|4|Trackpad|Trackpad|[4_mp_mk1_trackpad_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/4_mp_mk1_trackpad_via.uf2)|
|5|Encoder|Trackball|[5_mp_mk1_left_encoder_right_trackball_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/5_mp_mk1_left_encoder_right_trackball_via.uf2)|
|6|Encoder|Analog Joystick|[6_mp_mk1_left_encoder_right_joystick_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/6_mp_mk1_left_encoder_right_joystick_via.uf2)|
|7|Encoder|Trackpad|[7_mp_mk1_left_encoder_right_trackpad_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/7_mp_mk1_left_encoder_right_trackpad_via.uf2)|
|8|Trackball|Encoder|[8_mp_mk1_left_trackball_right_encoder_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/8_mp_mk1_left_trackball_right_encoder_via.uf2)|
|9|Analog Joystick|Encoder|[9_mp_mk1_left_joystick_right_encoder_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/9_mp_mk1_left_joystick_right_encoder_via.uf2)|
|10|Trackpad|Encoder|[10_mp_mk1_left_trackpad_right_encoder_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/10_mp_mk1_left_trackpad_right_encoder_via.uf2)|

If the pointing devices on the left and right are different, flash different firmware on each side.

|No.|LEFT|RIGHT|left *.uf2|right *.uf2|
|:----|:----|:----|:----|:----|
|11|Analog Joystick|Trackball|[11_mp_mk1_left_joystick_right_trackball_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/11_mp_mk1_left_joystick_right_trackball_LEFT_via.uf2)|[11_mp_mk1_left_joystick_right_trackball_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/11_mp_mk1_left_joystick_right_trackball_RIGHT_via.uf2)|
|12|Analog Joystick|Trackpad|[12_mp_mk1_left_joystick_right_trackpad_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/12_mp_mk1_left_joystick_right_trackpad_LEFT_via.uf2)|[12_mp_mk1_left_joystick_right_trackpad_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/12_mp_mk1_left_joystick_right_trackpad_RIGHT_via.uf2)|
|13|Trackball|Analog Joystick|[13_mp_mk1_left_trackball_right_joystick_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/13_mp_mk1_left_trackball_right_joystick_LEFT_via.uf2)|[13_mp_mk1_left_trackball_right_joystick_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/13_mp_mk1_left_trackball_right_joystick_RIGHT_via.uf2)|
|14|Trackpad|Analog Joystick|[14_mp_mk1_left_trackpad_right_joystick_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/14_mp_mk1_left_trackpad_right_joystick_LEFT_via.uf2)|[14_mp_mk1_left_trackpad_right_joystick_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/14_mp_mk1_left_trackpad_right_joystick_RIGHT_via.uf2)|
|15|Trackpad|Trackball|[15_mp_mk1_left_trackpad_right_trackball_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/15_mp_mk1_left_trackpad_right_trackball_LEFT_via.uf2)|[15_mp_mk1_left_trackpad_right_trackball_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/15_mp_mk1_left_trackpad_right_trackball_RIGHT_via.uf2)|
|16|Trackball|Trackpad|[16_mp_mk1_left_trackball_right_trackpad_LEFT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/16_mp_mk1_left_trackball_right_trackpad_LEFT_via.uf2)|[16_mp_mk1_left_trackball_right_trackpad_RIGHT_via.uf2](https://github.com/monkeypad/monkeypad/releases/download/v0.2.0/16_mp_mk1_left_trackball_right_trackpad_RIGHT_via.uf2)|
