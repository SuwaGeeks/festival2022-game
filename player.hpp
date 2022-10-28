#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__

#include <string>

class Player {
  private:
    double posX, posY;
    const int height = 50, width = 50;
    int shotIV;

    // グラフィックのKey
    const std::string graphic = "player";

  public:
    int remain;  // 残機
    int godTime;
    void act(int *x, int *y, int *dy);
    void getXY(int *x, int *y);
    void draw();
    Player(double x, double y);
};

#endif