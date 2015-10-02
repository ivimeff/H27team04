#include "GameMenu.h"
#include <stdio.h>
#include <DxLib.h>

GameMenu::GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad) : Scene(_DataManager, _Renderer, _GamePad)
{

}

GameMenu::~GameMenu()
{

}

void GameMenu::init()
{
	end = false;
	side = false;
	menu_x = 0;
	menu_y = 0;
}

void GameMenu::update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
	{
		side = true;
	}
}

void GameMenu::draw()
{
	m_Renderer->drawTexture(m_pDataManager->menu, menu_x, menu_y);
	m_Renderer->drawTexture(m_pDataManager->green, menu_t_x, menu_t_y);
	m_Renderer->drawTexture(m_pDataManager->blue, menu_t_x, menu_p_y);
}

void GameMenu::shift()
{
	//���j���[�؂�ւ��̓����H�̂Ƃ�
}

GAME_MODE GameMenu::nextScene()
{
	return GAME_MODE_TUTORIAL;
}

GAME_MODE GameMenu::sideScene()	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
{
	return GAME_MODE_GAMEPLAY;
}