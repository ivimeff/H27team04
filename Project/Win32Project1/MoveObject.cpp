#include <math.h>
#include "MoveObject.h"

//MoveObject::MoveObject(GamePlayBundle* _GamePlayBundle, def::CTag _tag) :
//Character(_GamePlayBundle, _tag) {}

MoveObject::MoveObject(GamePlayBundle* _GamePlayBundle, def::Vector2 _position,
	def::Vector2 _size, def::CTag _tag) :
	Character(_GamePlayBundle, _position, _size, _tag) {}

MoveObject::MoveObject(GamePlayBundle* _GamePlayBundle, def::Vector2 _position,
	def::CTag _tag) :
	Character(_GamePlayBundle, _position, _tag) {}

MoveObject::~MoveObject() {}

void MoveObject::moveUpdate()
{
	move();
	moveReflect();
	moveValue = def::Vector2(0, 0);
}

void MoveObject::onDent()
{

}

void MoveObject::moveReflect()
{
	moveReflectSide();
	moveReflectUpDown();
}

void MoveObject::moveReflectSide()
{
	if (moveValue.x > 0)
	{
		moveRight();
	}
	else if (moveValue.x < 0)
	{
		moveLeft();
	}
}

void MoveObject::moveReflectUpDown()
{
	if (moveValue.y > 0)
	{
		moveDown();
	}
	else if (moveValue.y < 0)
	{
		moveUp();
	}
}

void MoveObject::moveRight()
{
	for (float x = moveValue.x; x >= 0; --x) {
		if (!moveRightOne()) return;
		position.x += x < 1 ? fmod(moveValue.x, 1.f) : 1;
	}
}

void MoveObject::moveLeft()
{
	for (float x = -moveValue.x; x >= 0; --x) {
		if (!moveLeftOne()) return;
		position.x -= x < 1 ? fmod(-moveValue.x, 1.f) : 1;
	}
}

void MoveObject::moveUp()
{
	for (float y = -moveValue.y; y >= 0; --y) {
		if (!moveUpOne()) return;
		position.y -= y < 1 ? fmod(-moveValue.y, 1.f) : 1;
	}
}

void MoveObject::moveDown()
{
	for (float y = moveValue.y; y >= 0; --y) {
		if (!moveDownOne()) return;
		position.y += y < 1 ? fmod(moveValue.y, 1.f) : 1;
	}
}

bool MoveObject::moveRightOne()
{
	def::Vector2 startPosition = def::Vector2(position.x + halfSize.x, position.y - halfSize.y);
	if (!mapData->isCollisionSide(startPosition, size.y)) return true;
	onDent();
	return false;
}

bool MoveObject::moveLeftOne()
{
	def::Vector2 startPosition = def::Vector2(position.x - halfSize.x, position.y - halfSize.y);
	if (!mapData->isCollisionSide(startPosition, size.y)) return true;
	onDent();
	return false;
}

bool MoveObject::moveUpOne()
{
	def::Vector2 startPosition = def::Vector2(position.x - halfSize.x, position.y - halfSize.y);
	if (!mapData->isCollisionUpDown(startPosition, size.x)) return true;
	onDent();
	return false;
}

bool MoveObject::moveDownOne()
{
	def::Vector2 startPosition = def::Vector2(position.x - halfSize.x, position.y + halfSize.y);
	if (!mapData->isCollisionUpDown(startPosition, size.x)) return true;
	onDent();
	return false;
}
