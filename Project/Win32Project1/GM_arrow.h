#pragma once
#include "MoveObject.h"
#include "CharacterManager.h"

class GM_arrow :public MoveObject
{
public:
	GM_arrow(GamePlayBundle* _GamePlayBundle);
	GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~GM_arrow();

	void init();
	void update();
	void draw();

	void hited(Character* _target);

private:
	bool hit;
	void move();
	void onDent();
	int animation, time, speed;
};