#ifndef _GMAEPLAY_H
#define _GAMEPLAY_H

#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "Camera.h"

class GamePlay : public Scene
{
public:
	GamePlay(DataManager *_DataManager);
	~GamePlay();

	void init();
	void update();
	void draw();
	GAME_MODE nextScene();
private:
	MapData *m_pMapData;
	Camera *camera;
	CharacterManager* m_CharacterManager;
	
};

#endif