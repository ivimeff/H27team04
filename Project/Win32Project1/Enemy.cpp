#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera) :
Enemy(_DataManager, _Renderer, _MapData, _camera, def::Vector2(0, 0))
{}

Enemy::Enemy(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position) :
MoveObject(_DataManager, _Renderer, _MapData, _camera, _position)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Enemy::Enemy(GamePlayBundle* _GamePlayBundle) : Enemy(_GamePlayBundle, def::Vector2(0, 0)) {}

Enemy::Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position)
{
	size = def::Vector2(64, 64);
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
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	renderer->drawTexture(dataManager->suraimu, drawPos);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	if(hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
#endif
	hit = false;
}

void Enemy::move()
{
	moveValue.x++;
}

void Enemy::hited(Character* _target)
{
	if ((typeid(_target) == typeid(Player))) return;
	hit = true;
}