#pragma once
#include "MoveObject.h"
#include "CharacterManager.h"

class GM_arrow :public MoveObject
{
public:
	GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, bool _spFlg, def::Vector2 _dir);
	~GM_arrow();

	void init();
	void update();
	void draw();
	bool isSpiritual();
	void hited(Character* _target);

private:
	bool hit;
	void move();
	void onDent();
	int animation, time, speed;
	float x, y;
	def::Vector2 sepos, direction;
};