#include "Player.h"

Player::Player(DataManager *_DataManager, MapData *_MapData) : MoveObject(_DataManager, _MapData) {}

Player::Player(DataManager *_DataManager, MapData *_MapData, D3DXVECTOR2 _position) : MoveObject(_DataManager, _MapData, _position) {}

Player::~Player() {}

void Player::init()
{
	moveValue = D3DXVECTOR2(0, 0);
}

void Player::draw()
{
	gsDraw2DEx(dataManager->suraimu, position.x - PlayerSize::hx, position.y - PlayerSize::hy, PlayerSize::x, PlayerSize::y);
}

void Player::update()
{
	move();
	MoveObject::moveUpdate();
}

void Player::move()
{
	moveValue = D3DXVECTOR2(0, 0);
	if (gsKeyState(VK_LEFT) == GSKS_PRESS)
	{
		moveValue.x -= 3.0f;
	}
	if (gsKeyState(VK_RIGHT) == GSKS_PRESS)
	{
		moveValue.x += 3.0f;
	}
	if (gsKeyState(VK_UP) == GSKS_PRESS)
	{
		moveValue.y -= 3.0f;
	}
	if (gsKeyState(VK_DOWN) == GSKS_PRESS)
	{
		moveValue.y += 3.0f;
	}

	//position += moveValue;
}