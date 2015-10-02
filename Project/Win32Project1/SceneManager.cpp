#include "SceneManager.h"
#include <stdio.h>

SceneManager::SceneManager()
{
	m_pDataManager = new DataManager();
	if (!m_pDataManager->load()) return;
	scenes.insert(std::make_pair(GAME_MODE_GAMETITLE, new GameTitle(m_pDataManager)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEMENU, new GameMenu(m_pDataManager)));
	scenes.insert(std::make_pair(GAME_MODE_TUTORIAL, new Tutorial(m_pDataManager)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEPLAY, new GamePlay(m_pDataManager)));
	scenes.insert(std::make_pair(GAME_MODE_GAMEOVER, new GameOver(m_pDataManager)));
	mGameMode = GAME_MODE_GAMETITLE;
	currentScene = scenes[mGameMode];
	init();
}

SceneManager::~SceneManager()
{
	delete m_pDataManager;
	//delete m_pGameTitle;
	//delete m_pGamePlay;
	//delete m_pGameOver;
}

void SceneManager::init()
{
	currentScene->init();

	//switch (mGameMode)
	//{
	//case GAME_MODE_GAMETITLE:
	//{
	//	m_pGameTitle->init();
	//	break;
	//}
	//case GAME_MODE_GAMEPLAY:
	//{
	//	m_pGamePlay->init();
	//	break;
	//}
	//case GAME_MODE_GAMEOVER:
	//{
	//	m_pGameOver->init();
	//	break;
	//}
	//default:
	//	break;
	//}


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

	//GAME_MODE OldScene = mGameMode;//★ 今のゲームシーンを保存

	//switch (mGameMode)
	//{
	//case GAME_MODE_GAMETITLE:
	//{
	//	m_pGameTitle->update();
	//	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	//	{
	//		mGameMode = GAME_MODE_GAMEPLAY;
	//	}
	//	break;
	//}
	//case GAME_MODE_GAMEPLAY:
	//{
	//	m_pGamePlay->update();
	//	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	//	{
	//		mGameMode = GAME_MODE_GAMEOVER;
	//	}
	//	break;
	//}
	//case GAME_MODE_GAMEOVER:
	//{
	//	m_pGameOver->update();
	//	if (gsKeyState(VK_RETURN) == GSKS_DOWN)
	//	{
	//		mGameMode = GAME_MODE_GAMETITLE;
	//	}
	//	break;
	//}
	//default:
	//	break;
	//}

	//if (OldScene != mGameMode)//★ もしゲームシーンが変わったら、初期化する 
	//{
	//	init();
	//}
}

void SceneManager::draw()
{
	currentScene->draw();

	//switch (mGameMode)
	//{
	//case GAME_MODE_GAMETITLE:
	//{
	//	m_pGameTitle->draw();
	//	break;
	//}
	//case GAME_MODE_GAMEPLAY:
	//{
	//	m_pGamePlay->draw();
	//	break;
	//}
	//case GAME_MODE_GAMEOVER:
	//{
	//	m_pGameOver->draw();
	//	break;
	//}
	//default:
	//	break;
	//}
	
}