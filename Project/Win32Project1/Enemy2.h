#ifndef _ENEMY2_
#define _ENEMY2_

#include "MoveObject.h"

class Enemy2 : public MoveObject
{
public:
	Enemy2(GamePlayBundle* _GamePlayBundle);
	Enemy2(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Enemy2();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
private:
	void move();
	void onDent();
	bool hit;
	def::Vector2 speed;
	float x, y;
	float nomalspeed;

};

#endif