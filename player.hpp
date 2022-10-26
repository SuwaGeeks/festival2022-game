#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__

class Player {
  private:
    int posX, posY;

  public:
    double act(int *x, int *y, int *dy);
    Player(int x, int y);
};

#endif