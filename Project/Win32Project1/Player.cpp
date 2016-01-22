#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "Enemy.h"
#include "GM_ironball.h"
#include "GM_arrow.h"
#include "GM_spidernet.h"
#include "Passage.h"
#include"Block.h"
#include "Spiritual.h"
#include"Enemy2.h"

bool Player::hitflg = false;
bool Player::leftstop = false;
bool Player::rightstop = false;
bool Player::topstop = false;
bool Player::bottomstop = false;
def::Vector2 Player::currentpos = def::Vector2(0, 0);

Player::Player(GamePlayBundle* _GamePlayBandle) : Player(_GamePlayBandle, def::Vector2(0, 0)) {}

Player::Player(GamePlayBundle* _GamePlayBandle, def::Vector2 _position) : MoveObject(_GamePlayBandle, _position, def::C_PLAYER)
{
	size = playerSize;
	halfSize = playerHalfSize;
	hitTag = def::C_NONE;
	direction = DR_DOWN;
	hitting = bHit = treasureFlg = false;

	spsize = def::Vector2(64, 64);
	sphalfSize = spsize / 2;
}

Player::~Player() {}

void Player::init()
{
	//moveValue = D3DXVECTOR2(0, 0);
	animation = time = 0;
	spanim = sptime = 0;
	switch (hitTag)
	{
	case def::C_PASS_UP:
	case def::C_PASS_DOWN:
		reversePosY();
		mapData->changeMap(nextIndex);
		break;
	case def::C_PASS_LEFT:
	case def::C_PASS_RIGHT:
		reversePosX();
		mapData->changeMap(nextIndex);
		break;
	}
	nextIndex = 0;
	hitTag = def::C_NONE;
	t = 3.0f;
	PmoveX = 0.0f;
	PmoveY = 0.0f;
	moveSpeed = speed;
	PlayerDamageFlg = false;
}

void Player::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// ☆MapDataのレイヤー分け用
	//renderer->setMapLayer(mapData->getLayer(position.y + halfSize.y - 1));
	//renderer->drawTextureRect(dataManager->anim, drawPos.x, drawPos.y,
	//	animation % 4 * size.x, direction * size.y, size.x, size.y);
	def::Rect srcRect = def::Rect(
		animation % 4 * size.x,
		direction * size.y,
		animation % 4 * size.x + size.x,
		direction * size.y + size.y);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(
		"Anim", drawPos, srcRect), layer);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	std::ostringstream ostr;
	ostr << "X:" << position.x << ", Y:" << position.y;
	renderer->drawString(ostr.str().c_str(), 0, 0);

#endif
	// ☆MapDataのレイヤー分け用
	renderer->setLayer(def::L_MAIN);
}

void Player::update()
{
	if (hitflg == true)
	{
		PlayerMove();
	}
	if (timerflg == true)
	{
		timer();
	}
	bHit = hitting;
	currentpos = position;
	if (!hitting) hitTag = def::C_NONE;
	MoveObject::moveUpdate();
	spawnSpiritual();
	if (time++ % 6 == 0) animation++;
	if (sptime++ % 12 == 0)spanim++;
	camera->setPosition(position);
	hitting = false;
	moveSpeed = speed;
}

void Player::move()
{

	if (gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.x -= moveSpeed;
		direction = DR_LEFT;
		PmoveX = moveValue.x;
		PmoveY = moveValue.y;
		if (leftstop == true)
		{
			moveValue.x += moveSpeed;
			leftstop = false;
		}
	}
	else if (gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.x += moveSpeed;
		direction = DR_RIGHT;
		PmoveX = moveValue.x;
		PmoveY = moveValue.y;
		if (rightstop == true)
		{
			moveValue.x -= moveSpeed;
			rightstop = false;
		}
	}
	if (gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.y -= moveSpeed;
		direction = DR_UP;
		PmoveY = moveValue.y;
		PmoveX = moveValue.x;
		if (topstop == true)
		{
			moveValue.y += moveSpeed;
			topstop = false;
	}
	}
	else if (gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.y += moveSpeed;
		direction = DR_DOWN;
		PmoveY = moveValue.y;
		PmoveX = moveValue.x;
		if (bottomstop == true)
		{
			moveValue.y -= moveSpeed;
			bottomstop = false;
	}
	}
	if (gamePad->getInputButton(PAD_INPUT_2) == State::STATE_PRESS)
	{
		moveValue /= 2;
	}

}

void Player::hited(Character* _target)
{
	// TODO:条件をタグにする
	if (typeid(*_target) == typeid(Enemy))
	{
		soundManager->playSE("PlayerDamageSE");
		return;
	}
	if (typeid(*_target) == typeid(GM_ironball))
	{
		return;
	}
	if (typeid(*_target) == typeid(GM_arrow))
	{
		if (_target->isSpiritual())
		return;
	}
	if (_target->getTag() == def::C_SPIDERNET)
	{
		moveSpeed /= _target->isSpiritual() ? 1 : 2;
		return;
	}

	if (_target->getTag() == def::C_ENEMY)
	{
		printf("%d", PlayerDamageFlg);
		PlayerDamageFlg = true;
		return;
	}
	
	if (_target->getTag() == def::C_TREASURE)
	{
		treasureFlg = true;
		return;
	}

	if ((_target->getTag() == def::C_PASS_UP ||
		_target->getTag() == def::C_PASS_DOWN ||
		_target->getTag() == def::C_PASS_LEFT ||
		_target->getTag() == def::C_PASS_RIGHT) &&
		!bHit)
	{
		hitTag = _target->getTag();
		nextIndex = ((Passage*)_target)->getNextIndex();
	}
	hitting = true;
}

def::CTag Player::getHitTag()
{
	return hitTag;
}

void Player::reversePosX()
{
	position.x = -position.x + Map::widthSize;
}

void Player::reversePosY()
{
	position.y = -position.y + Map::heightSize;
}

bool Player::isHit()
{
	return hitting;
}
void Player::PlayerMove()
{
	timerflg = true;

	moveValue.x = -PmoveX / 2;

	moveValue.y = -PmoveY / 2;
	hitflg = false;
}

void Player::timer()
{
	t = t - 0.1f;
	if (t <= 0)
	{
		t = 3.0f;
		timerflg = false;
	}
}

void Player::hitLeft(Character* _target)
{
	if (typeid(*_target) == typeid(Block))
	{
		return;
	}
}

void Player::hitRight(Character* _target)
{
	if (typeid(*_target) == typeid(Block))
	{
		return;
	}
}

void Player::hitTop(Character* _target)
{
	if (typeid(*_target) == typeid(Block))
	{
		return;
	}
}

void Player::hitBottom(Character* _target)
{
	if (typeid(*_target) == typeid(Block))
	{
		return;
	}
}

void Player::spawnSpiritual()
{
	if (gamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN)
	{
		mediator->addObj
			(
			new Spiritual
			(
			gamePlayBundle, position, halfSize, direction
			)
			);
	}
}

// プレイヤーパラメータークラス作ったらそのうち消す
bool Player::isTreasure()
{
	return treasureFlg;
}

def::Vector2 Player::getpos()
{
	return	currentpos;
}
