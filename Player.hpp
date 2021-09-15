#pragma once
#include<vector>
#include"Character.hpp"

namespace pl {
	void Instantiate();
	void Update();
	Player* getPlayer();
	std::vector<Shot*> getShots();
}

void UpdatePlayer();
void UpdateShotState(Shot* shot);
void UpdateShotView(Shot* shot);
