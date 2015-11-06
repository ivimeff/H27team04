#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "Enemy.h"
#include "Passage.h"

Player::Player(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera) :
Player(_DataManager, _Renderer, _MapData, _camera, def::Vector2(0, 0)) {}

Player::Player(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position) :
MoveObject(_DataManager, _Renderer, _MapData, _camera, _position)
{
	size = def::Vector2(PlayerSize::x, PlayerSize::y);
	halfSize = def::Vector2(PlayerSize::hx, PlayerSize::hy);
}

Player::Player(GamePlayBundle* _GamePlayBandle) : Player(_GamePlayBandle, def::Vector2(0, 0)) {}

Player::Player(GamePlayBundle* _GamePlayBandle, def::Vector2 _position) : MoveObject(_GamePlayBandle, _position)
{
	size = def::Vector2(PlayerSize::x, PlayerSize::y);
	halfSize = def::Vector2(PlayerSize::hx, PlayerSize::hy);
}

Player::~Player() {}

void Player::init()
{
	//moveValue = D3DXVECTOR2(0, 0);
	direction = DR_DOWN;
	animation = time = 0;
}

void Player::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	renderer->drawTextureRect(dataManager->anim, drawPos.x, drawPos.y,
		animation % 4 * size.x, direction * size.y, size.x, size.y);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	std::ostringstream ostr;
	ostr << "X:" << position.x << ", Y:" << position.y;
	renderer->drawString(ostr.str().c_str(), 0, 0);
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

	if (gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_PRESS)
	{
		moveValue.x -= speed;
		direction = DR_LEFT;
	}
	if (gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_PRESS)
	{
		moveValue.x += speed;
		direction = DR_RIGHT;
	}
	if (gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_PRESS)
	{
		moveValue.y -= speed;
		direction = DR_UP;
	}
	if (gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_PRESS)
	{
		moveValue.y += speed;
		direction = DR_DOWN;
	}

}

void Player::hited(Character* _target)
{
	if (typeid(*_target) == typeid(Enemy))
	{
		return;
	}

	if (typeid(*_target) == typeid(Passage))
	{
		mapData->changeMap(((Passage*)_target)->getNextIndex());
	}

}