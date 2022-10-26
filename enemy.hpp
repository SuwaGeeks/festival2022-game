#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__

#include <string>

class Enemy {
  private:
    double posX, posY, dx, dy;

    // グラフィックのKey
    const std::string graphic = "enemy1";

  public:
    void act(int *x, int *y, int *dy);
    Enemy(double x, double y, double dx, double dy);
    ~Enemy();
};

#endif