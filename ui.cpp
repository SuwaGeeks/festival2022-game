#include <Dxlib.h>
#include <string.h>
#include <algorithm>
#include "ui.hpp"

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

    this->footLine_y = (int)(0.90*(this->Sy));
    this->footLine_w = (int)(0.005*(this->Sy));

    // スコアをリセット
    this->highScore = highScore;
    this->score_1 = 0;
    this->score_2 = 0;
}

Ui::~Ui(){
    // scvに追記
}

void Ui::renewScore(int ds){
    this->score_1 += ds;
    highScore = std::max(score_1, highScore);
}

void Ui::draw(){

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