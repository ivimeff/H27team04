#include "GameMenu.h"
#include <stdio.h>

GameMenu::GameMenu(DataManager *_DataManager) : Scene(_DataManager)
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
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}

	if (gsKeyState(VK_SPACE) == GSKS_DOWN)	//�`���[�g���A���Ƃ��̃V�[���̕���Ɏg�����
	{
		side = true;
	}
}

void GameMenu::draw()
{
	gsDraw2D(m_pDataManager->menu, menu_x, menu_y);
	gsDraw2D(m_pDataManager->green, menu_t_x, menu_t_y);
	gsDraw2D(m_pDataManager->blue, menu_t_x, menu_p_y);
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