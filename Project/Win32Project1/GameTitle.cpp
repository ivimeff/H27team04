#include "GameTitle.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

GameTitle::GameTitle(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer) : Scene(_DataManager, _Renderer, _GamePad,_Changer) {}

void GameTitle::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/title.png");
	timer = 0;
}

void GameTitle::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (Key_Get(KEY_INPUT_SPACE) != 0){	//�X�y�[�X�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_Menu);//���j���[�ɕύX
	}
	timer++;
}

void GameTitle::Draw()
{
	//m_Renderer->drawTexture(m_pDataManager->title, title_x, title_y);
	Scene::Draw();
#ifdef _DEBUG
	//�����\��
	DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "Space�L�[�������ƃ��j���[��ʂɈڍs���܂��B", GetColor(255, 0, 0));
#endif

	if ((timer % 100) < 50)
	{
		m_Renderer->drawTexture(m_pDataManager->space,540,500);
	}

}
