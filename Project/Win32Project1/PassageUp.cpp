#include "PassageUp.h"
#include "Player.h"

PassageUp::PassageUp(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Passage(_GamePlayBundle, _position, def::P_UP, def::C_PASS_UP)
{
	size = def::Vector2(64, 2);
	halfSize = size / 2;
	position.y -= Map::chipSize / 2;
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
	def::Vector2 cPos = camera->getPosition();
	renderer->drawRect(
		position - (cPos + halfSize),
		size,
		0xff00ffff
		);
}