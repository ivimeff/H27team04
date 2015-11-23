#include "PassageRight.h"
#include "Player.h"

PassageRight::PassageRight(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, def::P_RIGHT, def::C_PASS_RIGHT)
{
	size = def::Vector2(2, 64);
	halfSize = size / 2;
	position.x += Map::chipSize / 2;
}

PassageRight::~PassageRight()
{}

void PassageRight::init()
{

}

void PassageRight::update()
{

}

void PassageRight::draw()
{
	def::Vector2 cPos = camera->getPosition();
	renderer->drawRect(
		position - (cPos + halfSize),
		size,
		0xff00ffff
		);
}