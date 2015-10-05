#include "GamePlay.h"
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include <DxLib.h>

GamePlay::GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad) : Scene(_DataManager, _Renderer, _GamePad)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, _Renderer, camera);
	gamePlayBundle = new GamePlayBundle(_DataManager, m_Renderer, m_pMapData, camera, _GamePad);
	m_CharacterManager = new CharacterManager(gamePlayBundle);
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
	m_CharacterManager->add(new Player(gamePlayBundle, def::Vector2(200, 200)));
}

void GamePlay::update()
{
	m_pMapData->update();
	m_CharacterManager->update();
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}
}

void GamePlay::draw()
{
	m_pMapData->draw();
	m_CharacterManager->draw();

}

GAME_MODE GamePlay::nextScene()
{
	return GAME_MODE_GAMEOVER;
}

GAME_MODE GamePlay::sideScene()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return GAME_MODE_GAMEOVER;
}