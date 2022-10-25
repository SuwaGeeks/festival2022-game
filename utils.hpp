#ifndef __UTILS_HPP_INCLUDED__
#define __UTILS_HPP_INCLUDED__

class Utils{
    private:
    
        // 画面の縦解像度
        int displayHeight = 800;

        // 画面の横解像度
        int displayWidth = 600;

        // 画面のビット深度
        int displayBitDepth = 32;

        // windowモードで起動するか
        bool isWindowMode = true;

        // windowのタイトル
        const char* windowTitle = "f2022-game";

        // windowサイズが変更可能であるか
        bool isWindowScaleable = false;

        // windowの倍率
        double windowScale = 1.0;

    public:
        Utils();
        ~Utils();
};


#endif