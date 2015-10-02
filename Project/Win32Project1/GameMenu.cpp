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

	if (gsKeyState(VK_SPACE) == GSKS_DOWN)	//チュートリアルとかのシーンの分岐に使うやつ
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
	//メニュー切り替えの動き？のとこ
}

GAME_MODE GameMenu::nextScene()
{
	return GAME_MODE_TUTORIAL;
}

GAME_MODE GameMenu::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMEPLAY;
}