#ifndef _GAMEPLAYUI_
#define _GAMEPLAYUI_

#include "Scene.h"	//

class Renderer;	//	

class GamePlayUI
{
public:
	GamePlayUI(Renderer *_Renderer,GamePad *_gamepad);	//
	~GamePlayUI();
	void init();
	void updata();
	void draw();
	void SetViewSize(int);
	void SetPlayerDamageFlg(bool);
	int GameOverFlg;

private:
	int EnergieIcon_x;//96*96
	int EnergieIcon_y;
	int EnergieCage_x;//320*32
	int EnergieCage_y;
	int Heart_x;//32*32
	int Heart_y;
	int Heart;
	int HeartMax;
	int Energie;
	int WordSize;
	bool PlayerDamageFlg;
	bool EnergieFlg;
	int StarTime;
	Renderer *m_Renderer;	//
	GamePad *m_gamepad;
};


#endif