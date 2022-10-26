#ifndef __EMEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include <string>

class Enemy {
  private:
    double posX, posY, dx, dy;
    const int height = 50, width = 50;

    // グラフィックのKey
    const std::string graphic = "enemy1";

  public:
    void act(int *x, int *y, int *dy);
    void getXY(int *x, int *y);
    void draw();
    Enemy(double x, double y, double dx, double dy);
    ~Enemy();
};

#endif