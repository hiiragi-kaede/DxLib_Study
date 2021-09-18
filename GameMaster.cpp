#include "GameMaster.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include"Enemy.hpp"
#include"string"

static const int TitleFont = CreateFontToHandle(DX_FONTTYPE_NORMAL, 40, 3);
static const unsigned Cr_white = GetColor(255, 255, 255);
static const unsigned Cr_orange = GetColor(255, 45, 00);
static master::GameState gameState = master::GameState::Title;
static const int OptionSize = 3;
static const std::string OptionStr[OptionSize] = { "Play","Config","Exit Game" };
static const int OptionPos[2] = { 100,200 };
static const int OptionDis = 20;
static int SelectedOption = 0;
static const int WaitTimeMS = 150;
static int StartTime = 0;

void master::drawTitleScene()
{
	SetFontSize(40);
	DrawString(100, 120, "Test Title", Cr_white);
	master::drawTitleOptions();
}

void master::drawTitleOptions()
{
	SetFontSize(15);
	for (int i = 0; i < OptionSize; i++) {
		unsigned color = (i == SelectedOption) ? Cr_orange : Cr_white;
		DrawString(OptionPos[0], OptionPos[1] + OptionDis * i, OptionStr[i].c_str(), color);
	}
}

void master::Update()
{
	master::CheckGameStart();
	master::CheckTitleSelect();
}

master::GameState master::GetGameState()
{
	return gameState;
}

void master::SetGameState(master::GameState state)
{
	gameState = state;
}

void master::CheckGameStart()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SetGameState(master::GameState::Game);
		pl::Instantiate();
		ene::Instantiate();
	}
}

void master::CheckTitleSelect()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			SelectedOption = (SelectedOption + 1) % OptionSize;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			SelectedOption--;
			SelectedOption = (SelectedOption < 0) ?
							SelectedOption + OptionSize : SelectedOption;
			StartTime = GetNowCount();
		}
	}
}

