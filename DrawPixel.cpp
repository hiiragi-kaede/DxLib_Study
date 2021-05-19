#include"DxLib.h"

void UpdatePlayer(int* PlayerX, int* PlayerY, int PlayerGraph, int ShotGraph, int* ShotX, int* ShotY, int* ShotFlag);
void UpdateEnemy(int* EnemyX, int* EnemyY, int EnemyGraph, int* EnemyDir);

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);


	int PlayerGraph = LoadGraph("img/PlayerImg.png");
	int PlayerX = 288, PlayerY = 400;

	int EnemyGraph = LoadGraph("img/EnemyImg.png");
	int EnemyX = 0, EnemyY = 50;

	int EnemyDir = 1;

	int ShotGraph = LoadGraph("img/Shot.png");
	int ShotFlag = 0;
	int ShotX = 0, ShotY = 0;

	while (1) {
		ClearDrawScreen();

		UpdatePlayer(&PlayerX, &PlayerY, PlayerGraph, ShotGraph, &ShotX, &ShotY, &ShotFlag);

		UpdateEnemy(&EnemyX, &EnemyY, EnemyGraph, &EnemyDir);

		ScreenFlip();

		if (ProcessMessage() < 0) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}

void UpdatePlayer(int* PlayerX, int* PlayerY, int PlayerGraph, int ShotGraph, int* ShotX,int* ShotY,int* ShotFlag){

	if (CheckHitKey(KEY_INPUT_UP) == 1) *PlayerY -= 3;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) *PlayerY += 3;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) *PlayerX -= 3;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) *PlayerX += 3;

	if (*PlayerX < 0) *PlayerX = 0;
	if (*PlayerX > 640 - 64) *PlayerX = 640 - 64;

	if (*PlayerY < 0) *PlayerY = 0;
	if (*PlayerY > 480 - 64) *PlayerY = 480 - 64;

	DrawGraph(*PlayerX, *PlayerY, PlayerGraph, FALSE);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1
		&& *ShotFlag == 0) {
		int Pw, Ph, Sw, Sh;

		GetGraphSize(PlayerGraph, &Pw, &Ph);
		GetGraphSize(ShotGraph, &Sw, &Sh);

		*ShotX = (Pw - Sw) / 2 + *PlayerX;
		*ShotY = (Ph - Sh) / 2 + *PlayerY;

		*ShotFlag = 1;
	}

	if (*ShotFlag == 1) {
		*ShotY -= 16;
		if (*ShotY < -80) {
			*ShotFlag = 0;
		}

		DrawGraph(*ShotX, *ShotY, ShotGraph, FALSE);
	}
}

void UpdateEnemy(int* EnemyX, int* EnemyY, int EnemyGraph,int* EnemyDir) {
	if (*EnemyDir == 1) *EnemyX += 3;
	if (*EnemyDir == 0) *EnemyX -= 3;

	if (*EnemyX > 640 - 64)
	{
		*EnemyX = 640 - 64;
		*EnemyDir = 0;
	}

	if (*EnemyX < 0)
	{
		*EnemyX = 0;
		*EnemyDir = 1;
	}

	DrawGraph(*EnemyX, *EnemyY, EnemyGraph, FALSE);
}
