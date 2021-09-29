#include "GameOver.hpp"
#include"GameMaster.hpp"
#include"DxLib.h"
#include"Color.hpp"
#include<string>

static const int GameOverSize = 2;
static const std::string GameOverStr[GameOverSize] = { "もう一度","タイトルへ"};
static const int TitlePos[2] = { 100,200 };
static const int TitleDist = 20;
static int SelectNum = 0;

static const int WaitTimeMS = 150;
static int StartTime = 0;

void over::drawGameOvers()
{
	SetFontSize(40);
	DrawString(100, 120, "Game Over", color::getWhite());

	SetFontSize(15);
	for (int i = 0; i < GameOverSize; i++) {
		unsigned color = (i == SelectNum) ? color::getOrange() : color::getWhite();
		DrawString(TitlePos[0], TitlePos[1] + TitleDist * i, GameOverStr[i].c_str(), color);
	}
}

void over::Update()
{
	over::drawGameOvers();
	over::UpdateGameOverSelect();
	over::CheckSelect();
}

void over::UpdateGameOverSelect()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			SelectNum = (SelectNum + 1) % GameOverSize;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			SelectNum--;
			SelectNum = (SelectNum < 0) ?
				SelectNum + GameOverSize : SelectNum;
			StartTime = GetNowCount();
		}
	}
}

void over::CheckSelect()
{
	switch (SelectNum) {
	case 0:
		ChangeState(master::GameState::Game);
		break;
	case 1:
		ChangeState(master::GameState::Title);
		break;
	default:
		break;
	}
}

void over::ChangeState(master::GameState state)
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			master::SetGameState(state);
			ResetSelectNum();
			StartTime = GetNowCount();
			WaitTimer(300);
		}
	}
}

void over::ResetSelectNum()
{
	SelectNum = 0;
}
