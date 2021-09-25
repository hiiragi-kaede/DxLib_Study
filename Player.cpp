#include "Player.hpp"
#include"Character.hpp"
#include"DxLib.h"
#include"util.hpp"
#include<iostream>
#include<string>
#include"GameMaster.hpp"

static Player* player;
static std::vector<Shot*> shots;
static int shotBflag = 0;
static const int move_speed = 3;
static const int shot_size = 10;
static const int player_hitbox_size = 32;
static const int shot_hitbox_size = 10;
static const int max_hp = 3;

void pl::Instantiate() {
	player = new Player(288, 400, LoadGraph("img/PlayerImg.png"), player_hitbox_size, max_hp);
	while (shots.size() < shot_size) {
		shots.push_back(new Shot(0, 0, LoadGraph("img/Shot.png"), shot_hitbox_size, 0));
	}
}

void pl::Update() {
	player->Update();
}

Player* pl::getPlayer()
{
	return player;
}

std::vector<Shot*> pl::getShots()
{
	return shots;
}

/*
####################################################################################################
*/

Shot::Shot(int x, int y, int graph, int hitW, int hitH, int flag) : Character(x, y, graph, hitW, hitH), flag(flag) {}

Shot::Shot(int x, int y, int graph, int hitSize, int flag) : Character(x, y, graph, hitSize), flag(flag) {}

Shot::Shot() : Character(0, 0, 0, shot_hitbox_size), flag(0) {}

Shot::Shot(Shot* s) : Character(s->getX(), s->getY(), s->getGraph(), s->getHitW(), s->getHitH()), flag(s->getFlag()) {}

Player::Player(int x, int y, int graph, int hitSize, int MaxHP) : Character(x, y, graph, hitSize), MaxHP(MaxHP), HP(MaxHP) {}

Player::Player(int x, int y, int graph, int hitW, int hitH, int MaxHP) : Character(x, y, graph, hitW, hitH), MaxHP(MaxHP), HP(MaxHP) {}

void Player::Update()
{
	UpdatePlayer();
	UpdateHPView();
	CheckGameOver();
}

void Player::UpdatePlayer() {

	if (CheckHitKey(KEY_INPUT_UP) == 1) Player::setY(Player::getY() - move_speed);
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) Player::setY(Player::getY() + move_speed);
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) Player::setX(Player::getX() - move_speed);
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) Player::setX(Player::getX() + move_speed);

	if (Player::getX() < 0) Player::setX(0);
	if (Player::getX() > 640 - 64) Player::setX(640 - 64);

	if (Player::getY() < 0) Player::setY(0);
	if (Player::getY() > 480 - 64) Player::setY(480 - 64);

	util::DrawRotaGraph(Player::getX(), Player::getY(), 1.0, 0, Player::getGraph(), TRUE);

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
			shots[i]->UpdateShotView();
		}
	}
}

void Player::UpdateShotState(Shot* shot) {
	int Pw, Ph, Sw, Sh;

	GetGraphSize(Player::getGraph(), &Pw, &Ph);
	GetGraphSize(shot->getGraph(), &Sw, &Sh);

	shot->setX((Pw - Sw) / 2 + Player::getX());
	shot->setY((Ph - Sh) / 2 + Player::getY());

	shot->setFlag(1);
}


void Shot::UpdateShotView() {
	if (Shot::getFlag() == 1) {
		Shot::setY(Shot::getY() - 16);
		if (Shot::getY() < -80) {
			Shot::setFlag(0);
		}

		DrawGraph(Shot::getX(), Shot::getY(), Shot::getGraph(), TRUE);
	}
}

void Player::UpdateHPView()
{
	//”’F‚Ì’l‚ðŽæ“¾
	unsigned int Cr = GetColor(255, 255, 255);

	std::string tmp = "HP:" + std::to_string(player->getHP());
	char const* hp_char = tmp.c_str();
	DrawString(0, 0, hp_char, Cr);
}

void Player::CheckGameOver()
{
	if (player->getHP() == 0) {
		pl::Instantiate();
		master::SetGameState(master::GameState::GameOver);
	}
}

