#pragma once

#include"Character.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include<vector>

namespace ene {
	void Instantiate();
	void Update();
}

void UpdateEnemy(Enemy* enemy, Player* player);
void UpdateEnemyShotView(EnemyShot* shot);
void HitCheck(Enemy* enemy, std::vector<Shot*> shots);
void EnemyShotCtrl(Enemy* enemy, Player* player);