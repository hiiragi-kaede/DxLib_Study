#include"DxLib.h"

//�v���O������WinMain����n�܂�B
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	if (DxLib_Init() == -1) { //DX���C�u��������������
		return -1;//�G���[���N�����璼���ɏI��
	}

	LoadGraphScreen(0, 0, "img/JK.png",FALSE);
	WaitKey(); //�L�[���͑҂�
	DxLib_End(); //DX���C�u�����g�p�̏I������

	return 0;
}