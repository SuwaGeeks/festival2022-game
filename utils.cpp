#include <Dxlib.h>
#include "utils.hpp"

utils::utils(){
    SetGraphMode(this->displayWidth , this->displayHeight , this->displayBitDepth) ;
    ChangeWindowMode(this->isWindowMode);
    SetWindowText(this->windowTitle);
    SetWindowSizeChangeEnableFlag(this->isWindowScaleable);
    SetWindowSizeExtendRate(this->windowScale);
    if( DxLib_Init() == -1 )exit;	// ＤＸライブラリ初期化処理
}

utils::~utils(){
    DxLib_End();	// ＤＸライブラリ使用の終了処理
}