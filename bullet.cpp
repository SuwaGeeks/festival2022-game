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

void Bullet::move(){
    this->y += dy;
}

void Bullet::draw(){
    DrawGraph((int)(this->x) ,(int)(this->y) ,graphics[this->graphic] , FALSE) ;
}

