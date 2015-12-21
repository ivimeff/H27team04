#include "Tutorial2.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial2::Tutorial2(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Change) : Scene(_DataManager, _Renderer, _GamePad, _Change)
{

}

void Tutorial2::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/tuto2.png");
}

void Tutorial2::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_SPACE) != 0){	//�X�y�[�X�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_Tutorial3);//���j���[�ɕύX
	}
}

void Tutorial2::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//�����\��
	DrawString(0, 0, "�`���[�g���A����ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Space�L�[�������Ǝ��̉�ʂɈڂ�܂��B", GetColor(255, 0, 0));
#endif
}