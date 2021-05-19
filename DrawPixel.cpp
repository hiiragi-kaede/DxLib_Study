#include"DxLib.h"

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);


	int BallGraph = LoadGraph("img/ball.png");
	int BallX = -64, BallY = 0;

	int SquareGraph = LoadGraph("img/square.png");
	int SquareX = 640, SquareY = 300;

	for (int i = 0; i < 400; i++) {
		ClearDrawScreen();

		BallX += 3;

		DrawGraph(BallX, BallY, BallGraph, FALSE);

		SquareX -= 3;
		SquareY -= 2;

		DrawGraph(SquareX, SquareY, SquareGraph, FALSE);

		ScreenFlip();

		if (ProcessMessage() < 0) break;
	}

	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}