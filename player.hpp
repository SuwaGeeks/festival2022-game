#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__

#include <string>

class Player {
  private:
    double posX, posY;
    const int height = 50, width = 50;

    // グラフィックのKey
    const std::string graphic = "enemy1";

  public:
    void act(double *x, double *y, double *dy);
    void getXY(int *x, int *y);
    void draw();
    Player(double x, double y);
};

#endif