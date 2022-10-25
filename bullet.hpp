#ifndef __BULLET_HPP_INCLUDED__
#define __BULLET_HPP_INCLUDED__

#include <string>

class Bullet{
    private:
        double dy;
        const std::string graphic = "bullet1";

    public:
        double x, y;
        bool isEnemy;

        Bullet(int, int, double, bool);
        ~Bullet();
        void move();
        void draw();
};


#endif