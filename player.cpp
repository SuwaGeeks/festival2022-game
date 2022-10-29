#include <Dxlib.h>
#include <stdlib.h>
#include "player.hpp"
#include "graphics.hpp"
#include "settings.hpp"

// コンストラクタ
Player::Player(double x, double y){
  this->posX = x;
  this->posY = y;
  this->remain = 2;
  this->godTime = 0;
  this->shotIV = 0;
}

// プレイヤーの行動
void Player::act(int *x, int *y, int *dy){

  *x = (int)(this->posX);
  *y = (int)(this->posY);
  // dyを初期化
  *dy = 0;

  // 左右の移動(左右どちらも押している場合には停止する)
  if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)){
    this->posX -= PLAYER_DELTA_X;
  }
  if(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)){
    this->posX += PLAYER_DELTA_X;
  }

  // 境界処理
  if(this->posX < this->width/2){
      this->posX = this->width/2;
  }
  if(this->posX > WINDOW_WIDTH-this->width/2){
      this->posX = WINDOW_WIDTH-this->width/2;
  }

  // 玉の発射
  if(!shotIV && (CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_SPACE))){
    *dy = 1;
    shotIV += 30;
  }

  // 無敵時間の更新
  if(this->godTime > 0)this->godTime--;

  // 発射インターバルの更新
  if(this->shotIV > 0)this->shotIV--;
}

// ゲッタ
void Player::getXY(int *x, int *y){
  *x = this->posX;
  *y = this->posY;
}

// 描画関数
void Player::draw(){
  DrawGraph((int)(this->posX)-(this->width)/2 ,(int)(this->posY)-(this->height)/2 ,graphics[this->graphic] , TRUE);
  for (int i = 0; i < remain; i++){
    DrawGraph(5+i*(this->width + 5), 745, graphics[this->graphic], true);
  }
}