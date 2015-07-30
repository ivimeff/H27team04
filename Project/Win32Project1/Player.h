#ifndef _PLAYER_
#define _PLAYER_

#include "def.h"
#include "gs.h"
#include "DataManager.h"
#include "MoveObject.h"

class Player : public MoveObject
{
public:
	Player(DataManager *_DataManager, MapData *_MapData);
	Player(DataManager *_DataManager, MapData *_MapData, D3DXVECTOR2 _position);
	~Player();
	void init();
	void draw();
	void update();
private:
	void move();
	void moveUpdate();
};

#endif