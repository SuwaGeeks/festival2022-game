#include <DxLib.h>
#include "utils.hpp"
#include "graphics.hpp"
#include "bullet.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Utils* aaa = new Utils();
	loadGraphics();

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK) ;

	bullet b(300, 0, 1, false);

	// windowsが例外スロー または ESC入力　でループ終了
	while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0)){
		// 裏画面を初期化(真っ黒にする)
		ClearDrawScreen() ;

		b.move();
		b.draw();
		DrawFormatString( 0, 0, GetColor( 255 , 255 , 255 ), "bullet(%.0f,%.0f)", b.x, b.y);


		// 裏画面の内容を表画面に反映する
		ScreenFlip() ;
	}

	deleteGraphics();
	delete aaa;

	return 0 ;
}