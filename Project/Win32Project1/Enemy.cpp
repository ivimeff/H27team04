#include "Enemy.h"
#include "Player.h"
#include"Block.h"
Enemy::Enemy(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _dir) :
MoveObject(_GamePlayBundle, _position, def::C_ENEMY), direction(_dir)
{
	//size = def::Vector2(64, 64);
	//halfSize = size / 2;
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
	pPos.x = fabsf(sepos.x);
	pPos.y = fabsf(sepos.y);
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
	moveValue += direction * speed;
	moveValue /= netFlg ? 2 : 1;

	if (pPos.x <= 200 && pPos.y <= 200)
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
	case def::C_BLOCK:
	case def::C_PLAYER:
		return;
	case def::C_IRONBALL:
	case def::C_ARROW:
		if (_target->isSpiritual())
			soundManager->playSE("EnemyDamegeSE");
			deadFlg = true;
		break;
	case def::C_SPIDERNET:
		if (_target->isSpiritual())
			netFlg = true;
		return;
	}
}

#define __CHECKER(XY) switch(_target->getTag()) \
{ \
case def::C_BLOCK: \
	direction.##XY *= hitstate ? 1 : -1; \
	break; \
}

void Enemy::hitLeft(Character* _target)
{
	__CHECKER(x)
}

void Enemy::hitRight(Character* _target)
{
	__CHECKER(x)
}

void Enemy::hitTop(Character* _target)
{
	__CHECKER(y)
}

void Enemy::hitBottom(Character* _target)
{
	__CHECKER(y)
}

//壁に当たったら
void Enemy::onDent()
{
	hit = true;
	//speed = -speed;
	direction *= -1;
	hitstate = !hitstate;
	//switch (hitstate)
	//{
	//case true:
	//	hitstate = false;
	//	break;
	//case false:
	//	hitstate = true;
	//	break;
	//}
}

//やること
//プレイヤーを追いかけてくるパターンをつくる
//ダメージ処理
//クモの巣に引っかかったときのストップ処理