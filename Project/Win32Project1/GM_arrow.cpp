#include "GM_arrow.h"
#include "Player.h"
#include "CharacterManager.h"
#include "GM_ArrowLauncher.h"
#include "Effect.h"

GM_arrow::GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, bool _spFlg) :GM_arrow(_GamePlayBundle, _position)
{
	spFlg = _spFlg;
}

GM_arrow::GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_ARROW)
{
	size = def::Vector2(64, 32);
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
	sepos = (Player::getpos() - position);
	x = fabsf(sepos.x);
	y = fabsf(sepos.y);
	MoveObject::moveUpdate();
}

void GM_arrow::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);

	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(spFlg ? "Arrow_SP" : "Arrow", drawPos), layer);

#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif

}

void GM_arrow::move()
{
	
	moveValue.x += speed * (spFlg ? 2 : 1);
	if (x <= 200 && y <= 200)
	{
		soundManager->playSE(spFlg ? "Arrow_QuickSE" : "Arrow_NomalSE");
	}
}

//ƒLƒƒƒ‰ƒNƒ^‚É“–‚½‚Á‚½‚ç
void GM_arrow::hited(Character* _target)
{
	switch (_target->getTag())
	{
	case def::C_LAUNCHER:
	case def::C_ARROW:
		return;
	case def::C_SPIRITUAL:
		spFlg = true;
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
		"Explosion",
		gamePlayBundle, position, def::Vector2(192, 192),
		def::AnimBase(def::Vector2(5, 2), 10, 6)
		)
		);
}

bool GM_arrow::isSpiritual()
{
	return spFlg;
}

//•Ç‚É“–‚½‚Á‚½‚ç
void GM_arrow::onDent()
{
	hit = true;
	deadFlg = true;
}
