#include "PassageUp.h"
#include "Player.h"

PassageUp::PassageUp(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, 1)
{

}

PassageUp::~PassageUp()
{}

void PassageUp::init()
{

}

void PassageUp::update()
{

}

void PassageUp::draw()
{

}

void PassageUp::hited(Character* _target)
{
	if (typeid(*_target) == typeid(Player))
	{

	}
}