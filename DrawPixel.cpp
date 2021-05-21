#include"DxLib.h"
#include"Character.hpp"
#include<vector>

#define SHOTSIZE 10

void UpdatePlayer(Player* player, std::vector<Shot*> shots,int& shotBflag);
void UpdateEnemy(Enemy* enemy);
void UpdateShotState(Player* player,Shot* shot);
void UpdateShotView(Shot* shot);
void HitCheck(Enemy* enemy, std::vector<Shot*> shots);


//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);


	Player* player = new Player(288, 400, LoadGraph("img/PlayerImg.png"));

	Enemy* enemy = new Enemy(0, 50, LoadGraph("img/EnemyImg.png"), 1);

	std::vector<Shot*> shots;
	for (int i = 0; i < SHOTSIZE; i++) {
		shots.push_back(new Shot(0, 0, LoadGraph("img/Shot.png"), 0));
	}
	int shotBflag = 0;

	while (1) {
		ClearDrawScreen();

		
		UpdatePlayer(player, shots, shotBflag);

		UpdateEnemy(enemy);

		HitCheck(enemy, shots);

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}

void UpdatePlayer(Player* player, std::vector<Shot*> shots, int& ShotBFlag) {

	if (CheckHitKey(KEY_INPUT_UP) == 1) player->setY(player->getY() - 3);
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) player->setY(player->getY() + 3);
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) player->setX(player->getX() - 3);
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) player->setX(player->getX() + 3);

	if (player->getX() < 0) player->setX(0);
	if (player->getX() > 640 - 64) player->setX(640 - 64);

	if (player->getY() < 0) player->setY(0);
	if (player->getY() > 480 - 64) player->setY(480 - 64);

	DrawGraph(player->getX(), player->getY(), player->getGraph(), TRUE);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		if (ShotBFlag == 0) {
			for (size_t i = 0; i < shots.size(); i++) {
				if (shots[i]->getFlag() == 0) {
					UpdateShotState(player, shots[i]);
					break;
				}
			}
			ShotBFlag = 1;
		}
		else {
			ShotBFlag = 0;
		}
	}

	for (size_t i = 0; i < shots.size(); i++) {
		if (shots[i]->getFlag() == 1) {
			UpdateShotView(shots[i]);
		}
	}
}

void UpdateShotState(Player* player, Shot* shot) {
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

void UpdateEnemy(Enemy* enemy) {
	int EnemyDir = enemy->getDir();
	int EnemyX = enemy->getX();
	int EnemyY = enemy->getY();

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
}

void HitCheck(Enemy* enemy, std::vector<Shot*> shots) {
	int EneW, EneH, SW, SH;
	GetGraphSize(enemy->getGraph(), &EneW, &EneH);
	GetGraphSize(shots[0]->getGraph(), &SW, &SH);

	for (auto shot : shots) {
		if (shot->getFlag() == 1) {
			if (((shot->getX() > enemy->getX() && shot->getX() < enemy->getX()+ EneW) ||
				(enemy->getX() > shot->getX() && enemy->getX() < shot->getX() + SW)) &&
				((shot->getY() > enemy->getY() && shot->getY() < enemy->getY() + EneH) ||
				(enemy->getY() > shot->getY() && enemy->getY() < shot->getY() + SH))) {

				//�ڐG�����ꍇ�e�͏�����
				shot->setFlag(0);
			}
		}
	}
}
