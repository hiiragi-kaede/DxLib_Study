#include"DxLib.h"

//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
	}

	//�`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	int x = 0, y = 0;
	while(1) {
		//��ʂɕ`����Ă�����̂����S������
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_LEFT) == 1) x -= 8;
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) x += 8;
		if (CheckHitKey(KEY_INPUT_UP) == 1) y -= 8;
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) y += 8;

		LoadGraphScreen(x,y, "img/JK.png", FALSE);

		//����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		WaitTimer(20);

		//Windows����̖��߂��G���[�Ȃ瑦���I��
		//��������Ȃ���Ήi���Ƀ��[�v����悤�ȃv���O�����ɂ̓��[�v�̒��Ɉ�͂��̏�����������K�v������B
		if (ProcessMessage() == -1) break;

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}