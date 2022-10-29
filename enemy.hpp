#ifndef __EMEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include <string>
#include <utility>

class Enemy {
  private:
    double posX, posY, dx, dy;
    const int height = 48, width = 48;
    int graphic_flag;
    int score;

    // グラフィックのKey
    std::string graphic[2];

  public:
    void act(int *x, int *y, int *dy);
    void getXY(int *x, int *y);
    void draw();
    int getScore();
    Enemy(double x, double y, double dx, double dy);
    ~Enemy();
};

#endif