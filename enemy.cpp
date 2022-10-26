#include <Dxlib.h>
#include <stdlib.h>
#include "enemy.hpp"
#include "graphics.hpp"

#define SHOOT_RATE 0.1

// コンストラクタ
Enemy::Enemy(double x, double y, double dx, double dy){
  this->posX = x;
  this->posY = y;
  this->dx = dx;
  this->dy = dy;
  // srand(time(NULL)); mainのはじめでやってるので消しました
}

// デストラクタ
Enemy::~Enemy(){ }

// 敵の行動
void Enemy::act(int *x, int *y, int *dy){
  // dyを初期化
  *dy = 0;

  // 自身を移動する
  this->posX += this->dx;
  this->posY += this->dy;

  // 弾を撃つかどうか判断
  double ifShooting = (double)rand() / RAND_MAX;
  if(ifShooting < SHOOT_RATE){
    *dy = 1;  // 弾を撃つならdyをフラグとして1にする。
    *x = (int)(this->posX);  *y = (int)(this->posY);
  }
}

// ゲッタ
void Enemy::getXY(int *x, int *y){
  *x = this->posX;
  *y = this->posY;
}

// 描画関数
void Enemy::draw(){
  DrawGraph((int)(this->posX)-(this->width)/2 ,(int)(this->posY)-(this->height)/2 ,graphics[this->graphic] , FALSE);
}