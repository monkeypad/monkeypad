# Monkeypad (4x6)

Monkeypad is a split keyboard featuring a detachable modular trackball, analog joystick, and encoder. It has a tenting structure and can be angled to fit the human hand. 

## Connecting the Keyboards
It has 4 PCB boards and 2 modules, a main and sub board for each of the left and right sides. The main and sub communicate via I2C, the left and right MCUs communicates with UART communication. one of the MCUs communicates with the PC via USB.

**Important:** Avoid connecting each left and right MCU directly to the PC using USB cables, as this may cause delays, making it difficult to move the pointing device accurately. For optimal performance, it is highly recommended to use a TRRS cable to connect the left and right components.

-   Keyboard Maintainer: [ozsan](https://github.com/monkeypad)
-   Hardware Supported: Raspberry Pi Pico / Raspberry Pi Pico W
-   Hardware Availability: [monkeypad](*Note: Hardware not yet available; stay tuned for updates*)

## Building the firmware

**Important:** Ensure you specify the modules in `rules.mk` before compiling the firmware when swapping modules for different applications or uses.

```c
MODULE_DEVICE_LEFT = {analog_joystick / pmw3389 / encoder}
MODULE_DEVICE_RIGHT = {analog_joystick / pmw3389 / encoder}
```
QMK (version: 0.23.0) currently does not support multiple different pointing device sensor types. If using different pointing devices for left and right (analog_joystick / pmw3389), you need separate firmware for each side, requiring you to compile twice. When using encoders, the firmware remains the same for left and right.

Please select the TARGET_POINTING_DEVICE

```c
TARGET_POINTING_DEVICE = {analog_joystick / pmw3389}
```
The command is:

```shell
qmk compile -kb monkeypad/monkeypad/{MODEL}/{VERSION} -km {KEYMAP}

```
Check out the via layout if you're looking for VIA support.

| Version | default                                                         | via                                                         |
| -------------- | --------------------------------------------------------------- | ----------------------------------------------------------- |
| Mk1            | `qmk compile -kb monkeypad/monkeypad/4x6/mk1 -km default` | `qmk compile -kb monkeypad/monkeypad/4x6/mk1 -km via` |

### Trackball Drag-scroll
Enable scrolling with the trackball or analog-joystick using drag-scroll. When enabled, mouse_report `x` and `y` movements convert into `h` (horizontal) and `v` (vertical) movement.
Connect the USB to either the left or right MCU to utilize the drag-scroll function.

Call `monkeypad_set_trackball_mode(mode)` to enable/disable drag-scroll for the trackball.

To invert the scrolling direction (i.e., mimic macOS "natural" scroll direction), define `TRACKBALL_SCROLL_REVERSE` in `config.h`

```c
#define TRACKBALL_SCROLL_REVERSE
```

### Analog Joystick Keycode
To change the function of the Analog Joystick, connect the USB to the joystick side. If connected to the opposite side of the split keyboard, this mode will not work.

Call `monkeypad_set_joystick_mode(mode)` to change the function of analog joystick.

The default settings allow for the following:

| Mode           | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| JOYSTICK_MOUSE_MODE | Functions as a mouse, mode controlling the mouse cursor. |
| JOYSTICK_WHEEL_MODE | Sends Wheel Up (KC_WH_U), Down (KC_WH_D), Left (KC_WH_L), and Right (KC_WH_R) key codes of the wheel. |
| JOYSTICK_ARROW_MODE | Sends Up (KC_UP), Down (KC_DOWN), Left (KC_LEFT), and Right (KC_RIGHT) key codes. |
| JOYSTICK_GAMEPAD_MODE | Sends the W (KC_W), A (KC_A), S (KC_S), and D (KC_D) key codes used in games. |

To invert the scrolling direction when using JOYSTICK_WHEEL_MODE, define `JOYSTICK_WHEEL_REVERSE` in `config.h`

```c
#define JOYSTICK_WHEEL_REVERSE
```

### Custom Keycode
Use the following keycodes to change the trackball, joystick mode
| Keycode        | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| MK_SCROLL | Change the trackball to drag scroll mode |
| MK_WHEEL | Change the analog joystick to wheel scroll mode | 
| MK_ARROW | Change the analog joystick to arrow('←↑↓→') mode | 
| MK_PAD | Change the analog joystic to game('wasd') mode | 

Drag Scroll Configuration
Dynamic DPI scaling
DPI range is { 200, 400, 600, 800, 1200, 1600, 2400, 3200, 4000 }. Default to 600 DPI
| Keycode        | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| DPI_UP | Increases the DPI |
| DPI_DN | Decreases the DPI | 
| DPI_RST | Reset the DPI value (default:600) | 
| DPI_FINE | DPI is set to the lowest value (200) while the key is held down | 
