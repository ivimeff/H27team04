#include "Treasure.h"

Treasure::Treasure(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Character(_GamePlayBundle, _position, def::Vector2(64, 64), def::C_TREASURE)
{

}

Treasure::~Treasure()
{

}

void Treasure::init()
{

}

void Treasure::update()
{

}

void Treasure::draw()
{
	def::Vector2 drawPos = position - camera->getPosition() - halfSize;
	renderer->drawRect(drawPos, size, 0xffffff00, true);
}

void Treasure::hited(Character* _target)
{
	if (_target->getTag() != def::C_PLAYER) return;

	deadFlg = true;
}