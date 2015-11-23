#include "PassageLeft.h"
#include "Player.h"

PassageLeft::PassageLeft(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, def::P_LEFT, def::C_PASS_LEFT)
{
	size = def::Vector2(2, 64);
	halfSize = size / 2;
	position.x -= Map::chipSize / 2;
}

PassageLeft::~PassageLeft()
{}

void PassageLeft::init()
{

}

void PassageLeft::update()
{

}

void PassageLeft::draw()
{
	def::Vector2 cPos = camera->getPosition();
	renderer->drawRect(
		position - (cPos + halfSize),
		size,
		0xff00ffff
		);
}