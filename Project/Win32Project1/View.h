#ifndef _VIEW_
#define _VIEW_

#include "DataManager.h"
#include "Player.h"
#include "GamePlayBundle.h"

class View
{
public:
	View(DataManager *_DataManager);
	~View();
	void init();
	void updata();
	void draw();
	int ViewSize;
	bool EnergieFlg;
	int Energie;
private:
	DataManager *m_DataManager;
};

#endif