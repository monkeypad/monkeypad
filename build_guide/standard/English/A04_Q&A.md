<!-- ### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)  -->

### Q&A

If your Monkeypad is not functioning correctly, please check the following:

- **Raspberry Pi Pico is not recognized by the PC.**
  
  - If none of the functions on the main board and modules are working, there might be an issue with the power system. Disconnect the sub-board and the TRRS cables between the left and right sides, then perform operation checks individually.
  
  - Use the `flash_nuke.uf2` file from the [Raspberry Pi official documentation](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) to restore the Raspberry Pi Pico to its factory settings.

- **Specific keys do not respond.**
  
  - **Check diode orientation:** Ensure that the diodes are oriented correctly.
  
  - **Verify key socket soldering:** Make sure that the key sockets are properly soldered. Use pliers or tweezers to gently touch them and confirm that the sockets are not floating.
  
  - **Inspect key switch pins:** Check if any of the key switch pins are bent.
  
  - **Ensure secure mounting:** Confirm that the PCB and top plate are securely fixed.

- **Only the sub-board's keys do not respond.**
  
  - **Check TRRS cable connections:** Ensure that the TRRS cables between the main and sub boards are fully inserted.
  
  - **Verify correct TRRS port usage:** Make sure you haven't inserted the TRRS cables into the wrong ports.
  
  - **Avoid PCB and top plate interference:** Ensure that the PCB and top plate are not interfering with each other by trimming any excess cable length with wire cutters.
  
  - **Confirm resistor values:** Verify that the resistor values are correct.
  
  - **Use a multimeter:** If you have a multimeter, check the connection between the main and sub boards. Confirm that you can measure a voltage around **3.3V**.

- **Keys on the board without USB connected do not respond.**
  
  - **Test each side individually:** Connect each side one by one and verify if each key switch is functioning.
  
  - **Ensure TRRS cable insertion:** Make sure that the TRRS cables for communication between the left and right Raspberry Pi Picos are fully inserted.
  
  - **Check connections with a multimeter:** Use a multimeter to verify the connections.

- **LED does not light up.** *(If other functions are working properly)*
  
  - **Verify LED orientation:** Ensure that the LED is oriented correctly.
  
  - **Check sub-board power:** Confirm that there is no power failure on the sub-board side. Temporarily disconnect the sub-board and check if other functions are working.
  
  - **Review LED settings:** Check if you accidentally pressed a key that changed the LED settings (e.g., pressing the LED off button).

- **Board without USB connected does not work.**
  
  - **Ensure TRRS cable insertion:** Confirm that the TRRS cables for communication between the left and right Raspberry Pi Picos are fully inserted.
  
  - **Test each side separately:** Connect each side to the PC one by one and perform operation checks.
  
  - **Use a multimeter:** Verify the connections using a multimeter.

- **Custom keycodes for analog joystick do not respond.**
  
  - **Check USB connection:** Only the side with the analog joystick is functional. Ensure that the USB is connected properly.

- **Analog joystick movement is slow.**
  
  - **USB connection:** If the Pico is not connected to the PC via USB, it is designed to be slower. Ensure that the USB is connected.
  
  - **Adjust speed settings:** If it still feels slow, modify the build parameters in `analog_joystick.c` within Remap to set your preferred speed and create custom firmware.

- **Mouse cursor drifts/moves on its own.**
  
  - **Joystick calibration:** If a joystick is installed, it reads the initial position as the starting point upon boot. Avoid touching the joystick and press the reset button, or reconnect the USB cable to reboot.
  
  - **Verify firmware:** If you are not using a joystick module, ensure that the correct firmware is flashed.

- **Trackball movement is slow.**
  
  - **USB connection:** If the Pico is not connected to the PC via USB, it is designed to be slower. Ensure that the USB is connected.
  
  - **Adjust DPI settings:** The trackball can change speed using DPI values via key presses. On Layer (3) Fn Layer, press the custom keys {DPI_UP (increase speed), DPI_DN (decrease speed), DPI_RST (reset)} to adjust the trackball movement. Refer to the [Default Keymap](../images/keymap_cheatsheet_monkeypad.pdf).

  - **Customize firmware:** You can also change the DPI range and default value in Remap's `monkeypad.c` build parameters to create custom firmware.

- **Mouse cursor lags/skips.**
  
  - **Limit USB connections:** Connecting both left and right Picos to the PC via USB causes delays as they attempt to communicate. Connect only one side to the PC and connect the other side via TRRS cable.
  
  - **Firmware considerations:** Similarly, flashing firmware for a split keyboard may cause cursor skipping when used with one hand. Ensure proper firmware settings.

- **Trackball does not respond or responds poorly.**
  
  - **Check lens attachment:** Ensure that the lens is properly attached.
  
  - **Verify sensor orientation:** Confirm that the sensor is oriented correctly.
  
  - **Adjust sensor distance:** The distance between the ball and sensor should be correctly set horizontally. Ensure that mounting screws are properly tightened and that the lens is not floating or attached at an angle, as this can prevent the sensor from accurately recognizing movements.
  
  - **Secure the lens:** Try fixing the lens from the backside with masking tape to prevent movement, or test the sensor by mounting only the sensor without the trackball cover.
