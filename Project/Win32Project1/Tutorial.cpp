#include "Tutorial.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial::Tutorial(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Change) : Scene(_DataManager, _Renderer, _GamePad,_Change)
{

}

void Tutorial::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/tuto.png");
}

void Tutorial::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) != 0){	//�X�y�[�X�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_Menu);//���j���[�ɕύX
	}
}

void Tutorial::Draw()
{
	//m_Renderer->drawTexture(m_pDataManager->tuto, tuto_x, tuto_y);
	Scene::Draw();
	//�����\��
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Space�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 0, 0));
}

