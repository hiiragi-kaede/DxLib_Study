#include "GameMaster.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include"Enemy.hpp"
#include"string"
#include"Config.hpp"
#include"GameOver.hpp"
#include"util.hpp"

enum class GameState { Title, Game, Config, GameOver };

static GameState gameState = GameState::Title;

static const unsigned Cr_white = GetColor(255, 255, 255);
static const unsigned Cr_orange = GetColor(255, 45, 00);

static const int TitleSize = 3;
static const std::string TitleStr[TitleSize] = { "Play","Config","Exit Game" };
static const int TitlePos[2] = { 100,200 };
static const int TitleDist = 20;
static int TitleSelectNum = 0;

static const int WaitTimeMS = 150;
static int StartTime = 0;

void master::Update()
{
	switch (gameState)
	{
	case GameState::Title:
		master::drawTitleScene();
		master::TitleUpdate();
		break;
	case GameState::Game:
		pl::Update();

		ene::Update();

		util::EscToTitle();
		break;
	case GameState::Config:
		cfg::Update();
		break;
	case GameState::GameOver:
		over::Update();
		break;
	default:
		break;
	}
}

void master::drawTitleScene()
{
	SetFontSize(40);
	DrawString(100, 120, "Test Title", Cr_white);
	master::drawTitles();
}

void master::drawTitles()
{
	SetFontSize(15);
	for (int i = 0; i < TitleSize; i++) {
		unsigned color = (i == TitleSelectNum) ? Cr_orange : Cr_white;
		DrawString(TitlePos[0], TitlePos[1] + TitleDist * i, TitleStr[i].c_str(), color);
	}
}

void master::TitleUpdate()
{
	master::CheckGameStart();
	master::MoveToConfig();
	master::UpdateTitleSelect();
	master::ExitGame();
}


void master::CheckGameStart()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 0) {
		SetToGame();
		ResetSelectNum();
		pl::Instantiate();
		ene::Instantiate();
		WaitTimer(300);
	}
}

void master::UpdateTitleSelect()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			TitleSelectNum = (TitleSelectNum + 1) % TitleSize;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			TitleSelectNum--;
			TitleSelectNum = (TitleSelectNum < 0) ?
							TitleSelectNum + TitleSize : TitleSelectNum;
			StartTime = GetNowCount();
		}
	}
}

void master::ExitGame()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 2) {
		DxLib_End();
	}
}

void master::MoveToConfig()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 1) {
			master::SetToConfig();
			ResetSelectNum();
			StartTime = GetNowCount();
			WaitTimer(300);
		}
	}
}

void master::ResetSelectNum()
{
	TitleSelectNum = 0;
}

void master::SetToTitle()
{
	gameState = GameState::Title;
}

void master::SetToGame()
{
	gameState = GameState::Game;
}

void master::SetToConfig()
{
	gameState = GameState::Config;
}

void master::SetToGameOver()
{
	gameState = GameState::GameOver;
}
