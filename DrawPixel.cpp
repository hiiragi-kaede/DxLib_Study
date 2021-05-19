#include"DxLib.h"

//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
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

	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}