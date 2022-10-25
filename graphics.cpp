#include <Dxlib.h>
#include <map>
#include <string>
#include "graphics.hpp"

// グッフィックを持つ連想配列(Global変数)
// key:グラフィックの名前(string), value: グラッフィックハンドル(int)
std::map<std::string, int> graphics;

// プログラム開始時に実行
void loadGraphics(){
    graphics["player"] = LoadGraph("../assets/player/player1.png");
    graphics["enemy1"] = LoadGraph("../assets/enemys/enemy1.png");
    graphics["bullet1"] = LoadGraph("../assets/bullets/bullet1.png");
}

// プログラム終了時に実行
void deleteGraphics(){
    
    // DeleteGraph(Graphics.player);
    // DeleteGraph(Graphics.enemy1);
    // DeleteGraph(Graphics.bullet1);

    auto iter = graphics.begin();
    while (iter != graphics.end()) {
        DeleteGraph(iter->second);
        ++iter;
    }
}