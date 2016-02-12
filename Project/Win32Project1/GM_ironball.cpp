#include "GM_ironball.h"
#include "Player.h"
#include "CharacterManager.h"

//GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle) : GM_ironball(_GamePlayBundle, def::Vector2(0, 0)) {}

GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _dir) :
MoveObject(_GamePlayBundle, _position, def::C_IRONBALL), direction(_dir)
{
}

GM_ironball::~GM_ironball() {}

void GM_ironball::init()
{
	animation = time = 0;
	speed = 2;
	spFlg = false;
}

void GM_ironball::update()
{
	spiritualUpdate();
	if (time++ % 3 == 0)animation++;
	sepos = (Player::getpos() - position);
	x = fabsf(sepos.x);
	y = fabsf(sepos.y);
	if (spFlg == true && spComplete == false)
	{
		soundManager->playSE("SpCompleteSE");
		spComplete = true;
	}
	MoveObject::moveUpdate();
	spHitFlg = false;
}

void GM_ironball::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);
	// 
	//renderer->drawTextureRect("Ironball", drawPos.x, drawPos.y,
	//	animation % 4 * size.x,0,size.x, size.y);
	def::Rect srcRect = def::Rect(
		animation % 4 * size.x, 0,
		(animation % 4 + 1) * size.x, size.y);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(
		spFlg ? "Ironball_SP" : 
		"Ironball", drawPos, srcRect), layer);
	if (spHitFlg) renderer->addDrawOrder(
		def::DRAWORDER(
		"Ironball_SP", drawPos + halfSize, srcRect,
		(spTime / maxSpTime) * 100), layer
		);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif
	
}

void GM_ironball::move()
{
	moveValue += direction * speed;
	if (x <= 200 && y <= 200)
	{
		soundManager->playSE("IronballSE");
	}
}

//ƒLƒƒƒ‰ƒNƒ^‚É“–‚½‚Á‚½‚ç
void GM_ironball::hited(Character* _target)
{
	switch (_target->getTag())
	{
	case def::C_PLAYER:
		if (spFlg)
			return;
		break;
	case def::C_SPIRITUAL:
		spHitFlg = true;
		return;
	case def::C_IRONBALL:
		direction *= -1;
		break;
	}
	hit = true;
}

//•Ç‚É“–‚½‚Á‚½‚ç
void GM_ironball::onDent()
{
	hit = true;
	//speed = -speed;
	direction *= -1;
}

bool GM_ironball::isSpiritual()
{
	return spFlg;
}