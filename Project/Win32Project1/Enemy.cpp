#include "Enemy.h"
#include "Player.h"
#include"Block.h"
#include "Effect.h"
Enemy::Enemy(GamePlayBundle* _GamePlayBundle) : Enemy(_GamePlayBundle, def::Vector2(0, 0)) {}

Enemy::Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_ENEMY)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

Enemy::~Enemy() {}

void Enemy::init()
{
	animation = time = 0;
	speed = 1;
	hitstate = true;
	netFlg = true;
}

void Enemy::update()
{
	if (time++ % 4 == 0)animation++;
	moveUpdate();
	netFlg = false;
	sepos = (Player::getpos() - position);
	x = fabsf(sepos.x);
	y = fabsf(sepos.y);
}

void Enemy::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	def::Rect srcRect = def::Rect(
		0, animation % 3 * size.y,
		 size.x, (animation % 3 + 1) *size.y);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER("Suraimu", drawPos,srcRect), layer);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	if(hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif
	
}

void Enemy::move()
{
	moveValue.x += speed;
	moveValue /= netFlg ? 2 : 1;

	if (x <= 200 && y <= 200)
	{
		soundManager->playSE("EnemySE");
	}
	
}

void Enemy::hited(Character* _target)
{
	//if ((typeid(_target) == typeid(Player))) return;
	//hit = true;
	switch (_target->getTag())
	{
	case def::C_SPIRITUAL:
		return;
	case def::C_BLOCK:
		return;
	case def::C_IRONBALL:
	case def::C_ARROW:
		if (_target->isSpiritual())
			deadFlg = true;
		break;
	case def::C_SPIDERNET:
		if (_target->isSpiritual())
			netFlg = true;
		return;
	case def::C_PLAYER:
		return;
	}
	effect->addObj(
		new Effect(
		"Break",
		gamePlayBundle, position, def::Vector2(48, 48),
		def::AnimBase(def::Vector2(5, 2), 10, 6)
		)
		);
}

void Enemy::hitLeft(Character* _target)
{
	if (typeid(*_target) == typeid(Block) && hitstate == false)
	{
		moveValue.x = moveValue.x - speed;
	}
	if (typeid(*_target) == typeid(Block) && hitstate == true)
	{
		moveValue.x = moveValue.x + 3;
	}
}

void Enemy::hitRight(Character* _target)
{
	if (typeid(*_target) == typeid(Block) && hitstate == true)
	{
		moveValue.x = moveValue.x - speed;
	}

	if (typeid(*_target) == typeid(Block) && hitstate == false)
	{
		moveValue.x = moveValue.x - 3;
	}
}
//壁に当たったら
void Enemy::onDent()
{
	hit = true;
	speed = -speed;
	switch (hitstate)
	{
	case true:
		hitstate = false;
		break;
	case false:
		hitstate = true;
		break;
	}
}

//やること
//プレイヤーを追いかけてくるパターンをつくる
//ダメージ処理
//クモの巣に引っかかったときのストップ処理