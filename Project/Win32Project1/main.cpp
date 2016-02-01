#include "DxLib.h"
#include "SceneManager.h"
#include "def.h"
#include "Keyboard.h"
#include "resource.h"
#pragma warning(disable:4996)

void ShowConsole()
{
	/*�R���\�[���E�B���h�E���쐬*/
	AllocConsole();
	freopen(
		"CONIN$",      //�V�����t�@�C���̃p�X
		"r",       //�A�N�Z�X���̎��
		stdin       //FILE�\���̂ւ̃|�C���^
		);
	freopen(
		"CONOUT$",
		"w",
		stdout
		);
}

class Fps{
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps(){
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update(){
		if (mCount == 0){ //1�t���[���ڂȂ玞�����L��
			mStartTime = GetNowCount();
		}
		if (mCount == N){ //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw(){
		DrawFormatString(window::width - 80, 0, GetColor(255, 255, 255), "FPS:%.1f", mFps);
	}

	void Wait(){
		int tookTime = GetNowCount() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0){
			Sleep(waitTime);	//�ҋ@
		}
	}
};

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ShowConsole();
#ifndef _DEBUG
#else
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h
	SetWindowText("test");
#endif
	SetWindowIconID(TEST);
	SetMainWindowText("�ؕ|���{");
	SetGraphMode(window::width, window::height, 16);		// ��ʃ��[�h�̃Z�b�g

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Fps fps;

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	Renderer renderer;
	SoundManager sound;
	//SceneManager* sceneManager = new SceneManager();

	SceneManager sceneManager(&renderer, &sound);
	sceneManager.Initialize();
	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Update();
		Key_Update();
		sceneManager.Update();	//�X�V
		renderer.begin();
		sceneManager.Draw();	//�`��
//#ifdef _DEBUG
		fps.Draw();
//#endif
		renderer.end();
		fps.Wait();
	}
	sceneManager.Finalize();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}