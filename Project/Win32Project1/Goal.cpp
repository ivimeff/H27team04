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
	//renderer->drawRect(def::Rect(drawPos, size), 0xffffff00);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER("Door", drawPos), layer);
}

void Goal::hited(Character* _target)
{
	if (_target->getTag() != def::C_PLAYER) return;
	goalFlg = ((Player*)_target)->isTreasure();
}

bool Goal::isGoal()
{
	return goalFlg;
}