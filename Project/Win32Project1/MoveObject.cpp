#include <math.h>
#include "MoveObject.h"

MoveObject::MoveObject(DataManager* _DataManager, MapData* _MapData, Camera *_camera) : Character(_DataManager, _MapData, _camera) {}

MoveObject::MoveObject(DataManager* _DataManager, MapData* _MapData, Camera *_camera, D3DXVECTOR2 _position) : Character(_DataManager, _MapData, _camera, _position) {}

MoveObject::~MoveObject() {}

void MoveObject::moveUpdate()
{
	move();
	moveReflect();
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
		position.x += x < 1 ? fmod(moveValue.x, 1) : 1;
	}
}

void MoveObject::moveLeft()
{
	for (float x = -moveValue.x; x >= 0; --x) {
		if (!moveLeftOne()) return;
		position.x -= x < 1 ? fmod(-moveValue.x, 1) : 1;
	}
}

void MoveObject::moveUp()
{
	for (float y = -moveValue.y; y >= 0; --y) {
		if (!moveUpOne()) return;
		position.y -= y < 1 ? fmod(-moveValue.y, 1) : 1;
	}
}

void MoveObject::moveDown()
{
	for (float y = moveValue.y; y >= 0; --y) {
		if (!moveDownOne()) return;
		position.y += y < 1 ? fmod(moveValue.y, 1) : 1;
	}
}

bool MoveObject::moveRightOne()
{
	D3DXVECTOR2 startPosition = D3DXVECTOR2(position.x + PlayerSize::hx, position.y - PlayerSize::hy);
	if (!mapData->isCollisionSide(startPosition, PlayerSize::y)) return true;
	return false;
}

bool MoveObject::moveLeftOne()
{
	D3DXVECTOR2 startPosition = D3DXVECTOR2(position.x - PlayerSize::hx, position.y - PlayerSize::hy);
	if (!mapData->isCollisionSide(startPosition, PlayerSize::y)) return true;
	return false;
}

bool MoveObject::moveUpOne()
{
	D3DXVECTOR2 startPosition = D3DXVECTOR2(position.x - PlayerSize::hx, position.y - PlayerSize::hy);
	if (!mapData->isCollisionUpDown(startPosition, PlayerSize::x)) return true;
	return false;
}

bool MoveObject::moveDownOne()
{
	D3DXVECTOR2 startPosition = D3DXVECTOR2(position.x - PlayerSize::hx, position.y + PlayerSize::hy);
	if (!mapData->isCollisionUpDown(startPosition, PlayerSize::x)) return true;
	return false;
}
