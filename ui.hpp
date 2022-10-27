#ifndef __UI_HPP_INCLUDED__
#define __UI_HPP_INCLUDED__

#include <string>

using namespace std;

class Ui{
    private:
        // 画面の縦、横、bit深度
        int Sx, Sy, Cb;

        // スコア名の位置情報
        int sc1_name_x, hsc_name_x, sc2_name_x;
        int sc_name_y;

        // スコアの位置情報
        int sc1_x, hsc_x, sc2_x;
        int sc_y;

        // フィットラインの高さと幅
        int footLine_y, footLine_w;

        // スコア
        int score_1, score_2;
        int highScore;

        // プレイヤー名
        string name;

    public:
        Ui(int);
        ~Ui();
        void getName();
        void renewScore(int);
        void draw();
        void whowResult(std::vector<std::pair<int, const char*>>& scores);
};

#endif