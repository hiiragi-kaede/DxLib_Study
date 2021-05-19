#include"DxLib.h"

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	LoadGraphScreen(0, 0, "img/JK.png",FALSE);
	WaitKey(); //キー入力待ち
	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}