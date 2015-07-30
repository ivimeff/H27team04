#include "GameOver.h"

GameOver::GameOver(DataManager *_DataManager) : Scene(_DataManager) {}

GameOver::~GameOver()
{

}

void GameOver::init()
{
	end = false;
	over_x = 0;
	over_y = 0;
}

void GameOver::update()
{
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}
}

void GameOver::draw()
{
	gsDraw2D(m_pDataManager->over, over_x, over_y);
}

GAME_MODE GameOver::nextScene()
{
	return GAME_MODE_GAMETITLE;
}