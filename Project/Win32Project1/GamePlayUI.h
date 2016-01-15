#ifndef _GAMEPLAYUI_
#define _GAMEPLAYUI_

#include "Scene.h"	//

class Renderer;	//	

class GamePlayUI
{
public:
	GamePlayUI(Renderer *_Renderer);	//
	~GamePlayUI();
	void init();
	void updata();
	void draw();
	void SetViewSize(int);

private:
	int EnergieIcon_x;//96*96
	int EnergieIcon_y;
	int EnergieCage_x;//320*32
	int EnergieCage_y;
	int Heart_x;//32*32
	int Heart_y;
	int Energie;
	int WordSize;
	bool EnergieFlg;
	Renderer *m_Renderer;	//
};


#endif