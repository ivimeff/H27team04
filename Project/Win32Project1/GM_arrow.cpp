#include "GM_arrow.h"
#include "Player.h"
#include "CharacterManager.h"
#include "GM_ArrowLauncher.h"
#include "Effect.h"

GM_arrow::GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, bool _spFlg, def::Vector2 _dir) :
MoveObject(_GamePlayBundle, _position, def::C_ARROW), direction(_dir)
{
	spFlg = _spFlg;
	// 右か左なら横長に
	// それ以外なら縦長に
	size = direction == def::Vector2().Right() || direction == def::Vector2().Left() ?
		def::Vector2(64, 32) : def::Vector2(32, 64);
	halfSize = size / 2;
}

GM_arrow::~GM_arrow()
{
}

void GM_arrow::init()
{
	speed = 2;
}

void GM_arrow::update()
{
	spiritualUpdate();
	sepos = (Player::getpos() - position);
	x = fabsf(sepos.x);
	y = fabsf(sepos.y);
	MoveObject::moveUpdate();
	spHitFlg = false;
}

void GM_arrow::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - cPos;

	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(spFlg ? "Arrow_SP" : "Arrow",
		drawPos, direction.angle() - PI / 2, def::Vector2(0.5f, 0.5f)), layer);
	//renderer->addDrawOrder(def::DRAWORDER("Arrow_SP", drawPos + halfSize, (spTime / maxSpTime) * 100), layer);

#ifdef _DEBUG
	renderer->drawRect(
		drawPos.x - halfSize.x, drawPos.y - halfSize.y,
		drawPos.x - halfSize.x + size.x, drawPos.y - halfSize.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif

}

void GM_arrow::move()
{
	
	moveValue += direction * speed * (spFlg ? 2 : 1);
	if (x <= 200 && y <= 200)
	{
		soundManager->playSE(spFlg ? "Arrow_QuickSE" : "Arrow_NomalSE");
	}
}

//キャラクタに当たったら
void GM_arrow::hited(Character* _target)
{
	switch (_target->getTag())
	{
	case def::C_LAUNCHER:
	case def::C_ARROW:
	case def::C_SPIDERNET:
		return;
	case def::C_SPIRITUAL:
		//spHitFlg = true;
		return;
	case def::C_PLAYER:
		if (spFlg)
			return;
		break;
	case def::C_ENEMY:
		if (spFlg)
			break;
		return;
	}
	//if (_target->getTag() == def::C_LAUNCHER) return;
	//if (_target->getTag() == def::C_PLAYER) return;
	//if (_target->getTag() == def::C_ARROW) return;
	hit = true;
	deadFlg = true;
	effect->addObj(
		new Effect(
		"Break",
		gamePlayBundle, position, def::Vector2(48, 48),
		def::AnimBase(def::Vector2(5,2), 10, 6)
		)
		);
}

bool GM_arrow::isSpiritual()
{
	return spFlg;
}

//壁に当たったら
void GM_arrow::onDent()
{
	hit = true;
	deadFlg = true;
}
