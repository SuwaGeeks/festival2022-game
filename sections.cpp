#include <Dxlib.h>
#include <string>
#include "sections.hpp"

using namespace std;


string getName(){
    int inputDelay = 0, itr = 0;
    char name[8] = "";

    int Sx, Sy, Cb;
    int drawX, drawY;
    int drawDisX, drawDisY;
    GetScreenState(&Sx, &Sy, &Cb);

    // フォントサイズを指定(重いみたい)
    SetFontSize((int)(Sx/25));

    // 画面上から何%にスコア名、スコアを表示するか
    drawY = (int)(0.50*Sy);
    drawDisY = (int)(0.60*Sy);


    // windowsが例外スロー または ESC入力　でループ終了
	while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0)){
		// 裏画面を初期化(真っ黒にする)
		ClearDrawScreen();

        int InputChar = GetInputChar(true) ;

        // 操作コード以外の文字入力があった場合のみ表示処理を行う
        if(InputChar != 0 && InputChar >= CTRL_CODE_CMP && itr < 8)name[itr++] = InputChar;
        if(InputChar != 0 && InputChar == CTRL_CODE_BS && itr > 0)name[--itr] = ' ';

        if(InputChar != 0 && InputChar == CTRL_CODE_CR)break;
        drawX = (int)(0.50*Sx)-GetDrawFormatStringWidth("%s", name)/2;
        drawDisX = (int)(0.50*Sx)-GetDrawStringWidth("Type your name and press Enter.", strlen("Type your name and press Enter."))/2;

        DrawString(drawX ,drawY , name, GetColor(255, 255, 255));
        DrawString(drawDisX ,drawDisY , "Type your name and press Enter.", GetColor(255, 255, 255));

		// 裏画面の内容を表画面に反映する
		ScreenFlip() ;
	}

    return string(name);
}