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
static const int HitSize = 50;
static const int MaxHP = 1000;

void ene::Instantiate() {
	es = new EnemyShot(0, 0, LoadGraph("img/EnemyShot.png"), 10, 0);
	enemy = new Enemy(0, 50, LoadGraph("img/EnemyImg.png"), HitSize, MaxHP,
		1, 0, 0, LoadGraph("img/EnemyInDmg.png"),
		es, 0);
}

void ene::Update()
{
	Player* player = pl::getPlayer();
	std::vector<Shot*> shots = pl::getShots();
	enemy->Update(player,shots);
	es->Update(enemy, player);
}

/*
####################################################################################################
*/

Enemy::Enemy(int x, int y, int graph, int hitW, int hitH, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter) :
	Character(x, y, graph, hitW, hitH), MaxHP(MaxHP), HP(MaxHP), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph), shot(es), shotCounter(sCounter) {}

Enemy::Enemy(int x, int y, int graph, int hitSize, int MaxHP, int dir, int dFlag, int dCounter, int dGraph, EnemyShot* es, int sCounter) :
	Character(x, y, graph, hitSize), MaxHP(MaxHP), HP(MaxHP), dir(dir), damageFlag(dFlag), damageCounter(dCounter), damageGraph(dGraph), shot(es), shotCounter(sCounter) {}

void Enemy::Update(Player* player, std::vector<Shot*> shots)
{
	Enemy::UpdateEnemy(player);
	Enemy::UpdateHPView();
	HitCheck(shots);
}

EnemyShot::EnemyShot(int x, int y, int graph, int hitW, int hitH, int flag) :
	Shot(x, y, graph, hitW, hitH, flag), dx(0), dy(0) {}

EnemyShot::EnemyShot(int x, int y, int graph, int hitSize, int flag) :
	Shot(x, y, graph, hitSize, flag), dx(0), dy(0) {}

EnemyShot::EnemyShot(EnemyShot* es) : Shot(es->getX(), es->getY(), es->getGraph(), es->getHitW(), es->getHitH(), es->getFlag()), dx(0), dy(0) {}

void EnemyShot::Update(Enemy* enemy, Player* player)
{
	EnemyShot::UpdateEnemyShotView();
	//ダメージモーション中は攻撃しない
	if (enemy->getDamageFlag() == 0) {
		EnemyShot::EnemyShotCtrl(enemy, player);
		EnemyShot::AttackPlayer(player);
	}
}

void Enemy::UpdateHPView()
{
	//赤色の値を取得
	unsigned int Cr = GetColor(255, 0, 0);

	std::string tmp = "Ene HP:" + std::to_string(Enemy::getHP());
	char const* hp_char = tmp.c_str();
	DrawString(300, 0, hp_char, Cr);
}

void EnemyShot::UpdateEnemyShotView() {
	if (EnemyShot::getFlag() == 1) {
		EnemyShot::setX(int(EnemyShot::getX() + EnemyShot::getDx()));
		EnemyShot::setY(int(EnemyShot::getY() + EnemyShot::getDy()));
		if (EnemyShot::getY() > 480 || EnemyShot::getY() < 0 ||
			EnemyShot::getX() > 640 || EnemyShot::getX() < 0) {
			EnemyShot::setFlag(0);
		}

		DrawGraph(EnemyShot::getX(), EnemyShot::getY(), EnemyShot::getGraph(), TRUE);
	}
}

void Enemy::UpdateEnemy(Player* player) {
	int EnemyDir = Enemy::getDir();

	if (Enemy::getDamageFlag() == 1) {//ダメージアニメーション中
		DrawGraph(Enemy::getX(), Enemy::getY(), Enemy::getDamageGraph(), TRUE);

		Enemy::setDamageCounter(Enemy::getDamageCounter() + 1);

		if (Enemy::getDamageCounter() == 30) {
			Enemy::setDamageFlag(0);
		}
	}
	else {//ダメージアニメーション中でなければ
		if (EnemyDir == 1) Enemy::setX(Enemy::getX() + 3);
		if (EnemyDir == 0) Enemy::setX(Enemy::getX() - 3);

		if (Enemy::getX() > 640 - 64)
		{
			Enemy::setX(640 - 64);
			Enemy::setDir(0);
		}

		if (Enemy::getX() < 0)
		{
			Enemy::setX(0);
			Enemy::setDir(1);
		}

		DrawGraph(Enemy::getX(), Enemy::getY(), Enemy::getGraph(), TRUE);

	}
}

void EnemyShot::EnemyShotCtrl(Enemy* enemy, Player* player) {
	enemy->setShotCounter(enemy->getShotCounter() + 1);

	if (enemy->getShotCounter() == 60) {
		if (EnemyShot::getFlag() == 0) {
			int esW, esH, EneW, EneH;
			GetGraphSize(enemy->getGraph(), &EneW, &EneH);
			GetGraphSize(enemy->getShot()->getGraph(), &esW, &esH);

			EnemyShot::setX(enemy->getX() + EneW / 2 - esW / 2);
			EnemyShot::setY(enemy->getY() + EneH / 2 - esH / 2);

			//弾の移動速度を設定する
			double sb, sbx, sby, bx, by, sx, sy;
			sx = EnemyShot::getX() + esW / 2.0;
			sy = EnemyShot::getY() + esH / 2.0;

			int Pw, Ph;
			GetGraphSize(player->getGraph(), &Pw, &Ph);
			bx = player->getX() + Pw / 2.0;
			by = player->getY() + Ph / 2.0;

			sbx = bx - sx;
			sby = by - sy;

			sb = sqrt(sbx * sbx + sby * sby);

			EnemyShot::setDx(sbx / sb * 8);
			EnemyShot::setDy(sby / sb * 8);

			EnemyShot::setFlag(1);
		}
		enemy->setShotCounter(0);
	}
}

void EnemyShot::AttackPlayer(Player* player)
{
	if (EnemyShot::getFlag() == 1) {
		HitBox PlayerHitBox = player->getHitBox();
		HitBox EShotHitBox = EnemyShot::getHitBox();

		if (HitBoxCheck(PlayerHitBox, EShotHitBox)) {
			//接触した場合弾は消える
			EnemyShot::setFlag(0);

			player->DecreaseHP(attack);
		}
	}
}

void Enemy::HitCheck(std::vector<Shot*> shots) {
	for (auto shot : shots) {
		if (shot->getFlag() == 1) {
			HitBox EneHitBox = Enemy::getHitBox();
			HitBox ShotHitBox = shot->getHitBox();

			if (HitBoxCheck(EneHitBox, ShotHitBox)) {

				//接触した場合弾は消える
				shot->setFlag(0);

				Enemy::setDamageFlag(1);
				Enemy::setDamageCounter(0);

				Enemy::DecreaseHP(1);
			}
		}
	}
}
