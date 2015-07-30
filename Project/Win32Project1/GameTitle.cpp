#include "GameTitle.h"
#include <stdio.h>

GameTitle::GameTitle(DataManager *_DataManager) : Scene(_DataManager) {}

GameTitle::~GameTitle()
{

}

void GameTitle::init()
{
	end = false;
	title_x = 0;
	title_y = 0;
}

void GameTitle::update()
{
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}
}

void GameTitle::draw()
{
	gsDraw2D(m_pDataManager->title, title_x, title_y);
}

GAME_MODE GameTitle::nextScene()
{
	return GAME_MODE_GAMEPLAY;
}