#ifndef _GMAEPLAY_H
#define _GAMEPLAY_H

#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include"Player.h"

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
	Character *m_player;
	
};

#endif