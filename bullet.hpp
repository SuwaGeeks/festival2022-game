#ifndef __BULLET_HPP_INCLUDED__
#define __BULLET_HPP_INCLUDED__

#include <string>

class Bullet{
    private:
        double dy;

        // グラフィックのKey
        const std::string graphic = "bullet1";

    public:
        double x, y;

        // true:敵の弾, false:時機の弾
        bool isEnemy;

        // 引数: 初期座標x, y, y方向へ進む速さ[pix/sec], 敵の弾であるか
        Bullet(int, int, double, bool);
        ~Bullet();
        void move();
        void draw();
};


#endif