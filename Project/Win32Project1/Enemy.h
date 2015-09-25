#ifndef _ENEMY_
#define _ENEMY_

#include "MoveObject.h"

class Enemy : public MoveObject
{
public:
	Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera);
	Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position);
	~Enemy();

	void init();
	void update();
	void draw();

private:
	void move();



};

#endif