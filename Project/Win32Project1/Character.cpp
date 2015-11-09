#include "Character.h"

Character::Character(GamePlayBundle* _GamePlayBundle, def::CTag _tag) :
Character(_GamePlayBundle, def::Vector2(0, 0), _tag) {}

Character::Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::CTag _tag) :
dataManager(_GamePlayBundle->dataManager), renderer(_GamePlayBundle->renderer),
mapData(_GamePlayBundle->mapData), camera(_GamePlayBundle->camera),
position(_position), gamePad(_GamePlayBundle->gamePad), tag(_tag)
{
	deadFlg = false;
}

Character::~Character()
{}

void Character::init()
{}

void Character::update()
{}

void Character::draw()
{}

void Character::setPosition(def::Vector2 _position)
{
	position = def::Vector2(_position);
}

bool Character::isDead()
{
	return deadFlg;
}

def::Rect Character::getRect()
{
	def::Rect r = def::Rect(
		position.x - halfSize.x,
		position.y - halfSize.y,
		position.x + halfSize.x,
		position.y + halfSize.y);
	return r;
}

void Character::hited(Character* _target) {}

def::CTag Character::getTag()
{
	return tag;
}