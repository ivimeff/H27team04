#ifndef _PLAYER_
#define _PLAYER_

#include "def.h"
#include "gs.h"
#include "DataManager.h"
#include "MoveObject.h"

enum DIRECTION
{
	DR_DOWN = 0,
	DR_RIGHT = 1,
	DR_LEFT = 2,
	DR_UP = 3,
};

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
	DIRECTION direction;
	int animation, time;
	void move();
	void moveUpdate();
};

#endif