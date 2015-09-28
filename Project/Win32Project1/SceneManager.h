#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <map>
#include "gs.h"
#include "Scene.h"
#include "DataManager.h"
#include "GameTitle.h"
#include "GamePlay.h"
#include "GameOver.h"
#include "Tutorial.h"
#include "GameMenu.h"
#include "def.h"
#include "MapData.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void update();
	void draw();


private:
	std::map<GAME_MODE, Scene*> scenes;
	Scene* currentScene;
	GAME_MODE mGameMode;
	DataManager *m_pDataManager;
	//GameTitle *m_pGameTitle;
	//GamePlay *m_pGamePlay;
	//GameOver *m_pGameOver;
	//int x;
	//int y;
};

#endif