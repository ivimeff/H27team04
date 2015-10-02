#include "Enemy.h"
Enemy::Enemy(DataManager *_DataManager)
{
	m_pDataManager = _DataManager;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	enemy_x = 320;
	enemy_y = 320;
}

void Enemy::updata()
{

}

void Enemy::draw()
{
	gsDraw2D(m_pDataManager->blue, enemy_x, enemy_y);
}