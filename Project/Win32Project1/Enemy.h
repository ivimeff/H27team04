#ifndef _ENEMY_
#define _ENEMY_

#include "def.h"
#include "gs.h"
#include "DataManager.h"

class Enemy
{
public:
	Enemy(DataManager *_DataManager);
	~Enemy();
	void init();
	void updata();
	void draw();

private:
	DataManager *m_pDataManager;
	int enemy_x;
	int enemy_y;
};

#endif