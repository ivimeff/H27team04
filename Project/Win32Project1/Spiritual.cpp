#include "Spiritual.h"
#include "Player.h"
#include <DxLib.h>

Spiritual::Spiritual(GamePlayBundle* _GamePlayBundle, def::Vector2& _playerPos, def::Vector2& _halfSize, DIRECTION& _dir) :
Character(_GamePlayBundle, _playerPos, def::C_SPIRITUAL), playerPos(_playerPos), playerHalfSize(_halfSize), dir(_dir), animNum(0), animTime(0)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Spiritual::~Spiritual()
{

}

void Spiritual::init()
{
	setDir();
}

void Spiritual::update()
{
	setDir();
	if (++animTime % 12 == 0) ++animNum;
	if (gamePad->getInputButton(PAD_INPUT_2) == State::STATE_RELEASE) deadFlg = true;
}

void Spiritual::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - cPos - halfSize;
	renderer->drawTextureRect(dataManager->spiritual, drawPos.x, drawPos.y,
		animNum % 4 * size.x, 0, size.x, size.y);

#ifdef _DEBUG
	renderer->drawRect(drawPos, size);
#endif

}

void Spiritual::hited(Character* _target)
{

}

void Spiritual::setDir()
{
	position = playerPos;
	switch (dir)
	{
	case DIRECTION::DR_LEFT:
		position.x = playerPos.x - playerHalfSize.x - halfSize.x;
		break;
	case DIRECTION::DR_RIGHT:
		position.x = playerPos.x + playerHalfSize.x + halfSize.x;
		break;
	case DIRECTION::DR_UP:
		position.y = playerPos.y - playerHalfSize.y - halfSize.y;
		break;
	case DIRECTION::DR_DOWN:
		position.y = playerPos.y + playerHalfSize.y + halfSize.y;
		break;
	default:
		break;
	}
}