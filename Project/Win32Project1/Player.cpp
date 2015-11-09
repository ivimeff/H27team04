#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "Enemy.h"
#include "Passage.h"

Player::Player(GamePlayBundle* _GamePlayBandle) : Player(_GamePlayBandle, def::Vector2(0, 0)) {}

Player::Player(GamePlayBundle* _GamePlayBandle, def::Vector2 _position) : MoveObject(_GamePlayBandle, _position, def::C_PLAYER)
{
	size = playerSize;
	halfSize = playerHalfSize;
	hitTag = def::C_NONE;
	direction = DR_DOWN;
}

Player::~Player() {}

void Player::init()
{
	//moveValue = D3DXVECTOR2(0, 0);
	animation = time = 0;
	switch (hitTag)
	{
	case def::C_PASS_UP:
		reversePosY();
		mapData->changeMap(1);
		break;
	case def::C_PASS_DOWN:
		reversePosY();
		mapData->changeMap(-1);
		break;
	}
	hitTag = def::C_NONE;
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
	hitTag = def::C_NONE;
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

	if (_target->getTag() == def::C_PASS_UP ||
		_target->getTag() == def::C_PASS_DOWN)
	{
		hitTag = _target->getTag();
	}

}

def::CTag Player::getHitTag()
{
	return hitTag;
}

void Player::reversePosY()
{
	position.y = -position.y + Map::heightSize;
}