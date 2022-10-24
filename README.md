# ゲーム for 新風祭

## 作つくるもの
- スペースインベーダー

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
- システム、弾、スコア系 -> 藤本
- プレイヤー、敵、通信 -> 望月

敵の生成 <- システム(生成位置と移動方向をコンストラクタで渡す。(int x, int y, double dx, double dy)  (pix/sec)  
敵の行動 <- 引数act(int *x, int *y, int *dy)：移動(自分自身で)、弾の発射(一定時間か乱数か)。dy != 0 のとき弾を生成するフラグ。  
プレイヤーの移動処理 <- 引数act(int *x, int *y, int *dy)：移動(自分自身でキーボードから)、弾の発射(キーが押されていたら生成)。dy != 0 のとき弾を生成するフラグ。最後に描画  
プレイヤー/敵の消滅 <- デストラクタを作成する。

弾 <- 敵、プレイヤーがメンバ関数でシステムに生成を命令 (int *x, int *y, int *dy) dy != 0 のとき生成。弾の配列の空きが無ければ生成しない。  
敵の消滅 <-毎フレーム敵の座標を監視して、画面外ならインスタンスを消す。
敵のあたり判定 <- システム側で判定して当たってたならインスタンスを消す。
プレイヤーの当たり判定 <- プレイヤーの残機を減らして、当たった弾を消す。  
システム <- 敵を生成する、敵の数の上限などの確認をする。弾の制御を行う。敵/プレイヤーの動作act関数の呼び出し  
ゲーム制御(システム) <- プレイヤーの残機が負になったらスコアボードへ  

## 開発環境
- windows
- gcc 12.2.0

build commands

```
mkdir build
cd build
g++ -c ../*.cpp -DDX_GCC_COMPILE -I"../dxlib"


g++ *.o -o game.exe \
../dxlib/libDxLib.a \
../dxlib/libDxUseCLib.a \
../dxlib/libDxDrawFunc.a \
../dxlib/libjpeg.a \
../dxlib/libpng.a \
../dxlib/libzlib.a \
../dxlib/libtiff.a \
../dxlib/libtheora_static.a \
../dxlib/libvorbis_static.a \
../dxlib/libvorbisfile_static.a \
../dxlib/libogg_static.a \
../dxlib/libbulletdynamics.a \
../dxlib/libbulletcollision.a \
../dxlib/libbulletmath.a \
../dxlib/libopusfile.a \
../dxlib/libopus.a \
../dxlib/libsilk_common.a \
../dxlib/libcelt.a

rm *.o
cd ../
```