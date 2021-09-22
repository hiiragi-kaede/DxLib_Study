#include "Enemy.hpp"
#include"Character.hpp"
#include"DxLib.h"
#include"Player.hpp"
#include<vector>
#include<string>

static EnemyShot* es;
static Enemy* enemy;
//プレイヤーへの攻撃力
static const int attack = 1;
static const int MaxHP = 1000;

void ene::Instantiate() {
	es = new EnemyShot(0, 0, LoadGraph("img/EnemyShot.png"), 10, 0);
	enemy = new Enemy(0, 50, LoadGraph("img/EnemyImg.png"), 50, MaxHP,
		1, 0, 0, LoadGraph("img/EnemyInDmg.png"),
		es, 0);
}

void ene::Update()
{
	Player* player = pl::getPlayer();
	std::vector<Shot*> shots = pl::getShots();
	UpdateEnemy(player);
	ene::UpdateHPView();
	HitCheck(shots);
	AttackPlayer(player);
}

void ene::UpdateHPView()
{
	//赤色の値を取得
	unsigned int Cr = GetColor(255, 0, 0);

	std::string tmp = "Ene HP:" + std::to_string(enemy->getHP());
	char const* hp_char = tmp.c_str();
	DrawString(300, 0, hp_char, Cr);
}

void UpdateEnemyShotView() {
	if (es->getFlag() == 1) {
		es->setX(int(es->getX() + es->getDx()));
		es->setY(int(es->getY() + es->getDy()));
		if (es->getY() > 480 || es->getY() < 0 ||
			es->getX() > 640 || es->getX() < 0) {
			es->setFlag(0);
		}

		DrawGraph(es->getX(), es->getY(), es->getGraph(), TRUE);
	}
}

void UpdateEnemy(Player* player) {
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

		EnemyShotCtrl(player);
	}
	UpdateEnemyShotView();
}

void EnemyShotCtrl(Player* player) {
	enemy->setShotCounter(enemy->getShotCounter() + 1);

	if (enemy->getShotCounter() == 60) {
		if (es->getFlag() == 0) {
			int esW, esH, EneW, EneH;
			GetGraphSize(enemy->getGraph(), &EneW, &EneH);
			GetGraphSize(enemy->getShot()->getGraph(), &esW, &esH);

			es->setX(enemy->getX() + EneW / 2 - esW / 2);
			es->setY(enemy->getY() + EneH / 2 - esH / 2);

			//弾の移動速度を設定する
			double sb, sbx, sby, bx, by, sx, sy;
			sx = es->getX() + esW / 2.0;
			sy = es->getY() + esH / 2.0;

			int Pw, Ph;
			GetGraphSize(player->getGraph(), &Pw, &Ph);
			bx = player->getX() + Pw / 2.0;
			by = player->getY() + Ph / 2.0;

			sbx = bx - sx;
			sby = by - sy;

			sb = sqrt(sbx * sbx + sby * sby);

			es->setDx(sbx / sb * 8);
			es->setDy(sby / sb * 8);

			es->setFlag(1);
		}
		enemy->setShotCounter(0);
	}
}

void AttackPlayer(Player* player)
{
	if (es->getFlag() == 1) {
		HitBox PlayerHitBox = player->getHitBox();
		HitBox EShotHitBox = es->getHitBox();

		if (HitBoxCheck(PlayerHitBox, EShotHitBox)) {
			//接触した場合弾は消える
			es->setFlag(0);

			player->DecreaseHP(attack);
		}
	}
}

void HitCheck(std::vector<Shot*> shots) {
	for (auto shot : shots) {
		if (shot->getFlag() == 1) {
			HitBox EneHitBox = enemy->getHitBox();
			HitBox ShotHitBox = shot->getHitBox();

			if (HitBoxCheck(EneHitBox, ShotHitBox)) {

				//接触した場合弾は消える
				shot->setFlag(0);

				enemy->setDamageFlag(1);
				enemy->setDamageCounter(0);

				enemy->DecreaseHP(1);
			}
		}
	}
}
