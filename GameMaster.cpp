#include "GameMaster.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include"Enemy.hpp"
#include"string"
#include<iostream>

static const unsigned Cr_white = GetColor(255, 255, 255);
static const unsigned Cr_orange = GetColor(255, 45, 00);

static master::GameState gameState = master::GameState::Title;

static const int TitleSize = 3;
static const std::string TitleStr[TitleSize] = { "Play","Config","Exit Game" };
static const int TitlePos[2] = { 100,200 };
static const int TitleDist = 20;
static int TitleSelectNum = 0;

static const int ConfigSize = 4;
static const std::string ConfigStr[ConfigSize] = { "“ïˆÕ“x","BGM vol","SE vol","–ß‚é" };
static const int ConfigPos[2] = { 200,200 };
static int ConfigSelectNum = 0;

static const int DifficultSize = 3;
static const std::string DifficultyStr[DifficultSize] = { "Easy","Normal","Hard" };
static int Difficulty = 2;

static int BGMvol = 5;
static int SEvol = 5;
static const int MaxVol = 10;

static const int WaitTimeMS = 150;
static int StartTime = 0;

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

void master::drawConfigs()
{
	SetFontSize(40);
	DrawString(100, 120, "Config", Cr_white);

	SetFontSize(15);
	for (int i = 0; i < ConfigSize; i++) {
		unsigned color = (i == ConfigSelectNum) ? Cr_orange : Cr_white;
		DrawString(TitlePos[0], TitlePos[1] + TitleDist * i, ConfigStr[i].c_str(), color);
		std::string configMessage="";
		switch (i) {
		case 0:
			configMessage = DifficultyStr[Difficulty];
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
		DrawString(ConfigPos[0], ConfigPos[1] + TitleDist * i, configMessage.c_str(), Cr_white);
	}
}

void master::TitleUpdate()
{
	master::CheckGameStart();
	master::EditConfig();
	master::UpdateTitleSelect();
	master::ExitGame();
}

void master::ConfigUpdate()
{
	master::UpdateConfigSelect();
	master::ChangeConfig();
	master::drawConfigs();
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
	if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 0) {
		SetGameState(master::GameState::Game);
		pl::Instantiate();
		ene::Instantiate();
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

void master::UpdateConfigSelect()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			ConfigSelectNum = (ConfigSelectNum + 1) % ConfigSize;
			StartTime = GetNowCount();
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			ConfigSelectNum--;
			ConfigSelectNum = (ConfigSelectNum < 0) ?
				ConfigSelectNum + ConfigSize : ConfigSelectNum;
			StartTime = GetNowCount();
		}
	}
}


void master::ChangeConfigSelectNum(int& ChangeNum, int Limit)
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			ChangeNum = (ChangeNum + 1) % Limit;
			StartTime = GetNowCount();
			//DrawString(300, 100, "right", Cr_white);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT)) {
			ChangeNum--;
			ChangeNum = (ChangeNum < 0) ?
				ChangeNum + Limit : ChangeNum;
			StartTime = GetNowCount();
		}
	}
}

void master::ChangeConfig()
{
	switch (ConfigSelectNum) {
	case 0:
		master::ChangeConfigSelectNum(Difficulty, DifficultSize);
		break;
	case 1:
		master::ChangeConfigSelectNum(BGMvol, MaxVol);
		break;
	case 2:
		master::ChangeConfigSelectNum(SEvol, MaxVol);
		break;
	case 3:
		if (GetNowCount() - StartTime > WaitTimeMS) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				master::SetGameState(master::GameState::Title);
				StartTime = GetNowCount();
			}
		}
		break;
	default:
		break;
	}
}

void master::ExitGame()
{
	if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 2) {
		DxLib_End();
	}
}

void master::EditConfig()
{
	if (GetNowCount() - StartTime > WaitTimeMS) {
		if (CheckHitKey(KEY_INPUT_SPACE) && TitleSelectNum == 1) {
			master::SetGameState(master::GameState::Config);
			StartTime = GetNowCount();
		}
	}
}