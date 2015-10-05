#ifndef _GMAEOVER_H
#define _GAMEOVER_H

#include "DataManager.h"
#include "Scene.h"

class GameOver : public Scene
{
public:
	GameOver(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad);
	~GameOver();

	void init();
	void update();
	void draw();
	GAME_MODE nextScene();
	GAME_MODE sideScene();	//チュートリアルとかのシーンの分岐に使うやつ

private:
	int over_x;
	int over_y;
};


#endif