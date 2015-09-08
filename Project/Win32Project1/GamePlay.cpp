#include "GamePlay.h"
#include <stdio.h>
#include <time.h>

GamePlay::GamePlay(DataManager *_DataManager) : Scene(_DataManager)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, camera);
	m_player = new Player(_DataManager, m_pMapData, camera, D3DXVECTOR2(200, 200));
}

GamePlay::~GamePlay()
{
	delete m_player;
}

void GamePlay::init()
{
	end = false;
	m_pMapData->init();
}

void GamePlay::update()
{
	m_pMapData->update();
	m_player->update();
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}
}

void GamePlay::draw()
{
	m_pMapData->draw();
	m_player->draw();

}

GAME_MODE GamePlay::nextScene()
{
	return GAME_MODE_GAMEOVER;
}

//test