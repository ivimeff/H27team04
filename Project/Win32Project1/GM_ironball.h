#pragma once

#include "MoveObject.h"

class GM_ironball : public MoveObject
{
public:
	GM_ironball(GamePlayBundle* _GamePlayBundle);
	GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~GM_ironball();

	void init();
	void update();
	void draw();

	void hited(Character* _target);

private:
	bool hit;
	void move();
	int animation, time,speed;
};