#include "Enemy2.h"
#include "Player.h"
#include"Block.h"
#include"Spiritual.h"
#include<math.h>
Enemy2::Enemy2(GamePlayBundle* _GamePlayBundle) : Enemy2(_GamePlayBundle, def::Vector2(0, 0)) {}

Enemy2::Enemy2(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_ENEMY)
{
}

Enemy2::~Enemy2() {}

void Enemy2::init()
{
	speed = def::Vector2(1.0f, 1.0f);
	nomalspeed = 1;
	netFlg = false;
}

void Enemy2::update()
{
	speed = (Player::getpos() - position);
	//speed.dir();
	x = fabsf(speed.x);
	y = fabsf(speed.y);
	moveUpdate();
	netFlg = false;
}

void Enemy2::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	//renderer->drawTexture("Soul", drawPos);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER("Soul", drawPos), layer);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xffffffff);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif

}

void Enemy2::move()
{
	if (x <= 200 && y <= 200)
	{
		moveValue.y += speed.dir().y;
		moveValue.x += speed.dir().x;
	}
	else
	{
		moveValue.x += nomalspeed;
	}
	moveValue /= netFlg ? 2 : 1;
}

void Enemy2::hited(Character* _target)
{
	switch (_target->getTag())
	{
	case def::C_SPIRITUAL:
		return;
	case def::C_BLOCK:
		moveValue.y -= speed.dir().y / 2;
		moveValue.x -= speed.dir().x / 2;
		if (!(x <= 200 && y <= 200))
		{
			moveValue.x += -nomalspeed;
		}
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
	//if (typeid(*_target) == typeid(Spiritual))
	//{
	//	hit = true;
	//	return;
	//}
	//if (typeid(*_target) == typeid(Block))
	//{
	//	moveValue.y -= speed.dir().y / 2;
	//	moveValue.x -= speed.dir().x / 2;
	//	if (!(x <= 200 && y <= 200))
	//	{
	//		moveValue.x += -nomalspeed;
	//	}
	//	return;
	//}
	//if (_target->getTag() == def::C_IRONBALL)
	//{
	//	if (_target->isSpiritual())
	//		deadFlg = true;
	//	return;
	//}
	//if (_target->getTag() == def::C_SPIDERNET)
	//{
	//	if (_target->isSpiritual())
	//		netFlg = true;
	//	return;
	//}
	//if ((typeid(_target) == typeid(Player))) return;
	//hit = true;
	
}

//壁に当たったら
void Enemy2::onDent()
{
	hit = true;
	nomalspeed = -nomalspeed;
}

//やること
//ダメージ処理
//クモの巣に引っかかったときのストップ処理