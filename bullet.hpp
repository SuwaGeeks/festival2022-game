#ifndef __BULLET_HPP_INCLUDED__
#define __BULLET_HPP_INCLUDED__

#include <string>

class Bullet{
    private:
        double x, y;
        double dy;

        int width = 8, height = 24;

        // true:敵の弾, false:時機の弾
        bool isEnemy;

        // グラフィックのKey
        const std::string graphic = "bullet1";

    public:

        // 引数: 初期座標x, y, y方向へ進む速さ[pix/sec], 敵の弾であるか
        Bullet(int, int, double, bool);
        ~Bullet();
        void getXYF(int *x, int *y, int *isEnemy);
        void move();
        void draw();
};


#endif