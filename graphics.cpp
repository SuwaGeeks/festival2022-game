#include <Dxlib.h>
#include <map>
#include <string>
#include "graphics.hpp"

// グッフィックを持つ連想配列(Global変数)
// key:グラフィックの名前(string), value: グラッフィックハンドル(int)
std::map<std::string, int> graphics;

// プログラム開始時に実行
void loadGraphics(){
    graphics["player1"] = LoadGraph("../assets/player/player1.png");
    graphics["player2"] = LoadGraph("../assets/player/player2.png");
    graphics["player3"] = LoadGraph("../assets/player/player3.png");
    graphics["player4"] = LoadGraph("../assets/player/player4.png");
    graphics["enemy1-0"] = LoadGraph("../assets/enemys/enemy1-0.png");
    graphics["enemy1-1"] = LoadGraph("../assets/enemys/enemy1-1.png");
    graphics["enemy2-0"] = LoadGraph("../assets/enemys/enemy2-0.png");
    graphics["enemy2-1"] = LoadGraph("../assets/enemys/enemy2-1.png");
    graphics["enemy3-0"] = LoadGraph("../assets/enemys/enemy3-1.png");
    graphics["enemy3-1"] = LoadGraph("../assets/enemys/enemy3-2.png");
    graphics["enemy4-0"] = LoadGraph("../assets/enemys/enemy4-0.png");
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