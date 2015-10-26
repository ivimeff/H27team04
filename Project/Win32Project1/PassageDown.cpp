#include "PassageDown.h"
#include "Player.h"

PassageDown::PassageDown(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, -1)
{

}

PassageDown::~PassageDown()
{}

void PassageDown::init()
{

}

void PassageDown::update()
{

}

void PassageDown::draw()
{

}

void PassageDown::hited(Character* _target)
{
	if (typeid(*_target) == typeid(Player))
	{

	}
}