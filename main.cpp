#include <DxLib.h>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include "sections.hpp"
#include "settings.hpp"
#include "graphics.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "ui.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	// 敵と弾を管理するlist
	std::list<Bullet> bullet_list;
	std::list<Enemy> enemy_list;

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

	Ui gameCTL(highScore, getName());

	// windowsが例外スロー または ESC入力　でループ終了
	SetDrawScreen(DX_SCREEN_BACK);
	while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0)){
		ClearDrawScreen() ;

		// リスポーン処理
		if(std::rand()%120 == 0)enemy_list.push_back(Enemy((rand()%2)? 0: WINDOW_WIDTH, rand()%ENEMY_SPAWN_BORDER, (rand()%7)-3, (rand()%4)));
		
		// 移動処理
		int x, y, isShot;
		for(auto itr = enemy_list.begin(); itr != enemy_list.end(); ++itr) {
			(*itr).act(&x, &y, &isShot);
			if(isShot)bullet_list.push_back(Bullet(x, y, 30.0, true));
		}
		for(auto itr = bullet_list.begin(); itr != bullet_list.end(); ++itr) {
			(*itr).move();
		}
		

		// 当たり判定 & デスポーン処理
		int eX, eY, bX, bY, isEnemy;
		for(auto b_itr = bullet_list.begin(); b_itr != bullet_list.end();){
			(*b_itr).getXYF(&bX, &bY, &isEnemy);

			// 弾が画面外
			if(bX < 0 or bY < 0 or bX > WINDOW_WIDTH or bY > WINDOW_HEIGHT){
				b_itr = bullet_list.erase(b_itr);
				continue;
			}

			for (auto e_itr = enemy_list.begin(); e_itr != enemy_list.end();){
				(*e_itr).getXY(&eX, &eY);

				// 敵が画面外
				if(eX < 0 or eY < 0 or eX > WINDOW_WIDTH or eY > WINDOW_HEIGHT){
					e_itr = enemy_list.erase(e_itr);
					gameCTL.renewScore(100);
					continue;
				}

				// 当たり判定処理
				if(false/* 当たる条件 */){
					e_itr = enemy_list.erase(e_itr);
					continue;
				}
				e_itr++;
			}

			b_itr++;
    	}
		

		// 描画処理
		gameCTL.draw();
		for (auto enemy: enemy_list){
			enemy.draw();
		}
		for (auto bullet: bullet_list){
			bullet.draw();
		}


		ScreenFlip() ;
	}

	// 終了処理
	deleteGraphics();
	DxLib_End();

	return 0 ;
}