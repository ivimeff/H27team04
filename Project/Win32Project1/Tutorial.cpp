#include "Tutorial.h"
#include <stdio.h>

Tutorial::Tutorial(DataManager *_DataManager) : Scene(_DataManager)
{

}

Tutorial::~Tutorial()
{

}

void Tutorial::init()
{
	end = false;
	tuto_x = 0;
	tuto_y = 0;
}

void Tutorial::update()
{
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}
}

void Tutorial::draw()
{
	gsDraw2D(m_pDataManager->tuto, tuto_x, tuto_y);
}

GAME_MODE Tutorial::nextScene()
{
	return GAME_MODE_GAMEMENU;
}

GAME_MODE Tutorial::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMEMENU;
}