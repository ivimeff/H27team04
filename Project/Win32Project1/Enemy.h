#ifndef _ENEMY_
#define _ENEMY_

#include "MoveObject.h"

class Enemy : public MoveObject
{
public:
	Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _dir = def::Vector2(0, 0));
	~Enemy();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
	void hitLeft(Character* _target);
	void hitRight(Character* _target);
	void hitTop(Character* _target);
	void hitBottom(Character* _target);
private:
	void move();
	void onDent();
	bool hit;
	int speed;
	int animation,time;
	bool hitstate, netFlg;
	def::Vector2 pPos;		//float x, y;
	def::Vector2 sepos, direction;
};

#endif