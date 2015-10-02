#ifndef _GMAETITLE_H
#define _GAMETITLE_H

#include "DataManager.h"
#include "def.h"
#include "Scene.h"

class GameTitle : public Scene
{
public:
	GameTitle(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad);
	~GameTitle();

	void init();
	void update();
	void draw();
	GAME_MODE nextScene();
	GAME_MODE sideScene();	//チュートリアルとかのシーンの分岐に使うやつ

private:
	int title_x;
	int title_y;
};

#endif
