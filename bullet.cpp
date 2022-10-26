#include <Dxlib.h>
#include "bullet.hpp"
#include "graphics.hpp"

Bullet::Bullet(int x, int y, double dy, bool isEnemy){
    this->x = (double)x;
    this->y = (double)y;
    this->dy = dy;
    this->isEnemy = isEnemy;
}

Bullet::~Bullet(){

}

void Bullet::getXYF(int *x, int *y, int *isEnemy){
    *x = (int)(this->x);
    *y = (int)(this->y);
    *isEnemy = (int)(this->isEnemy);
}

void Bullet::move(){
    this->y += dy;
}

void Bullet::draw(){
    DrawGraph((int)(this->x)-(this->width)/2 ,(int)(this->y)-(this->height)/2  ,graphics[this->graphic] , FALSE) ;
}

