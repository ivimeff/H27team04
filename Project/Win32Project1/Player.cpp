#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "Enemy.h"
#include "GM_ironball.h"
#include "Passage.h"
#include"Block.h"

bool Player::hitflg = false;

Player::Player(GamePlayBundle* _GamePlayBandle) : Player(_GamePlayBandle, def::Vector2(0, 0)) {}

Player::Player(GamePlayBundle* _GamePlayBandle, def::Vector2 _position) : MoveObject(_GamePlayBandle, _position, def::C_PLAYER)
{
	size = playerSize;
	halfSize = playerHalfSize;
	hitTag = def::C_NONE;
	direction = DR_DOWN;
	hitting = bHit = false;

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
		reversePosY();
		mapData->changeMap(1);
		break;
	case def::C_PASS_DOWN:
		reversePosY();
		mapData->changeMap(-1);
		break;
	}
	hitTag = def::C_NONE;
	t = 3.0f;
	PmoveX = 0.0f;
	PmoveY = 0.0f;
}

void Player::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	renderer->drawTextureRect(dataManager->anim, drawPos.x, drawPos.y,
		animation % 4 * size.x, direction * size.y, size.x, size.y);
	//やること
	//一つの方向のみにする
	//判定を付ける
	//+α
	//もうちょっと短く書く
	//あとなぜかスペース押しながらだと左斜め上移動ができない			//パッドに書き直す
	if (gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_PRESS && CheckHitKey(KEY_INPUT_SPACE))
	{
		renderer->drawTextureRect(dataManager->spiritual, drawPos.x - 64, drawPos.y - 8,
			spanim % 4 * spsize.x, 0, spsize.x, spsize.y);
	}
	if (gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_PRESS&& CheckHitKey(KEY_INPUT_SPACE))
	{
		renderer->drawTextureRect(dataManager->spiritual, drawPos.x + 32, drawPos.y - 8,
			spanim % 4 * spsize.x, 0, spsize.x, spsize.y);
	}
	if (gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_PRESS&& CheckHitKey(KEY_INPUT_SPACE))
	{
		renderer->drawTextureRect(dataManager->spiritual, drawPos.x - 16, drawPos.y - 64,
			spanim % 4 * spsize.x, 0, spsize.x, spsize.y);
	}
	if (gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_PRESS&& CheckHitKey(KEY_INPUT_SPACE))
	{
		renderer->drawTextureRect(dataManager->spiritual, drawPos.x - 16, drawPos.y + 48,
			spanim % 4 * spsize.x, 0, spsize.x, spsize.y);
	}

#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	std::ostringstream ostr;
	ostr << "X:" << position.x << ", Y:" << position.y;
	renderer->drawString(ostr.str().c_str(), 0, 0);
#endif
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
	if (!hitting) hitTag = def::C_NONE;
	MoveObject::moveUpdate();
	if (time++ % 6 == 0) animation++;
	if (sptime++ % 12 == 0)spanim++;
	camera->setPosition(position);
	hitting = false;
}

void Player::move()
{

	if (gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.x -= speed;
		direction = DR_LEFT;
		PmoveX = moveValue.x;
		PmoveY = moveValue.y;
	}
	else if (gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.x += speed;
		direction = DR_RIGHT;
		PmoveX = moveValue.x;
		PmoveY = moveValue.y;
	}
	if (gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.y -= speed;
		direction = DR_UP;
		PmoveY = moveValue.y;
		PmoveX = moveValue.x;
	}
	else if (gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_PRESS && timerflg == false)
	{
		moveValue.y += speed;
		direction = DR_DOWN;
		PmoveY = moveValue.y;
		PmoveX = moveValue.x;
	}

}

void Player::hited(Character* _target)
{
	if (typeid(*_target) == typeid(Enemy))
	{
		return;
	}

	if (typeid(*_target) == typeid(GM_ironball))
	{
		return;
	}


	if ((_target->getTag() == def::C_PASS_UP ||
		_target->getTag() == def::C_PASS_DOWN) &&
		!bHit)
	{
		hitTag = _target->getTag();
	}
	hitting = true;
}

def::CTag Player::getHitTag()
{
	return hitTag;
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
//やること
//体力・霊力の実装
//ダメージ処理
//クモの巣に引っかかったときのストップ処理
//除霊アクション
//ＵＩまわり