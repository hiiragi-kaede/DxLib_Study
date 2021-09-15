#include"DxLib.h"
#include"Character.hpp"
#include<vector>
#include<math.h>
#include"util.hpp"
#include"Player.hpp"
#include"Enemy.hpp"

//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	pl::Instantiate();

	ene::Instantiate();

	while (1) {
		ClearDrawScreen();
		
		pl::Update();

		ene::Update();

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}