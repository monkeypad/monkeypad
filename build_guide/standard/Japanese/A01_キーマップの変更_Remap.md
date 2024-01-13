### Monkeypad Build Guide Top Page is here [English](01_build_guide.md)

  - [A01. キーマップの変更(Remap)](A01_キーマップの変更_Remap.md)
    - [A01-1. キーマップの変更(Remap)](#A01-1キーマップの変更)
    - [A01-2. より深くカスタマイズするには](#A01-2より深くカスタマイズするには)

### A01-1.キーマップの変更(Remap)

デフォルトのキーマップは以下からダウンロードできます。

[Default Keymap](../images/keymap_cheatsheet_monkeypad.pdf)

MonkeyPadは[Remap](https://salicylic-acid3.hatenablog.com/entry/remap-manual)に対応しています。特別なソフトをインストールしなくてもファームウェアのカスタマイズとキーマップの変更が可能です。VIAで変更する場合は次章[A02_キーマップの変更_VIA](A02_キーマップの変更_VIA.md)を参照してください。

Remapの使用方法については[自キ温泉ガイドのサリチル酸の記事](https://salicylic-acid3.hatenablog.com/entry/remap-manual)に詳しく解説されています。

Layout Optionを選択します。

![](../images/A01/remap_01.jpg)

取り付けたモジュールに合わせて、プルダウンから選択します。

![](../images/A01/remap_02.jpg)

キーマップをお好きな配置に変更後、flashボタンを押すと反映されます。

![](../images/A01/remap_03.jpg)


### A01-2.より深くカスタマイズするには

ご自身でファームウェアをビルドする場合

Monkeypadの最新ファームウェアはすべてGithubのリポジトリにて公開しています。ファームウェアからビルドする方法としては、以下の二通りがあります。

[Monkeypad(github)](https://github.com/monkeypad/monkeypad/tree/main/qmk_firmware/keyboards/monkeypad/monkeypad)

- Remap

Remapはキーマップの変更だけでなく、新機能としてファームウェアビルド機能が追加されました（2023/11）。ローカルにQMKの開発環境を構築することなく、ファームウェアをソースコードレベルからビルドすることもできます。詳しくは作者の[Yoichiroさんが解説されている記事](https://www.eisbahn.jp/yoichiro/2023/11/remap_building_firmware.html#gsc.tab=0)のユーザー向けの機能をご参照ください。

- QMK

monkeypadフォルダをお手持ちのQMK_Firmware/keyboardsへコピーして自由にキーマップ等を編集してビルドしてください。いろいろな方が解説されています。

