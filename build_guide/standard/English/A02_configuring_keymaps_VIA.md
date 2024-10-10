- [A02. Changing the Keymap (VIA)](A02_Changing_Keymap_VIA.md)
  - [A02-1. Changing the Keymap (VIA)](#A02-1VIA-Configuration-File)
  - [A02-2. Custom Keycodes](#A02-2Custom-Keycodes)

### A02-1.VIA Configuration File

To set up the keymap, download the VIA configuration file below.

[Download JSON file](https://github.com/monkeypad/monkeypad/releases/download/v0.1.0/Monkeypad_Mk1.json)

Go to the VIA website.
[VIA](https://www.caniusevia.com/)

Start VIA by clicking `Start Now` at the bottom left of the top page.

Connect your keyboard via USB. When `Searching for devices…` appears in the Configure tab, go to the Settings tab and toggle on `Show Design tab`.

In the Design tab, click the `Load Draft Definition` button and load the downloaded JSON file.

Return to the Configure tab, and your keyboard will be recognized, allowing you to use VIA.

### A02-2.Custom Keycodes

Change the modes of the trackball and joystick.

| Keycode        | Description                                                |
| -------------- | ---------------------------------------------------------- |
| MK_SCROLL      | Sets the trackball to scroll mode                          |
| MK_WHEEL       | Sets the joystick to wheel scroll mode                     | 
| MK_ARROW       | Sets the joystick to arrow keys mode ('←↑↓→')              | 
| MK_PAD         | Sets the joystick to WASD keys mode ('WASD')               | 

These are the settings for mouse and scroll DPI values.
DPI value range: {100, 200, 300, 400, 500, 600, 800, 1000, 1500, 2000}. The default value is **500 DPI**.

| Keycode    | Description                                                    |
| ---------- | -------------------------------------------------------------- |
| DPI_UP     | Increases the DPI                                              |
| DPI_DN     | Decreases the DPI                                              | 
| DPI_RST    | Resets the DPI to the default value (default: 500)             | 
| DPI_FINE   | Sets the DPI to the minimum (100) while the key is pressed     | 
