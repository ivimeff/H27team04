#include "DxLib.h"
#include "SceneManager.h"
#include "def.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef _DEBUG
#else
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h
	SetWindowText("test");
	SetGraphMode(window::width, window::height, 16);		// ��ʃ��[�h�̃Z�b�g
#endif

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	Renderer* renderer = new Renderer();
	SceneManager* sceneManager = new SceneManager();

	sceneManager->init();
	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		sceneManager->update();
		renderer->begin();
		sceneManager->draw();
		renderer->end();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}