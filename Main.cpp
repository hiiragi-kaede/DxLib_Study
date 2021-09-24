#include"DxLib.h"
#include"GameMaster.hpp"

//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	while (1) {
		ClearDrawScreen();
		
		master::Update();

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}