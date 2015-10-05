#ifndef _GAMEMENU_H
#define _GAMEMENU_H

#include "DataManager.h"
#include "def.h"
#include "Scene.h"

class GameMenu : public Scene
{
public:
	GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad);
	~GameMenu();

	void init();
	void update();
	void draw();
	void shift();
	GAME_MODE nextScene();
	GAME_MODE sideScene();	//チュートリアルとかのシーンの分岐に使うやつ

private:
	int menu_x;
	int menu_y;
	int menu_t_x = 280;
	int menu_t_y = 150;
	int menu_p_y = 430;
};

#endif