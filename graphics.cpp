#include <Dxlib.h>
#include <map>
#include <string>
#include "graphics.hpp"

// グッフィックを持つ連想配列(Global変数)
// key:グラフィックの名前(string), value: グラッフィックハンドル(int)
std::map<std::string, int> graphics;
std::map<std::string, int> sounds;

// プログラム開始時に実行
void loadGraphics(){

    sounds["appear"] = LoadSoundMem("../assets/sounds/appear.wav");
    sounds["e_break"] = LoadSoundMem("../assets/sounds/e_break.wav");
    sounds["p_break"] = LoadSoundMem("../assets/sounds/p_break.wav");
    sounds["e_shot"] = LoadSoundMem("../assets/sounds/e_shot.wav");
    sounds["p_shot"] = LoadSoundMem("../assets/sounds/p_shot.wav");
    
    graphics["player1"] = LoadGraph("../assets/graphics/player/player1.png");
    graphics["player2"] = LoadGraph("../assets/graphics/player/player2.png");
    graphics["player3"] = LoadGraph("../assets/graphics/player/player3.png");
    graphics["player4"] = LoadGraph("../assets/graphics/player/player4.png");

    graphics["enemy1-0"] = LoadGraph("../assets/graphics/enemys/enemy1-0.png");
    graphics["enemy1-1"] = LoadGraph("../assets/graphics/enemys/enemy1-1.png");
    graphics["enemy2-0"] = LoadGraph("../assets/graphics/enemys/enemy2-0.png");
    graphics["enemy2-1"] = LoadGraph("../assets/graphics/enemys/enemy2-1.png");
    graphics["enemy3-0"] = LoadGraph("../assets/graphics/enemys/enemy3-0.png");
    graphics["enemy3-1"] = LoadGraph("../assets/graphics/enemys/enemy3-1.png");
    graphics["enemy4-0"] = LoadGraph("../assets/graphics/enemys/enemy4-0.png");

    graphics["p_bullet1"] = LoadGraph("../assets/graphics/bullets/p_bullet1.png");
    graphics["e_bullet-0"] = LoadGraph("../assets/graphics/bullets/e_bullet-0.png");
    graphics["e_bullet-1"] = LoadGraph("../assets/graphics/bullets/e_bullet-1.png");

    graphics["qr"] = LoadGraph("../assets/graphics/qr.png");

}

// プログラム終了時に実行
void deleteGraphics(){

    for(auto itr = sounds.begin(); itr != sounds.end(); ++itr){
        DeleteSoundMem(itr->second);
    }

    for(auto itr = graphics.begin(); itr != graphics.end(); ++itr){
        DeleteGraph(itr->second);
    }

}