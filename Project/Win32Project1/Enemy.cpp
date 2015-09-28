#include "Enemy.h"

Enemy::Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera) :
Enemy(_DataManager, _MapData, _camera, D3DXVECTOR2(0, 0))
{}

Enemy::Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position) :
MoveObject(_DataManager, _MapData, _camera, _position)
{
	size = D3DXVECTOR2(64, 64);
	halfSize = size / 2;
}

Enemy::~Enemy() {}

void Enemy::init()
{

}

void Enemy::update()
{
	moveUpdate();
}

void Enemy::draw()
{
	D3DXVECTOR2 cPos = camera->getPosition(),
		drawPos = position - cPos;
	// 
	gsDraw2D(dataManager->suraimu, drawPos.x, drawPos.y);
#ifdef _DEBUG
	drawPos -= D3DXVECTOR2(halfSize.x, halfSize.y);
	gsDraw2DRectangle(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
#endif
}

void Enemy::move()
{
	moveValue.x++;
}