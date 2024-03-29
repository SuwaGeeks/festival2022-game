#include <Dxlib.h>
#include <stdlib.h>
#include <iostream>
#include "enemy.hpp"
#include "graphics.hpp"
#include "settings.hpp"

// コンストラクタ
Enemy::Enemy(double x, double y, double dx, double dy){
  this->posX = x;
  this->posY = y;
  this->dx = dx;
  this->dy = dy;
  this->graphic_flag = 0;
  srand(time(NULL));
  int eType = (rand()%100);
  if(eType < 40){
    this->graphic[0] = "enemy1-0";
    this->graphic[1] = "enemy1-1";
    this->score = 100;
  }else if(eType < 70){
    this->graphic[0] = "enemy2-0";
    this->graphic[1] = "enemy2-1";
    this->score = 200;
  }else if(eType < 90){
    this->graphic[0] = "enemy3-0";
    this->graphic[1] = "enemy3-1";
    this->score = 300;
  }else{
    this->graphic[0] = "enemy4-0";
    this->graphic[1] = "enemy4-0";
    this->score = 500;
  }
}

// デストラクタ
Enemy::~Enemy(){
}

// 敵の行動
void Enemy::act(int *x, int *y, int *dy){
  // dyを初期化
  *dy = 0;

  // 自身を移動する
  this->posX += this->dx;
  this->posY += this->dy;

  // 弾を撃つかどうか判断
  double ifShooting = (double)rand() / RAND_MAX;
  if(ifShooting < ENEMY_SHOOT_RATE){
    *dy = 1;  // 弾を撃つならdyをフラグとして1にする。
    *x = (int)(this->posX);  *y = (int)(this->posY);
  }

  // アニメーション用の処理
  this->graphic_flag++;
  if(this->graphic_flag > 60) {this->graphic_flag = 0;}
  // std::cout << this->graphic_flag << std::endl;
}

int Enemy::getScore(){
  return (int)((1+(ENEMY_SPAWN_BORDER-(this->posY))/ENEMY_SPAWN_BORDER)*(this->score));
}

// ゲッタ
void Enemy::getXY(int *x, int *y){
  *x = this->posX;
  *y = this->posY;
}

// 描画関数
void Enemy::draw(){
  DrawGraph((int)(this->posX)-(this->width)/2 ,(int)(this->posY)-(this->height)/2 ,graphics[this->graphic[this->graphic_flag > 30]] , TRUE);
  // this->graphic_flag++;
}