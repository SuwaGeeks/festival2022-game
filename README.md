# ゲーム for 新風祭

## 作ったもの
スペースインベーダー

## 動作確認環境
- Windows 10 Education 21H2
- gcc 12.2.0
- GNU Make 3.81
- Git Bash / コマンドプロンプト
- (一応ゲームパッド対応です。)

## 遊び方

[DXライブラリ](https://dxlib.xsrv.jp/dxdload.html)のWindows版 Gnu C++( MinGW )用をダウンロードし、解答した後、「プロジェクトに追加すべきファイル_GCC(MinGW)用」フォルダの中から自分のgccのバージョンに合ったものの**中身をすべて**をこのプロジェクトの`dxlib`フォルダに入れてください。

コンパイル
```
mkdir build
make
```

起動
```
game.exe  # cmd
./game.exe  # Git bash
```

Clean
```
make clean  # cmd
make clean_b  # git bash
```
## 内容
- ランダムのリスポーン/移動する敵を撃破
- 敵の種類たくさん
- 画面外に出たらデスポーン
- 敵の攻撃が3(残機)回当たればGameOver
- スコアを記録
- 進行に応じて難易度が上昇
  - 移動速度が早くなる
  - 攻撃頻度が高くなる

(できれば実装)
- スコアに応じて残機の増加
- webベースのスコアボード

## 作業分担
- システム、弾、スコア系 -> [Yudai Fujimoto](https://github.com/Apricot256)
- プレイヤー、敵、通信 -> [Mochi](https://github.com/mochi-yu)