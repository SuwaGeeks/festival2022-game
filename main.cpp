#include <DxLib.h>
#include <list>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "settings.hpp"
#include "graphics.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "ui.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	// 敵と弾を管理するlist
	std::list<Bullet> bullet_list;
	std::list<Enemy> enemy_list;

	std::vector<std::pair<int, std::string>> scores = readScore();
	// for(std::pair x: scores){
    //     std::cout << x.first << " " << x.second << std::endl;
    // }
	for (int i = scores.size(); i < 10; i++)scores.push_back(std::make_pair(0, "NO NAME"));
	int highScore = 0;	// ハイスコア

	// 開始処理
	std::srand(time(NULL));
	SetGraphMode(WINDOW_WIDTH , WINDOW_HEIGHT , WINDOW_BIT_DEPTH) ;
    ChangeWindowMode(WINDOW_MODE);
    SetWindowText(WINDOW_TITLE);
    SetWindowSizeChangeEnableFlag(WINDOW_SCALABLE);
    SetWindowSizeExtendRate(WINDOW_SCALE);
    if( DxLib_Init() == -1 )exit;
	loadGraphics();
	SetDrawScreen(DX_SCREEN_BACK);

	while(true){
		Ui *gameCTL = new Ui(highScore);
		Player player(WINDOW_WIDTH/2, 710);

		// windowsが例外スロー または ESC入力　でループ終了
		while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0) && player.remain >= 0){
			ClearDrawScreen();

			// リスポーン処理(今は適当)
			if(std::rand()%((int)(60*(1-sin(gameCTL->getScore()/100000.0)))) == 0){
				int side = rand()%2;
				int esp_x, esp_y = rand()%ENEMY_SPAWN_BORDER, esp_dx, esp_dy = rand()%4;
				if(side == 0){
					esp_x = 0;
					esp_dx = (rand()%4)+1;
				}else{
					esp_x = WINDOW_WIDTH;
					esp_dx = -1*((rand()%4)+1);
				}
				enemy_list.push_back(Enemy(esp_x, esp_y, esp_dx, rand()%4));
				// PlaySoundMem(sounds["appear"] , DX_PLAYTYPE_BACK);
			}

			// 移動処理
			int x, y, isShot;
			for(auto itr = enemy_list.begin(); itr != enemy_list.end(); ++itr) {
				(*itr).act(&x, &y, &isShot);
				if(isShot)bullet_list.push_back(Bullet(x, y, 5.0, true));
			}
			for(auto itr = bullet_list.begin(); itr != bullet_list.end(); ++itr) {
				(*itr).move();
			}

			// 自機処理
			int pX, pY, pisShot;
			player.act(&pX, &pY, &pisShot);
			if(pisShot)bullet_list.push_back(Bullet(pX, pY, -30.0, false));



			// 当たり判定 & デスポーン処理
			int eX, eY, bX, bY, isEnemy;
			
			// 敵と時機の当たり判定
			for (auto e_itr = enemy_list.begin(); e_itr != enemy_list.end(); ++e_itr){
				(*e_itr).getXY(&eX, &eY);
				if(!(player.godTime) && (eX-pX)*(eX-pX)+(eY-pY)*(eY-pY) < (ENEMY_CD+PLAYER_CD)*(ENEMY_CD+PLAYER_CD)){
					PlaySoundMem(sounds["p_break"] , DX_PLAYTYPE_BACK);
					player.godTime = 60;
					player.remain--;
					continue;
				}
			}

			for(auto b_itr = bullet_list.begin(); b_itr != bullet_list.end();){
				(*b_itr).getXYF(&bX, &bY, &isEnemy);

				// 弾が画面外
				if(bX < 0 or bY < 0 or bX > WINDOW_WIDTH or bY > WINDOW_HEIGHT){
					b_itr = bullet_list.erase(b_itr);
					continue;
				}

				// 時機と弾の当たり判定
				if(isEnemy && !(player.godTime) && (pX-bX)*(pX-bX)+(pY-bY)*(pY-bY) < (BULLET_CD+PLAYER_CD)*(BULLET_CD+PLAYER_CD)){
					PlaySoundMem(sounds["p_break"] , DX_PLAYTYPE_BACK);
					b_itr = bullet_list.erase(b_itr);
					player.godTime = 60;
					player.remain--;
					continue;
				}

				// 敵の消滅処理
				for (auto e_itr = enemy_list.begin(); e_itr != enemy_list.end();){
					(*e_itr).getXY(&eX, &eY);

					// 敵が画面外
					if(eX < 0 or eY < 0 or eX > WINDOW_WIDTH or eY > WINDOW_HEIGHT){
						e_itr = enemy_list.erase(e_itr);
						continue;
					}

					// 敵の当たり判定処理
					if(!isEnemy && (eX-bX)*(eX-bX)+(eY-bY)*(eY-bY) < (ENEMY_CD+BULLET_CD)*(ENEMY_CD+BULLET_CD)){
						gameCTL->renewScore((*e_itr).getScore(), eX, eY);
						e_itr = enemy_list.erase(e_itr);
						b_itr = bullet_list.erase(b_itr);
						PlaySoundMem(sounds["e_break"] , DX_PLAYTYPE_BACK);
						break;
					}
					e_itr++;
				}

				b_itr++;
			}
			

			// 描画処理
			for (auto enemy: enemy_list){
				enemy.draw();
			}
			for (auto bullet: bullet_list){
				bullet.draw();
			}
			player.draw();
			gameCTL->draw();

			ScreenFlip();
		}
		// ゲーム終了処理
		gameCTL->waitResult();
		gameCTL->getName();
		gameCTL->showResult(scores, &highScore);
		enemy_list.clear();
		bullet_list.clear();
		delete gameCTL;
	}

	// 終了処理
	deleteGraphics();
	DxLib_End();

	return 0 ;
}