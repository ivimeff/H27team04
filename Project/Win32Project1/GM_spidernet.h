#pragma once

#include "CharacterManager.h"
#include "MoveObject.h"

class GM_spidernet : public MoveObject
{
public:
	GM_spidernet(GamePlayBundle* _GamePlayBundle);
	GM_spidernet(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~GM_spidernet();

	void init();
	void update();
	void draw();
	bool isSpiritual();

	void hited(Character* _target);

private:
	bool hit;
	void move();
};