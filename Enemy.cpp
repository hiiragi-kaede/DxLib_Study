#include "Enemy.hpp"
#include"Character.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include<vector>

static EnemyShot* es;
static Enemy* enemy;

void ene::Instantiate() {
	es = new EnemyShot(0, 0, LoadGraph("img/EnemyShot.png"), 10, 0);
	enemy = new Enemy(0, 50, LoadGraph("img/EnemyImg.png"), 50,
		1, 0, 0, LoadGraph("img/EnemyInDmg.png"),
		es, 0);
}

void ene::Update()
{
	Player* player = pl::getPlayer();
	std::vector<Shot*> shots = pl::getShots();
	UpdateEnemy(enemy, player);
	HitCheck(enemy, shots);
}

void UpdateEnemyShotView(EnemyShot* shot) {
	if (shot->getFlag() == 1) {
		shot->setX(int(shot->getX() + shot->getDx()));
		shot->setY(int(shot->getY() + shot->getDy()));
		if (shot->getY() > 480 || shot->getY() < 0 ||
			shot->getX() > 640 || shot->getX() < 0) {
			shot->setFlag(0);
		}

		DrawGraph(shot->getX(), shot->getY(), shot->getGraph(), TRUE);
	}
}

void UpdateEnemy(Enemy* enemy, Player* player) {
	int EnemyDir = enemy->getDir();
	int EnemyX = enemy->getX();
	int EnemyY = enemy->getY();

	if (enemy->getDamageFlag() == 1) {//ダメージアニメーション中
		DrawGraph(enemy->getX(), enemy->getY(), enemy->getDamageGraph(), TRUE);

		enemy->setDamageCounter(enemy->getDamageCounter() + 1);

		if (enemy->getDamageCounter() == 30) {
			enemy->setDamageFlag(0);
		}
	}
	else {//ダメージアニメーション中でなければ
		if (EnemyDir == 1) enemy->setX(enemy->getX() + 3);
		if (EnemyDir == 0) enemy->setX(enemy->getX() - 3);

		if (enemy->getX() > 640 - 64)
		{
			enemy->setX(640 - 64);
			enemy->setDir(0);
		}

		if (enemy->getX() < 0)
		{
			enemy->setX(0);
			enemy->setDir(1);
		}

		DrawGraph(enemy->getX(), enemy->getY(), enemy->getGraph(), TRUE);

		EnemyShotCtrl(enemy, player);
	}
	UpdateEnemyShotView(enemy->getShot());
}

void EnemyShotCtrl(Enemy* enemy, Player* player) {
	enemy->setShotCounter(enemy->getShotCounter() + 1);

	if (enemy->getShotCounter() == 60) {
		if (enemy->getShot()->getFlag() == 0) {
			int esW, esH, EneW, EneH;
			GetGraphSize(enemy->getGraph(), &EneW, &EneH);
			GetGraphSize(enemy->getShot()->getGraph(), &esW, &esH);

			enemy->getShot()->setX(enemy->getX() + EneW / 2 - esW / 2);
			enemy->getShot()->setY(enemy->getY() + EneH / 2 - esH / 2);

			//弾の移動速度を設定する
			double sb, sbx, sby, bx, by, sx, sy;
			sx = enemy->getShot()->getX() + esW / 2.0;
			sy = enemy->getShot()->getY() + esH / 2.0;

			int Pw, Ph;
			GetGraphSize(player->getGraph(), &Pw, &Ph);
			bx = player->getX() + Pw / 2.0;
			by = player->getY() + Ph / 2.0;

			sbx = bx - sx;
			sby = by - sy;

			sb = sqrt(sbx * sbx + sby * sby);

			enemy->getShot()->setDx(sbx / sb * 8);
			enemy->getShot()->setDy(sby / sb * 8);

			enemy->getShot()->setFlag(1);
		}
		enemy->setShotCounter(0);
	}
}

void HitCheck(Enemy* enemy, std::vector<Shot*> shots) {
	for (auto shot : shots) {
		if (shot->getFlag() == 1) {
			HitBox EneHitBox = enemy->getHitBox();
			HitBox ShotHitBox = shot->getHitBox();

			if (HitBoxCheck(EneHitBox, ShotHitBox)) {

				//接触した場合弾は消える
				shot->setFlag(0);

				enemy->setDamageFlag(1);
				enemy->setDamageCounter(0);
			}
		}
	}
}