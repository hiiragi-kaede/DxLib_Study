#include "GameMaster.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include"Enemy.hpp"

static const int TitleFont = CreateFontToHandle(DX_FONTTYPE_NORMAL, 40, 3);
static const unsigned Cr_white = GetColor(255, 255, 255);
static master::GameState gameState = master::GameState::Title;

void master::drawTitleScene()
{
	SetFontSize(40);
	DrawString(100, 120, "Test Title", Cr_white);
	SetFontSize(15);
	DrawString(100, 200, "Play", Cr_white);
	DrawString(100, 220, "Config", Cr_white);
}

void master::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SetGameState(master::GameState::Game);
		pl::Instantiate();
		ene::Instantiate();
	}
}

master::GameState master::GetGameState()
{
	return gameState;
}

void master::SetGameState(master::GameState state)
{
	gameState = state;
}

