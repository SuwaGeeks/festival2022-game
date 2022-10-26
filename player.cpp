#include <Dxlib.h>
#include <stdlib.h>
#include "player.hpp"
#include "graphics.hpp"
#include "settings.hpp"

// コンストラクタ
Player::Player(double x, double y){
  this->posX = x;
  this->posY = y;
}

// プレイヤーの行動
void Player::act(double *x, double *y, double *dy){
  // dyを初期化
  *dy = 0;

  // 左右の移動(左右どちらも押している場合には停止する)
  if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)){
    this->posX -= PLAYER_DELTA_X;
  }
  if(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)){
    this->posX += PLAYER_DELTA_X;
  }

  // 玉の発射
  if(CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_SPACE)){
    *dy = 1;
  }
}

// ゲッタ
void Player::getXY(int *x, int *y){
  *x = this->posX;
  *y = this->posY;
}

// 描画関数
void Player::draw(){
  DrawGraph((int)(this->posX)-(this->width)/2 ,(int)(this->posY)-(this->height)/2 ,graphics[this->graphic] , FALSE);
}