#include "GamePlay.h"
#include <stdio.h>
#include <time.h>
#include "Player.h"

GamePlay::GamePlay(DataManager *_DataManager) : Scene(_DataManager)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, camera);
	m_CharacterManager = new CharacterManager(_DataManager, m_pMapData, camera);
}

GamePlay::~GamePlay()
{
	delete m_CharacterManager;
}

void GamePlay::init()
{
	end = false;
	m_pMapData->init();
	m_CharacterManager->init();
	m_CharacterManager->add(new Player(m_pDataManager, m_pMapData, camera, D3DXVECTOR2(200, 200)));
	m_Enemy->init();
}

void GamePlay::update()
{
	m_pMapData->update();
	m_CharacterManager->update();
	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	{
		end = true;
	}
	m_Enemy->updata();
}

void GamePlay::draw()
{
	m_pMapData->draw();
	m_CharacterManager->draw();
	m_Enemy->draw();
}

GAME_MODE GamePlay::nextScene()
{
	return GAME_MODE_GAMEOVER;
}

//test