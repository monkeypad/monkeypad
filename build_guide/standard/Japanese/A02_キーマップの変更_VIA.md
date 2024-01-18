<!-- ### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)  -->

  - [A02. キーマップの変更(VIA)](A02_キーマップの変更_VIA.md)
    - [A02-1. キーマップの変更(VIA)](#A02-1VIA用ファイル)
    - [A02-2. カスタムキーコード](#A02-2カスタムキーコード)
    - [A02-3. ソースからビルド](#A02-3ソースコード)

### A02-1.VIA用ファイル

キーマップを設定するために、VIAの設定ファイルをダウンロードします。

[Download JSON file](https://github.com/monkeypad/monkeypad/releases/download/v0.1.0/Monkeypad_Mk1.json)

VIAのサイトに移動します。
[VIA](https://www.caniusevia.com/)

トップページ左下の`Start Now`でVIAを起動します。

キーボードをUSBで接続し、Configureタブに`Searching for devices…`と表示されたら、Settingsのタブで`Show Design tab`のトグルをオンにします。

Designタブで`Load Draft Definition`のボタンを押して、ダウンロードしたJSONファイルを読み込みます。

Configureタブに戻ると、キーボードが認識され、VIAが使用できるようになります。

### A02-2.カスタムキーコード

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
