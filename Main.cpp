#include"DxLib.h"
#include"Character.hpp"
#include<vector>
#include<math.h>
#include"util.hpp"
#include"Player.hpp"
#include"Enemy.hpp"
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
		
		switch (master::GetGameState())
		{
		case master::GameState::Title:
			master::drawTitleScene();
			master::TitleUpdate();
			break;
		case master::GameState::Game:
			pl::Update();

			ene::Update();

			util::EscToTitle();
			break;
		case master::GameState::Config:
			master::ConfigUpdate();
			break;
		default:
			break;
		}

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}