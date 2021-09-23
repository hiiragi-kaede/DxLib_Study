#pragma once
#include"GameMaster.hpp"

namespace over {
	void drawGameOvers();
	void Update();
	void UpdateGameOverSelect();
	void CheckSelect();
	void ChangeState(master::GameState state);
}