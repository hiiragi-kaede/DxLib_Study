#pragma once

#include"Character.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include<vector>

namespace ene {
	void Instantiate();
	void Update();
}

void UpdateEnemy(Player* player);
void UpdateEnemyShotView();
void HitCheck(std::vector<Shot*> shots);
void EnemyShotCtrl(Player* player);
void AttackPlayer(Player* player);