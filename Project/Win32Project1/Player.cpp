#include "Player.h"

Player::Player(DataManager *_DataManager, MapData *_MapData) : MoveObject(_DataManager, _MapData) {}

Player::Player(DataManager *_DataManager, MapData *_MapData, D3DXVECTOR2 _position) : MoveObject(_DataManager, _MapData, _position) {}

Player::~Player() {}

void Player::init()
{
	moveValue = D3DXVECTOR2(0, 0);
	direction = DR_DOWN;
	animation = time = 0;
}

void Player::draw()
{
	gsDraw2DPartEx(dataManager->red, position.x, position.y, PlayerSize::x, PlayerSize::y,
		animation % 4 * PlayerSize::x, direction * PlayerSize::y, PlayerSize::x, PlayerSize::y, 0, 0xffffffff);
}

void Player::update()
{
	move();
	MoveObject::moveUpdate();
	if (time++ % 6 == 0) animation++;
}

void Player::move()
{

	moveValue = D3DXVECTOR2(0, 0);
	if (gsKeyState(VK_LEFT) == GSKS_PRESS)
	{
		moveValue.x -= 3.0f;
		direction = DR_LEFT;
	}
	if (gsKeyState(VK_RIGHT) == GSKS_PRESS)
	{
		moveValue.x += 3.0f;
		direction = DR_RIGHT;
	}
	if (gsKeyState(VK_UP) == GSKS_PRESS)
	{
		moveValue.y -= 3.0f;
		direction = DR_UP;
	}
	if (gsKeyState(VK_DOWN) == GSKS_PRESS)
	{
		moveValue.y += 3.0f;
		direction = DR_DOWN;
	}

}