#include "Config.hpp"
#include"GameMaster.hpp"
#include"DxLib.h"
#include<string>

static const int ConfigSize = 4;
static const std::string ConfigStr[ConfigSize] = { "“ïˆÕ“x","BGM vol","SE vol","–ß‚é" };
static const int TitlePos[2] = { 100,200 };
static const int TitleDist = 20;
static const int ConfigPos[2] = { 200,200 };
static int SelectNum = 0;

static const int DifficultSize = 3;
static const std::string DiffStr[DifficultSize] = { "Easy","Normal","Hard" };
static int Difficulty = 1;

static int BGMvol = 5;
static int SEvol = 5;
static const int MaxVol = 10;

static const int WaitTimeMS = 150;
static int StartTime = 0;

void cfg::Update()
{
	cfg::UpdateConfigSelect();
	cfg::ChangeConfig();
	cfg::drawConfigs();
}

void cfg::drawConfigs()
{
	SetFontSize(40);
	DrawString(100, 120, "Config", master::getWhite());

	SetFontSize(15);
	for (int i = 0; i < ConfigSize; i++) {
		unsigned color = (i == SelectNum) ? master::getOrange() : master::getWhite();
		DrawString(TitlePos[0], TitlePos[1] + TitleDist * i, ConfigStr[i].c_str(), color);
		std::string configMessage = "";
		switch (i) {
		case 0:
			configMessage = DiffStr[Difficulty];
			break;
		case 1:
			configMessage = std::to_string(BGMvol);
			break;
		case 2:
			configMessage = std::to_string(SEvol);
			break;
		default:
			break;
		}
		DrawString(ConfigPos[0], ConfigPos[1] + TitleDist * i, configMessage.c_str(), master::getWhite());
	}
}

void cfg::UpdateConfigSelect()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			SelectNum = (SelectNum + 1) % ConfigSize;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			SelectNum--;
			SelectNum = (SelectNum < 0) ?
				SelectNum + ConfigSize : SelectNum;
			StartTime = GetNowCount();
		}
	}
}


void cfg::ChangeSelectNum(int& ChangeNum, int Limit)
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			ChangeNum = (ChangeNum + 1) % Limit;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_LEFT)) {
			ChangeNum--;
			ChangeNum = (ChangeNum < 0) ?
				ChangeNum + Limit : ChangeNum;
			StartTime = GetNowCount();
		}
	}
}

int cfg::GetDifficulty()
{
	return Difficulty;
}

void cfg::ChangeConfig()
{
	switch (SelectNum) {
	case 0:
		cfg::ChangeSelectNum(Difficulty, DifficultSize);
		break;
	case 1:
		cfg::ChangeSelectNum(BGMvol, MaxVol);
		break;
	case 2:
		cfg::ChangeSelectNum(SEvol, MaxVol);
		break;
	case 3:
		if (GetNowCount() - StartTime > WaitTimeMS) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				master::SetGameState(master::GameState::Title);
				StartTime = GetNowCount();
				WaitTimer(300);
			}
		}
		break;
	default:
		break;
	}
}