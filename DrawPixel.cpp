#include"DxLib.h"
#include"Character.hpp"
#include<vector>
#include<math.h>

#define SHOTSIZE 10

void UpdatePlayer(Player* player, std::vector<Shot*> shots,int& shotBflag);
void UpdateEnemy(Enemy* enemy,Player* player);
void UpdateShotState(Player* player,Shot* shot);
void UpdateShotView(Shot* shot);
void UpdateEnemyShotView(EnemyShot* shot);
void HitCheck(Enemy* enemy, std::vector<Shot*> shots);
void EnemyShotCtrl(Enemy* enemy, Player* player);

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);


	Player* player = new Player(288, 400, LoadGraph("img/PlayerImg.png"), 64);

	EnemyShot* es = new EnemyShot(0, 0, LoadGraph("img/EnemyShot.png"), 10, 0);
	Enemy* enemy = new Enemy(0, 50, LoadGraph("img/EnemyImg.png"), 50,
		1, 0, 0, LoadGraph("img/EnemyInDmg.png"),
		es, 0);

	std::vector<Shot*> shots;
	for (int i = 0; i < SHOTSIZE; i++) {
		shots.push_back(new Shot(0, 0, LoadGraph("img/Shot.png"), 10, 0));
	}
	int shotBflag = 0;

	while (1) {
		ClearDrawScreen();

		
		UpdatePlayer(player, shots, shotBflag);

		UpdateEnemy(enemy, player);

		HitCheck(enemy, shots);

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DXライブラリ使用の終了処理

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

void UpdateEnemyShotView(EnemyShot* shot) {
	if (shot->getFlag() == 1) {
		shot->setX(int(shot->getX() + shot->getDx()));
		shot->setY(int(shot->getY() + shot->getDy()));
		if (shot->getY() > 480 || shot->getY() <0 ||
			shot->getX() > 640 || shot->getX() < 0 ) {
			shot->setFlag(0);
		}

		DrawGraph(shot->getX(), shot->getY(), shot->getGraph(), TRUE);
	}
}

void UpdateEnemy(Enemy* enemy,Player* player) {
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

			if (((EneHitBox.Left>ShotHitBox.Left && EneHitBox.Left < ShotHitBox.Left + ShotHitBox.W) ||
				(ShotHitBox.Left > EneHitBox.Left && ShotHitBox.Left < EneHitBox.Left + EneHitBox.W)) &&
				((EneHitBox.Up > ShotHitBox.Up && EneHitBox.Up < ShotHitBox.Up + ShotHitBox.H) ||
				(ShotHitBox.Up > EneHitBox.Up && ShotHitBox.Up < EneHitBox.Up + EneHitBox.H))) {

				//接触した場合弾は消える
				shot->setFlag(0);

				enemy->setDamageFlag(1);
				enemy->setDamageCounter(0);
			}
		}
	}
}
