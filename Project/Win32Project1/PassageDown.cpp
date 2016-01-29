#include "PassageDown.h"
#include "Player.h"

PassageDown::PassageDown(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, def::P_DOWN, def::C_PASS_DOWN)
{
	size = def::Vector2(64, 2);
	halfSize = size / 2;
	position.y += Map::chipSize / 2;
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
#ifdef _DEBUG
	def::Vector2 cPos = camera->getPosition();
	renderer->drawRect(
		position - (cPos + halfSize),
		size,
		0xff00ffff
		);
#endif
}