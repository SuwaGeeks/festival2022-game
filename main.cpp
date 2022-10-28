#include <DxLib.h>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
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

	std::vector<std::pair<int, const char*>> scores(10, std::make_pair(0, "NO NAME"));
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

	Ui gameCTL(highScore);
	Player player(WINDOW_WIDTH/2, 700);

	// windowsが例外スロー または ESC入力　でループ終了
	while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0) && player.remain >= 0){
		ClearDrawScreen();

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

		// 自機処理
		int pX, pY, pisShot;
		player.act(&pX, &pY, &pisShot);
		if(pisShot)bullet_list.push_back(Bullet(pX, pY, -30.0, false));

		// 当たり判定 & デスポーン処理
		int eX, eY, bX, bY, isEnemy;
		for(auto b_itr = bullet_list.begin(); b_itr != bullet_list.end();){
			(*b_itr).getXYF(&bX, &bY, &isEnemy);

			// 弾が画面外
			if(bX < 0 or bY < 0 or bX > WINDOW_WIDTH or bY > WINDOW_HEIGHT){
				b_itr = bullet_list.erase(b_itr);
				continue;
			}

			// 時機の当たり判定
			if(isEnemy && !(player.godTime) && (pX-bX)*(pX-bX)+(pY-bY)*(pY-bY) < (BULLET_CD+PLAYER_CD)*(BULLET_CD+PLAYER_CD)){
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
				if(!isEnemy && (eX-bX)*(eX-bX)+(eY-bY)*(eY-bY) < (ENEMY_CD+BULLET_CD)*(BULLET_CD+PLAYER_CD)){
					e_itr = enemy_list.erase(e_itr);
					b_itr = bullet_list.erase(b_itr);
					gameCTL.renewScore(100);
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
		gameCTL.draw();

		ScreenFlip() ;
	}
	// ゲーム終了処理
	gameCTL.getName();
	gameCTL.whowResult(scores);

	// 終了処理
	deleteGraphics();
	DxLib_End();

	return 0 ;
}