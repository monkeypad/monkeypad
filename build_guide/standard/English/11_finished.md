<!-- ### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)  -->

  - [11. 11. Finished!](11_finished.md)
    - [11-1. Writing the Firmware](./11_finished.md/#11-1Writing the Firmware)
    - [11-2. Testing](./11_finished.md/#11-2Testing)

### 11-1. Writing the Firmware

Choose and install the left and right modules in any combination you prefer.

*Note:* If you want to secure the modules firmly so they do not move, you can also fix them using M3 self-tapping screws. *(If you want the modules to be replaceable, do not use screws.)*

Write the firmware.

To use Remap, please flash the following VIA-compatible firmware.

As mentioned in [9_Preliminary_Test](09_Preliminary_Test.md), pressing the Reset button (tact switch) installed on the PCB of the Raspberry Pi Pico twice quickly will boot it into DFU mode, allowing you to write programs. After assembly, press the tact switch on the backside twice using a thin rod or similar tool.

**Important:** The Monkeypad allows users to swap modules at any time according to their applications and needs. However, the program does not have a function to automatically recognize and switch the installed modules. Depending on your left and right modules, download and flash the following files.

The file names mean the following:

`{No}_{keyboard}_{model}_{left_module}_{right_module}_{LEFT_HAND or RIGHT_HAND}_{keymap}.uf2`

If the pointing devices on both sides are the same, or if an encoder is used on either side, flash the same firmware on both left and right.

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

### 11-2. Testing

**Good job!** If some features do not work as expected, let's troubleshoot by referring to the Q&A section.

Once all functions are operating correctly, the build is complete. Congratulations!!