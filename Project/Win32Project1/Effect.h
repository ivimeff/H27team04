#pragma once

#include "Character.h"

class Effect : public Character
{
public:
	Effect(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~Effect();
	void init();
};