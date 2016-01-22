#ifndef _VIEW_
#define _VIEW_

#include "DataManager.h"
#include "Player.h"
#include "GamePlayBundle.h"

class View
{
public:
	View(DataManager *_DataManager, GamePad *_gamepad);
	~View();
	void init();
	void updata();
	void draw();
	int ViewSize;
	bool EnergieFlg;
	int Energie;
	void SetPosition(def::Vector2);
private:
	float View_X;
	float View_Y;
	DataManager *m_DataManager;
	GamePad *m_gamepad;
};

#endif