#ifndef _ENEMY_
#define _ENEMY_

#include "MoveObject.h"

class Enemy : public MoveObject
{
public:
	Enemy(GamePlayBundle* _GamePlayBundle);
	Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Enemy();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
	void hitLeft(Character* _target);
	void hitRight(Character* _target);
private:
	void move();
	void onDent();
	bool hit;
	int speed;
	bool hitstate;
};

#endif