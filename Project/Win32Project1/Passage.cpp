#include "Passage.h"
#include "Player.h"

Passage::Passage(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, int _nIndex) :
Character(_GamePlayBundle, _position), nIndex(_nIndex)
{
	hitting = true;
}

Passage::~Passage() {}

void Passage::init()
{

}

void Passage::update()
{

}

void Passage::draw()
{

}

void Passage::hited(Character* target)
{
	if (typeid(*target)== typeid(Player))
	if (!hitting)
	{
		return;
	}
	hitting = false;
	return;

}

int Passage::getNextIndex()
{
	return nIndex;
}