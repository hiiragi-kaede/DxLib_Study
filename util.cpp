#include "util.hpp"
#include "DxLib.h"
#include"GameMaster.hpp"

int util::DrawRotaGraph(int x, int y, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag) {
	int GraphW, GraphH;
	GetGraphSize(GrHandle, &GraphW, &GraphH);
	return DxLib::DrawRotaGraph(x + GraphW / 2, y + GraphH / 2, ExtRate, Angle, GrHandle, TRUE);
}

void util::EscToTitle()
{
	if (CheckHitKey(KEY_INPUT_DELETE)) {
		master::SetGameState(master::GameState::Title);
	}
}
