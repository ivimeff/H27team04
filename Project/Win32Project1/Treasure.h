#ifndef _TREASURE_
#define _TREASURE_

#include "Character.h"

class Treasure : public Character
{
public:
	Treasure(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~Treasure();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
};

#endif