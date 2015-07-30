#ifndef _GMAEOVER_H
#define _GAMEOVER_H

#include "DataManager.h"
#include "gs.h"
#include "Scene.h"

class GameOver : public Scene
{
public:
	GameOver(DataManager *_DataManager);
	~GameOver();
	
	void init();
	void update();
	void draw();
	GAME_MODE nextScene();

private:
	int over_x;
	int over_y;
};


#endif