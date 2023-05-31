#include <Dxlib.h>
#include "bullet.hpp"
#include "graphics.hpp"

Bullet::Bullet(int x, int y, double dy, bool isEnemy){
    this->x = (double)x;
    this->y = (double)y;
    this->dy = dy;
    this->isEnemy = isEnemy;
    this->state = 0;
    if(isEnemy){
        // PlaySoundMem(sounds["e_shot"] , DX_PLAYTYPE_BACK);
    }else{
        PlaySoundMem(sounds["p_shot"] , DX_PLAYTYPE_BACK);
    }
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
    this->state++;
    if(this->state == 60)this->state = 0;
}

void Bullet::draw(){
    if(this->isEnemy){
        if(((this->state)/10)%2){
            DrawGraph((int)(this->x)-(this->width)/2 ,(int)(this->y)-(this->height)/2  ,graphics["e_bullet-0"] , TRUE);
        }else{
            DrawGraph((int)(this->x)-(this->width)/2 ,(int)(this->y)-(this->height)/2  ,graphics["e_bullet-1"] , TRUE);
        }
    }else{
        DrawGraph((int)(this->x)-(this->width)/2 ,(int)(this->y)-(this->height)/2  ,graphics["p_bullet1"] , TRUE) ;
    }
    
}

