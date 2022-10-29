#include <Dxlib.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include "ui.hpp"
#include "graphics.hpp"
#include "settings.hpp"

std::vector<std::string> split(std::string& input, char delimiter){
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

std::vector<std::pair<int, std::string>> readScore(){
    std::ifstream ifs("./result.csv");
    std::string line;
    std::vector<std::pair<int, std::string>> score_vec;
    while(getline(ifs, line)) {
        score_vec.push_back(make_pair(atoi(split(line, ',')[1].c_str()), split(line, ',')[0]));
    }
    return score_vec;
} 

Ui::Ui(int highScore){
    // 解像度、ビット深度を取得
    GetScreenState(&(this->Sx) , &(this->Sy) , &(this->Cb));

    // フォントサイズを指定(重いみたい)
    SetFontSize((int)((this->Sx)/25));
    
    // 画面左から何%にスコア名を表示するか
    this->sc1_name_x = (int)(0.25*(this->Sx))-GetDrawStringWidth("SCORE<1>", strlen("SCORE<1>"))/2;
    this->hsc_name_x = (int)(0.50*(this->Sx))-GetDrawStringWidth("HI-SCORE", strlen("HI-SCORE"))/2;
    this->sc2_name_x = (int)(0.75*(this->Sx))-GetDrawStringWidth("SCORE<2>", strlen("SCORE<2>"))/2;

    // 画面上から何%にスコア名、スコアを表示するか
    this->sc_name_y = (int)(0.05*(this->Sy));
    this->sc_y = (int)(0.10*(this->Sy));

    this->footLine_y = (int)(0.92*(this->Sy));
    this->footLine_w = (int)(0.005*(this->Sy));

    // スコアをリセット
    this->highScore = highScore;
    this->score_1 = 0;
    this->score_2 = 0;
}

Ui::~Ui(){
    
}

int Ui::getScore(){
    return this->score_1;
}

void Ui::waitResult(){
    const int topX = 100, topY = 100;
        
    ClearDrawScreen();

	while(!CheckHitKey(KEY_INPUT_ESCAPE) && !(ProcessMessage() < 0)){
		ClearDrawScreen();

        int InputChar = GetInputChar(true);
        if(InputChar != 0 && InputChar == CTRL_CODE_CR)break;

        int drawGO_x = (int)(0.50*Sx)-GetDrawStringWidth("Game Over !!", strlen("Game Over !!"))/2;
        int drawMSG_x = (int)(0.50*Sx)-GetDrawStringWidth("Press Enter to continue.", strlen("Press Enter to continue."))/2;

        DrawString(drawGO_x, 400, "Game Over !!", GetColor(255, 0, 0));
        DrawString(drawMSG_x, 500, "Press Enter to continue.", GetColor(255, 255, 255));

		ScreenFlip() ;
    }
}

void Ui::getName(){
    int itr = 0;
    char name[10] = "";

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
        if(InputChar != 0 && InputChar >= CTRL_CODE_CMP && itr < 9)name[itr++] = InputChar;
        if(InputChar != 0 && InputChar == CTRL_CODE_BS && itr > 0)name[--itr] = ' ';

        if(InputChar != 0 && InputChar == CTRL_CODE_CR && itr != 0)break;
        drawX = (int)(0.50*Sx)-GetDrawFormatStringWidth("%s", name)/2;
        drawDisX = (int)(0.50*Sx)-GetDrawStringWidth("Type your name and press Enter.", strlen("Type your name and press Enter."))/2;

        DrawString(drawX ,drawY , name, GetColor(255, 255, 255));
        DrawString(drawDisX ,drawDisY , "Type your name and press Enter.", GetColor(255, 255, 255));

		// 裏画面の内容を表画面に反映する
		ScreenFlip() ;
	}
    this->name = std::string(name);
}

void Ui::showResult(std::vector<std::pair<int, std::string>>& scores, int* highScore){
    const int topX = 100, topY = 100;
    const int score_center = (int)(0.50*(WINDOW_WIDTH)-GetDrawFormatStringWidth("%5s%10s%10s", "RANK","NAME","SCORE")/2);

    scores.push_back(std::make_pair(this->score_1, (this->name)));

    sort(scores.begin(), scores.end());
    reverse(scores.begin(), scores.end());

    std::ofstream ofs("./result.csv", std::ios::app);
    ofs << this->name << "," << this->score_1 << std::endl;

    ClearDrawScreen();

    // windowsが例外スローでループ終了
	while(!(ProcessMessage() < 0)){
		// 裏画面を初期化(真っ黒にする)
		ClearDrawScreen();
        int i = -1;

        DrawFormatString(score_center, topY+40*i+5 , GetColor(255, 255, 255), "%5s%10s%10s", "RANK","NAME","SCORE");
        // スコア表を描画
        for (int i = 0; i < 10; i++){
            DrawBox(topX , topY+40*i, WINDOW_WIDTH-topX, topY+3+40*i, GetColor(225, 225, 225), true);
            DrawFormatString(score_center, topY+40*i+5 , GetColor(255, 255, 255), "%3d%14s%3s%06d", i+1,scores[i].second.c_str(), "", scores[i].first);
        }
        i++;
        DrawBox(topX , topY+40*i, WINDOW_WIDTH-topX, topY+3+40*i, GetColor(225, 225, 225), true);
        DrawFormatString(score_center, 500 , GetColor(225, 0, 255), "YOU%14s%3s%06d" ,(this->name).c_str(), "", this->score_1);

        DrawGraph(WINDOW_WIDTH/2-75, 600, graphics["qr"], FALSE);

        int swampX = WINDOW_WIDTH/2 - GetDrawStringWidth("SWAMP QRCODE", strlen("SWAMP QRCODE"))/2;
        DrawString(swampX, 760, "SWAMP QRCODE", GetColor(255, 255, 255));

        int InputChar = GetInputChar(true);
        if(InputChar != 0 && InputChar == CTRL_CODE_CR)break;
        if(InputChar != 0 && InputChar == CTRL_CODE_ESC)exit(0);

		// 裏画面の内容を表画面に反映する
		ScreenFlip();
	}
    *highScore = this->highScore;
}

void Ui::renewScore(int ds, int x, int y){
    this->score_1 += ds;
    std::vector<int> data = {100, ds, x, y}; 
    this->scoreEffect.push_back(data);
    this->highScore = std::max(score_1, highScore);
}

void Ui::draw(){

    // スコアの残像を表示
    for(auto itr = this->scoreEffect.begin(); itr != this->scoreEffect.end();){
        DrawFormatString((*itr).at(2), (*itr).at(3), GetColor(2*(*itr).at(0), 2*(*itr).at(0), 2*(*itr).at(0)), "%d", (*itr).at(1));
        (*itr).at(0)--;
        if((*itr).at(0) == 0)itr = (this->scoreEffect).erase(itr);
        else itr++;
    }

    // 画面左から何%にスコアを表示するか
    this->sc1_x = (int)(0.25*(this->Sx))-GetDrawFormatStringWidth("%05d", this->score_1)/2;
    this->hsc_x = (int)(0.50*(this->Sx))-GetDrawFormatStringWidth("%05d", this->highScore)/2;
    this->sc2_x = (int)(0.75*(this->Sx))-GetDrawFormatStringWidth("%05d", this->score_2)/2;

    // スコア名を描画
    DrawString(this->sc1_name_x, this->sc_name_y, "SCORE<1>", GetColor(0 , 255, 255));
    DrawString(this->hsc_name_x, this->sc_name_y, "HI-SCORE", GetColor(0 , 100, 255));
    DrawString(this->sc2_name_x, this->sc_name_y, "SCORE<2>", GetColor(255 , 255, 0));

    // スコアを描画
    DrawFormatString(this->sc1_x, this->sc_y, GetColor(255, 255, 255), "%05d", this->score_1);
    DrawFormatString(this->hsc_x, this->sc_y, GetColor(0, 100, 255), "%05d", this->highScore);
    // DrawFormatString(this->sc2_x, this->sc_y, GetColor(255, 255, 255), "%05d", this->score_2);

    DrawBox(0 , this->footLine_y, this->Sx, this->footLine_y+this->footLine_w, GetColor(225, 0, 0), true) ;

}