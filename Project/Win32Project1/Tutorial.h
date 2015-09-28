#ifndef _TUTORIAL_H
#define _TUTORIAL_H

#include "DataManager.h"
#include "Scene.h"
#include "def.h"
#include "gs.h"

class Tutorial : public Scene
{
public:
	Tutorial(DataManager *_DataManager);
	~Tutorial();

	void init();
	void update();
	void draw();
	GAME_MODE nextScene();
	GAME_MODE sideScene();	//チュートリアルとかのシーンの分岐に使うやつ

private:
	int tuto_x;
	int tuto_y;
};

#endif