#ifndef _ENEMY_
#define _ENEMY_

#include "MoveObject.h"

class Enemy : public MoveObject
{
public:
	Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera);
	Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position);
	Enemy(GamePlayBundle* _GamePlayBundle);
	Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Enemy();

	void init();
	void update();
	void draw();

private:
	void move();



};

#endif