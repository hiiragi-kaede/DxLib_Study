#include"DxLib.h"

//プログラムはWinMainから始まる。
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DXライブラリ初期化処理
		return -1;//エラーが起きたら直ちに終了
	}

	//描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	int x = 0, y = 0;
	while(1) {
		//画面に描かれているものを一回全部消す
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_LEFT) == 1) x -= 8;
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) x += 8;
		if (CheckHitKey(KEY_INPUT_UP) == 1) y -= 8;
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) y += 8;

		LoadGraphScreen(x,y, "img/JK.png", FALSE);

		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		WaitTimer(20);

		//Windowsからの命令がエラーなら即時終了
		//手を加えなければ永遠にループするようなプログラムにはループの中に一つはこの処理を加える必要がある。
		if (ProcessMessage() == -1) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}
	DxLib_End(); //DXライブラリ使用の終了処理

	return 0;
}