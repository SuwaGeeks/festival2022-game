#include <Dxlib.h>

class Enemy {
  private:
    int posX, posY;

  public:
    double act(int *x, int *y, int *dy);
    Enemy(int x, int y, int dx, int dy);
};