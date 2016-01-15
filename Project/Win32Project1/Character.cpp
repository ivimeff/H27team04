#include "Character.h"

//Character::Character(GamePlayBundle* _GamePlayBundle, def::CTag _tag) :
//Character(_GamePlayBundle, def::Vector2(0, 0), _tag) {}

Character::Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _size, def::CTag _tag) :
dataManager(_GamePlayBundle->dataManager), soundManager(_GamePlayBundle->soundManager), renderer(_GamePlayBundle->renderer),
mapData(_GamePlayBundle->mapData), camera(_GamePlayBundle->camera),
position(_position), size(_size), halfSize(_size / 2), gamePad(_GamePlayBundle->gamePad), mediator(_GamePlayBundle->mediator),
gamePlayBundle(_GamePlayBundle), tag(_tag)
{
	deadFlg = false;
}

Character::Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::CTag _tag) :
Character(_GamePlayBundle, _position, def::Vector2(64, 64), _tag) {}

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

def::Rect Character::getObjLeftRect()
{
	def::Rect r = def::Rect(
		position.x - halfSize.x - 3.0f,
		//yTop
		position.y - halfSize.y,
		//xRight
		position.x - halfSize.x,// - 2.5f,
		//yBottom
		position.y + halfSize.y);
	return r;
}

def::Rect Character::getObjRightRect()
{
	def::Rect r = def::Rect(
		position.x + halfSize.x,// + 2.5f,
		//yTop
		position.y - halfSize.y,
		//xRight
		position.x + halfSize.x + 3.0f,
		//yBottom
		position.y + halfSize.y);
	return r;
}

def::Rect Character::getObjTopRect()
{
	def::Rect r = def::Rect(
		//xLeft
		position.x - halfSize.x,
		//yTop
		position.y - halfSize.y - 3.0f,
		//xRight
		position.x + halfSize.x,
		//yBottom
		position.y - halfSize.y);// -2.5f);
	return r;
}

def::Rect Character::getObjBottomRect()
{
	def::Rect r = def::Rect(
		//xLeft
		position.x - halfSize.x,
		//yTop
		position.y + halfSize.y,// + 2.5f,
		//xRight
		position.x + halfSize.x,
		//yBottom
		position.y + halfSize.y + 3.0f);
	return r;
}

void Character::hitLeft(Character* _target) {}

void Character::hitRight(Character* _target) {}


void Character::hitTop(Character* _target) {}


void Character::hitBottom(Character* _target) {}

def::DRAWORDER Character::getDrawOrder(TextureID id, def::Vector2 pos, def::Rect srcRect)
{
	return def::DRAWORDER(id, pos, srcRect);
}

def::Vector2 Character::getPos()
{
	return position;
}

def::Vector2 Character::getDrawPos()
{
	return position - camera->getPosition();
}
