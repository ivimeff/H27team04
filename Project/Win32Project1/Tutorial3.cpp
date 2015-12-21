#include "Tutorial3.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial3::Tutorial3(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Change) : Scene(_DataManager, _Renderer, _GamePad, _Change)
{

}

void Tutorial3::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/tuto3.png");
}

void Tutorial3::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_SPACE) != 0){	//�X�y�[�X�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_Menu);//���j���[�ɕύX
	}
}

void Tutorial3::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//�����\��
	DrawString(0, 0, "�`���[�g���A����ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Space�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 0, 0));
#endif
}