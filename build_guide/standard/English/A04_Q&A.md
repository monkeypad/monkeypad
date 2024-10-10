<!-- ### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)  -->

### Q&A
うまく動作しない場合、以下を確認してください。
- Raspberry Pi PicoがPCで認識しない。
  - メインボード、モジュールなどの機能が全て動かない場合、電源系での不良が起きている可能性がります。サブボードや左右間のTRRSケーブルを外し、単体で動作チェックを行なってください。

  - Raspberry Pi 公式ページの一番下の flash_nuke.uf2 を使うとRaspberry Pi Picoを工場出荷状態に戻すことができます。
https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

- 特定のキーが反応しない
  - ダイオードの向きはあっているか
  - キーソケットは確実にはんだ付けされているか。爪やピンセットで触ってみてソケットが浮かないか確認しましょう。
  - キースイッチのピンが曲がっていないか
  - 基板とトッププレートがしっかりと固定されているか

- サブボードのキーだけが反応しない
  - メイン、サブ間のTRRSケーブルがしっかりと奥までささっているか
  - TRRSケーブルのさす場所を間違えていないか
  - 基板とトッププレートが干渉していないか（ニッパーで余分な長さをカットしたか）
  - 抵抗の値は間違えていないか
  - テスターをお持ちの場合は、テスターでメインとサブの接続を確認してください。電源3.3V付近の電圧が測定できるかを確認してください。

- USBを接続していないボードのキーが反応しない
  - 片側ずつ繋いでそれぞれのキースイッチが動作するか。
  - Raspberry Pi Picoの左右通信用のTRRSケーブルがしっかりとささっているか。
  - テスターで接続を確認してください。

- LEDが光らない
（他の機能が問題なく動く場合）
  - LEDの向きが間違えていないか
  - サブボード側での電源不良が起きていないか。サブボードを一旦外して他の機能が動くか確認してください。
  - 誤ってキーを押して、LEDの設定が書き変わってしまっていないか。（LEDオフのボタンを押していないか）

- USBを接続していないボード側が動かない
  - Raspberry Pi Picoの左右通信用のTRRSケーブルがしっかりとささっているか確認してください。
  - 片側ずつPCに接続して動作確認をしてみてください。
  - テスターで接続を確認してください。

- アナログジョイスティックのカスタムキーが反応しない
  - アナログジョイスティックが付いている側のみが機能します。USBの接続先を確認してください。

- アナログジョイスティックの動きが遅い
  - PCにUSBで接続していない場合、仕様として遅くなることが確認されています。USBの接続先を確認してください。
  　それでも遅いと感じる場合は、Remapの`analog_joystick.c`のビルドパラメータを変更して好みのスピードを設定し、オリジナルのファームウェアを作成してください。

- マウスカーソルがドリフトする/勝手に動く
  - ジョイスティックを取り付けている場合、起動時の位置を初期状態として読み取ります。ジョイスティックに触れないようにしてリセットボタンを押すか、USBケーブルをつなぎ直して再起動してください。モジュールにジョイスティックを使用していない場合は、適切なファームウェアが書き込まれているか確認してください。

- トラックボールの動きが遅い
  - PCにUSBで接続していない場合、仕様として遅くなることが確認されています。トラックボールは、速度を決定するDPIの値を即座にキーで変更することができます。Layer(3)のFn Layerにカスタムキー{DPI_UP(速くする), DPI_DN(遅くする), DPI_RST(リセットする)}を押すことで、トラックボールの動きを変更できます。[Default Keymap](../images/keymap_cheatsheet_monkeypad.pdf)をご確認ください。また、Remapの`monkeypad.c`のビルドパラメータを変更して、DPIのレンジ、デフォルト値を設定し、オリジナルのファームウェアを作成することもできます。

- マウスカーソルが遅れる/カクつく
  - USBで左右両方をPCに接続すると左右間の通信を行い続けようとするため遅れが生じます。どちらか一方をPCに接続し、左右間はTRRSケーブルで接続してください。
  - 同様にスプリットキーボード用ファームウェアを書き込み、片手のみの利用だとカーソルがカクつきます。

- トラックボールが反応しない/反応が悪い。
  - レンズが取り付けられているか確認してください
  - センサーの向きが正しく取り付けられているか確認してください
  - ボールとセンサーの距離が水平に正しく取れていない可能性があります。取り付けのネジが正しく付いていること、レンズがカタついたり斜めに取り付くとセンサーが正確に認識しない場合があります。
  マスキングテープなどでレンズが動かないように裏面から貼ったり、トラックボールカバーを外してセンサーだけを取り付けた状態で反応するか試してみてください。

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

---
