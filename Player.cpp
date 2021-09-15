#include "Player.hpp"
#include"Character.hpp"
#include"DxLib.h"
#include"util.hpp"

static Player* player;
static std::vector<Shot*> shots;
static int shotBflag = 0;
static const int move_speed = 3;
static const int shot_size = 10;
static const int player_hitbox_size = 64;
static const int shot_hitbox_size = 10;

void pl::Instantiate() {
	player = new Player(288, 400, LoadGraph("img/PlayerImg.png"), player_hitbox_size);
	for (int i = 0; i < shot_size; i++) {
		shots.push_back(new Shot(0, 0, LoadGraph("img/Shot.png"), shot_hitbox_size, 0));
	}
}

void pl::Update() {
	UpdatePlayer();
}

Player* pl::getPlayer()
{
	return player;
}

std::vector<Shot*> pl::getShots()
{
	return shots;
}

void UpdatePlayer() {

	if (CheckHitKey(KEY_INPUT_UP) == 1) player->setY(player->getY() - move_speed);
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) player->setY(player->getY() + move_speed);
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) player->setX(player->getX() - move_speed);
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) player->setX(player->getX() + move_speed);

	if (player->getX() < 0) player->setX(0);
	if (player->getX() > 640 - 64) player->setX(640 - 64);

	if (player->getY() < 0) player->setY(0);
	if (player->getY() > 480 - 64) player->setY(480 - 64);

	util::DrawRotaGraph(player->getX(), player->getY(), 1.0, 0, player->getGraph(), TRUE);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		if (shotBflag == 0) {
			for (size_t i = 0; i < shots.size(); i++) {
				if (shots[i]->getFlag() == 0) {
					UpdateShotState(shots[i]);
					break;
				}
			}
			shotBflag = 1;
		}
		else {
			shotBflag = 0;
		}
	}

	for (size_t i = 0; i < shots.size(); i++) {
		if (shots[i]->getFlag() == 1) {
			UpdateShotView(shots[i]);
		}
	}
}

void UpdateShotState(Shot* shot) {
	int Pw, Ph, Sw, Sh;

	GetGraphSize(player->getGraph(), &Pw, &Ph);
	GetGraphSize(shot->getGraph(), &Sw, &Sh);

	shot->setX((Pw - Sw) / 2 + player->getX());
	shot->setY((Ph - Sh) / 2 + player->getY());

	shot->setFlag(1);
}


void UpdateShotView(Shot* shot) {
	if (shot->getFlag() == 1) {
		shot->setY(shot->getY() - 16);
		if (shot->getY() < -80) {
			shot->setFlag(0);
		}

		DrawGraph(shot->getX(), shot->getY(), shot->getGraph(), TRUE);
	}
}

