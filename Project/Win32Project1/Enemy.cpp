#include "Enemy.h"

Enemy::Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera) :
Enemy(_DataManager, _Renderer, _MapData, _camera, def::Vector2(0, 0))
{}

Enemy::Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position) :
MoveObject(_DataManager, _Renderer, _MapData, _camera, _position)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Enemy::Enemy(GamePlayBundle* _GamePlayBundle) : MoveObject(_GamePlayBundle) {}

Enemy::Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position) {}

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
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - cPos;
	// 
	renderer->drawTexture(dataManager->suraimu, drawPos.x, drawPos.y);
#ifdef _DEBUG
	drawPos -= def::Vector2(halfSize.x, halfSize.y);
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
#endif
}

void Enemy::move()
{
	moveValue.x++;
}