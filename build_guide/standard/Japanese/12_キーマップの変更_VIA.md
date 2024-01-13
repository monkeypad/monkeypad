### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)

  - [12. キーマップの変更(VIA)](12_キーマップの変更_VIA.md)
    - [12-1. キーマップの変更(VIA)](#12-1VIA用ファイル)
    - [12-2. カスタムキーコード](#12-2カスタムキーコード)
    - [12-3. ソースからビルド](#12-3ソースコード)

### 12-1.VIA用ファイル

キーマップを設定するために、VIAの設定ファイルをダウンロードします。

[Download JSON file](https://github.com/monkeypad/monkeypad/releases/download/v0.1.0/Monkeypad_Mk1.json)

VIAのサイトに移動します。
[VIA](https://www.caniusevia.com/)

トップページ左下の`Start Now`でVIAを起動します。

キーボードをUSBで接続し、Configureタブに`Searching for devices…`と表示されたら、Settingsのタブで`Show Design tab`のトグルをオンにします。

Designタブで`Load Draft Definition`のボタンを押して、ダウンロードしたJSONファイルを読み込みます。

Configureタブに戻ると、キーボードが認識され、VIAが使用できるようになります。

### 12-2.カスタムキーコード

トラックボールやジョイスティックのモードを変更します。

| Keycode        | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| MK_SCROLL | トラックボールをスクロールモードにします |
| MK_WHEEL | ジョイスティックをホイールスクロールモードにします。 | 
| MK_ARROW | ジョイスティックを矢印('←↑↓→')モードにします | 
| MK_PAD | ジョイスティックを('wasd')モードにします | 

マウス・スクロールの設定値です。
DPI値レンジ{ 100, 200, 300, 400, 500, 600, 800, 1000, 1500, 2000 } デフォルト値は 500 DPI
| Keycode        | Description                                                 |
| -------------- | ----------------------------------------------------------- |
| DPI_UP | DPIを増加させます |
| DPI_DN | DPIを減少させます | 
| DPI_RST | DPI値をデフォルト値に設定します (default:500) | 
| DPI_FINE | キーを押している間はDPI値を最小(100)にします | 

### 12-3.ソースコード

QMKは、左右で異なるポインティングデバイスのドライバーをサポートしていません。（2024/01時点）

もし左右で異なるポインティングデバイス(analog_joystick / pmw3360)を使用している場合、
ターゲットとなるポインティングデバイスを選択し、左右それぞれ1回ずつ、2回コンパイルする必要があります。
（左右で同じポインティングデバイスを使用する場合、エンコーダを使用する場合はファイルは左右で同じファームウェアを使用します.）

QMKでキーボードをコードからカスタムする場合、keyboards/monkeypad/monkeypad/4x6/mk1/rules.mkの
以下のように使用するポインティングデバイスの組み合わせと書き込む側のポインティングデバイスの２つを設定してください。

例：左がジョイスティックで右がトラックボール(pmw3360)の場合、以下のように指定します。

Please select Module type := analog_joystick / pmw3360 / encoder

pmw3360 = trackball sensor

```c
MODULE_DEVICE_LEFT = analog_joystick
MODULE_DEVICE_RIGHT = pmw3360
```

例：書き込むボードがトラックボールのモジュールの場合、`TARGET_POINTING_DEVICE`にpmw3360を設定します。

Please select TARGET_POINTING_DEVICE Type (analog_joystick / pmw3360) ?

```c
TARGET_POINTING_DEVICE = pmw3360
```
