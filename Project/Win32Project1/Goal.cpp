#include "Goal.h"
#include "Player.h"

Goal::Goal(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
Character(_GamePlayBundle, _position, def::C_GOAL)
{
	goalFlg = false;
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Goal::~Goal() {}

void Goal::init()
{

}

void Goal::update()
{

}

void Goal::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - halfSize - cPos;
	renderer->drawRect(def::Rect(drawPos, size), 0xffffff00);
}

void Goal::hited(Character* _target)
{
	if (_target->getTag() != def::C_PLAYER) return;
	goalFlg = true;
}

bool Goal::isGoal()
{
	return goalFlg;
}