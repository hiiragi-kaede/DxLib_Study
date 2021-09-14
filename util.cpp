#include "util.hpp"
#include "DxLib.h"

int util::DrawRotaGraph(int x, int y, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag) {
	int GraphW, GraphH;
	GetGraphSize(GrHandle, &GraphW, &GraphH);
	return DxLib::DrawRotaGraph(x + GraphW / 2, y + GraphH / 2, ExtRate, Angle, GrHandle, TRUE);
}
