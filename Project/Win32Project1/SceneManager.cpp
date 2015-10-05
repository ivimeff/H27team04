#include "SceneManager.h"
#include <stdio.h>

SceneManager::SceneManager()
{
	m_Renderer = new Renderer();
	m_pDataManager = new DataManager(m_Renderer);
	m_GamePad = new GamePad();
	if (!m_pDataManager->load()) return;
	scenes.insert(std::make_pair(GAME_MODE_GAMETITLE, new GameTitle(m_pDataManager,m_Renderer, m_GamePad)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEMENU, new GameMenu(m_pDataManager, m_Renderer, m_GamePad)));
	scenes.insert(std::make_pair(GAME_MODE_TUTORIAL, new Tutorial(m_pDataManager, m_Renderer, m_GamePad)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEPLAY, new GamePlay(m_pDataManager, m_Renderer, m_GamePad)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEOVER, new GameOver(m_pDataManager, m_Renderer, m_GamePad)));
	mGameMode = GAME_MODE_GAMETITLE;
	currentScene = scenes[mGameMode];
	init();
}

SceneManager::~SceneManager()
{
	delete m_pDataManager;
}

void SceneManager::init()
{
	currentScene->init();
	m_GamePad->init();


}

void SceneManager::update()
{
	currentScene->update();
	if (currentScene->isEnd())
	{
		mGameMode = currentScene->nextScene();
		currentScene = scenes[mGameMode];
		currentScene->init();
	}

	if (currentScene->isMenu())	//チュートリアルとかのシーンの分岐に使うやつ
	{
		mGameMode = currentScene->sideScene();
		currentScene = scenes[mGameMode];
		currentScene->init();
	}

	m_GamePad->update();
}

void SceneManager::draw()
{
	currentScene->draw();

}