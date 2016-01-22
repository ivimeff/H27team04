#ifndef _GAMEPLAYUI_
#define _GAMEPLAYUI_

#include "DataManager.h"
#include "Scene.h"

class GamePlayUI
{
public:
	GamePlayUI(DataManager *_DataManager);
	~GamePlayUI();
	void init();
	void updata();
	void draw();
	void SetViewSize(int);
	bool SetPlayerDamageFlg(bool);

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
	bool PlayerDamageFlg;
	DataManager *m_DataManager;
};


#endif