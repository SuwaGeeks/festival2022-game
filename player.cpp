#include <Dxlib.h>

class Player {
  private:
    int posX, posY;

  public:
    double act(int *x, int *y, int *dy);
    Player(int x, int y);
};