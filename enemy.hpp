#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__

class Enemy {
  private:
    int posX, posY, dx, dy;

  public:
    double act(int *x, int *y, int *dy);
    Enemy(int x, int y, int dx, int dy);
};

#endif