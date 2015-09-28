#include "Player.h"
#include <iostream>
#include <sstream>

Player::Player(DataManager *_DataManager, MapData *_MapData, Camera *_camera) : MoveObject(_DataManager, _MapData, _camera) {}

Player::Player(DataManager *_DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position) : MoveObject(_DataManager, _MapData, _camera, _position) {}

Player::~Player() {}

void Player::init()
{
	//moveValue = D3DXVECTOR2(0, 0);
	direction = DR_DOWN;
	animation = time = 0;
}

void Player::draw()
{
	D3DXVECTOR2 cPos = camera->getPosition(),
		drawPos = position - cPos;
	// 
	gsDraw2DPartEx(dataManager->anim, drawPos.x, drawPos.y, PlayerSize::x, PlayerSize::y,
		animation % 4 * PlayerSize::x, direction * PlayerSize::y, PlayerSize::x, PlayerSize::y, 0, 0xffffffff);
#ifdef _DEBUG
	drawPos -= D3DXVECTOR2(PlayerSize::hx, PlayerSize::hy);
	gsDraw2DRectangle(drawPos.x, drawPos.y, drawPos.x + PlayerSize::x, drawPos.y + PlayerSize::y, 0xffffffff);
	char str[100];
	sprintf(str, "X:%5.3f, Y:%5.3f", position.x, position.y);
	gsDrawText(0, 0, str);
#endif
}

void Player::update()
{
	MoveObject::moveUpdate();
	if (time++ % 6 == 0) animation++;
	camera->setPosition(position);
}

void Player::move()
{

	if (gsKeyState(VK_LEFT) == GSKS_PRESS)
	{
		moveValue.x -= speed;
		direction = DR_LEFT;
	}
	if (gsKeyState(VK_RIGHT) == GSKS_PRESS)
	{
		moveValue.x += speed;
		direction = DR_RIGHT;
	}
	if (gsKeyState(VK_UP) == GSKS_PRESS)
	{
		moveValue.y -= speed;
		direction = DR_UP;
	}
	if (gsKeyState(VK_DOWN) == GSKS_PRESS)
	{
		moveValue.y += speed;
		direction = DR_DOWN;
	}

}