#include"DxLib.h"
#include"GameMaster.hpp"

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	while (1) {
		ClearDrawScreen();
		
		master::Update();

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}