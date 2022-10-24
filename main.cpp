#include <DxLib.h>
#include "draw.hpp"
#include "utils.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	utils* aaa = new utils();


	SuwaGeeks();
	WaitKey();

	delete aaa;
	return 0 ;
}