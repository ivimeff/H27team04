#include"Block.h"
#include"Player.h"
#include <DxLib.h>

Block::Block(GamePlayBundle* _GamePlayBundle) : Block(_GamePlayBundle, def::Vector2(0, 0)) {}

Block::Block(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_BLOCK)
{
	size = blockSize;
	halfSize = blockHalfSize;
}

Block::~Block() {}

void Block::init()
{
	movePoint = 0;
}

void Block::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);


	renderer->drawTexture("Block", drawPos.x, drawPos.y);
#ifdef _DEBUG
	drawPos -= def::Vector2(halfSize.x, halfSize.y);
	//renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
#endif
}

void Block::update()
{
	if (moveValue == def::Vector2(0, 0) &&
		(gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_RELEASE ||
		gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_RELEASE ||
		gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_RELEASE ||
		gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_RELEASE)
		)
	{
		move_block = MOVE_STOP;
	}
	move();
	MoveObject::moveUpdate();
}

void Block::move()
{

}

void Block::hited(Character* _target)
{
	if ((typeid(_target) == typeid(Player))) return;
}


void Block::hitLeft(Character* _target)
{
	if (typeid(*_target) == typeid(Player) &&
		gamePad->getInputButton(PAD_INPUT_RIGHT) == State::STATE_PRESS &&
		(move_block == MOVE_STOP || move_block == MOVE_RIGHT))
	{
		moveValue.x += 3;
		move_block = MOVE_RIGHT;
		soundManager->playSE("BlockSE");
	}
}

void Block::hitRight(Character* _target)
{

	if (typeid(*_target) == typeid(Player) &&
		gamePad->getInputButton(PAD_INPUT_LEFT) == State::STATE_PRESS &&
		(move_block == MOVE_STOP || move_block == MOVE_LEFT))
	{
		moveValue.x -= 3;
		move_block = MOVE_LEFT;
		soundManager->playSE("BlockSE");
	}

}

void Block::hitTop(Character* _target)
{
	if (typeid(*_target) == typeid(Player) &&
		gamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_PRESS &&
		(move_block == MOVE_STOP || move_block == MOVE_DOWN))
	{
		moveValue.y += 3;
		move_block = MOVE_DOWN;
		soundManager->playSE("BlockSE");
	}
}

void Block::hitBottom(Character* _target)
{
	if (typeid(*_target) == typeid(Player) &&
		gamePad->getInputButton(PAD_INPUT_UP) == State::STATE_PRESS &&
		(move_block == MOVE_STOP || move_block == MOVE_UP))
	{
		moveValue.y -= 3;
		move_block = MOVE_UP;
		soundManager->playSE("BlockSE");
	}
}

void Block::onDent()
{
	Player::hitflg = true;
}

