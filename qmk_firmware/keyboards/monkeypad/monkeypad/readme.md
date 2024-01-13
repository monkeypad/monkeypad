# Monkeypad QMK Firmware

![Monkeypad](https://github.com/monkeypad/monkeypad/blob/main/build_guide/standard/images/01/monkeypad_1_00.jpeg)

## Introduction

Monkeypad is a customizable mechanical keyboard designed for enthusiasts seeking a personalized typing experience. This repository contains the QMK firmware for Monkeypad, empowering users to program and configure their keyboards according to their preferences.

## Features

- Interchangeable modules for trackball, joystick, and encoder
- User-adjustable tenting structure
- Stylish aluminum plate for a split keyboard design
- Expansion ports for additional functionalities

## Getting Started

If you're assembling and customizing keymaps for the first time, Monkeypad supports VIA, enabling users to utilize most features without setting up a local development environment. For detailed customization, follow the steps below:

### Prerequisites

Before you begin, ensure you have the following installed:
If you are building a QMK environment for the first time, please follow the official QMK instructions to build the QMK build environment.

Currently, Monkeypad firmwares are verified to compile with QMK 0.23.1.

### QMK Installation

- [English Instructions](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_getting_started.md)
- [Japanese Instructions](https://github.com/qmk/qmk_firmware/blob/master/docs/ja/newbs_getting_started.md)

### Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/monkeypad/monkeypad.git

Open the QMK the Monkeypad firmware.

Customize your keymap in the keymaps directory.

Configuration
Monkeypad's QMK firmware can be configured to meet your specific needs. Refer to the following sections for customization options:

2. Compile the firmware

```bash
qmk compile -kb monkeypad/monkeypad/4x6/mk1 -km default
or
qmk compile -kb monkeypad/monkeypad/4x6/mk1 -km via
```
The firmware file follows this naming format:
monkeypad_monkeypad_<model_name>_<keymap_name>.{bin,uf2}

3. Flash the firmware to your Monkeypad.
Once the firmware has been prepared, the last step is to flash the firmware to the MCUs.

Put Your Keyboard into DFU (Bootloader) Mode

Quickly press the Reset button twice on the PCB board connected to the Raspberry Pi Pico, making sure the RP2040 reboots in DFU mode and is recognized as a USB storage drive.

Enter the bootloader using any of the following methods:
Double-tap the RESET button on the main PCB (or Hold the BOOTSEL button on the PCB while plugin in the usb cable).
Wait for the OS to detect the device
Copy the `monkeypad_monkeypad_4x6_mk1_<keymap_name>.uf2` file by dragging and dropping them to the new USB disk.

4. Compile & flash the firmware
Other methods include the following
you have multiple keyboards, you can specify the keyboard and keymap:

You can also compile and flash by specifying a keyboard and keymap and typing the following command to flash via CLI eg. 

```bash
qmk flash -kb monkeypad/monkeypad/4x6/mk1 -km default
or
qmk flash -kb monkeypad/monkeypad/4x6/mk1 -km via
```

Then it will be in write standby, and when the user presses the reset button on the PCB twice, it will reboot as DFU mode and the flash will be completed.

5. Test It Out!
Congrats! Your custom firmware has been programmed to your keyboard and you're ready to test it out!

## Where to Buy

Opening soon (*Note: Hardware not yet available; stay tuned for updates*)

* Available
    * Monkeypad
* Modules
    * Trackball (PMW3389)
    * Analog joystick
    * Encoder
    * ... under development

## Customizing the Firmware

Monkeypad offers a range of customizable features to tailor your keyboard experience. Explore the following options to personalize your keyboard to suit your preferences.

See the readme.md for further information of [source code](4x6/readme.md). 
