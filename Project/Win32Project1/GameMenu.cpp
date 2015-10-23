#include "GameMenu.h"
#include <DxLib.h>

GameMenu::GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer) : Scene(_DataManager, _Renderer, _GamePad, _Changer)
{
}

void GameMenu::Initialize()
{
	end = false;
	side = false;
	mImageHandle = LoadGraph("Image/menu.png");

}

void GameMenu::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_1) == State::STATE_DOWN)	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
	{
		side = true;
	}

	if (CheckHitKey(KEY_INPUT_J) != 0){	//J�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_GamePlay);//�Q�[����ʂɕύX
	}

	if (CheckHitKey(KEY_INPUT_RETURN) != 0){	//�X�y�[�X�������ꂽ��
		m_SceneChanger->ChangeScene(eScene_Tutorial);//�`���[�g���A���ɕύX
	}
}

void GameMenu::Draw()
{
	/*m_Renderer->drawTexture(m_pDataManager->menu, menu_x, menu_y);
	m_Renderer->drawTexture(m_pDataManager->green, menu_t_x, menu_t_y);
	m_Renderer->drawTexture(m_pDataManager->blue, menu_t_x, menu_p_y);*/

	Scene::Draw();
	//�����\��
	DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 0, 0));
	DrawString(0, 20, "J�L�[�������ƃQ�[����ʂɈڍs���܂��B", GetColor(255, 0, 0));
	DrawString(0, 40, "Enter�L�[�������ƃ`���[�g���A����ʂɈڍs���܂��B", GetColor(255, 0, 0));
}