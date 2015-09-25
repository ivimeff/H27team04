#include "Enemy.h"

Enemy::Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera) :
MoveObject(_DataManager, _MapData, _camera) {}

Enemy::Enemy(DataManager* _DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position) :
MoveObject(_DataManager, _MapData, _camera, _position) {}

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
	gsDraw2D(dataManager->suraimu, position.x - camera->getPosition().x, position.y - camera->getPosition().y);
}

void Enemy::move()
{
	moveValue.x++;
}