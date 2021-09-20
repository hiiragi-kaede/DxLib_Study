#include"DxLib.h"
#include"Character.hpp"
#include<vector>
#include<math.h>
#include"util.hpp"
#include"Player.hpp"
#include"Enemy.hpp"
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
	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}