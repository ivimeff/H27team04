#include "GM_ironball.h"
#include "Player.h"
#include "CharacterManager.h"

GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle) : GM_ironball(_GamePlayBundle, def::Vector2(0, 0)) {}

GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_IRONBALL)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
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
	if (time++ % 3 == 0)animation++;
	MoveObject::moveUpdate();
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
		spFlg ? "Ironball_SP" : "Ironball", drawPos, srcRect), layer);
#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif
	
}

void GM_ironball::move()
{
	moveValue.x = moveValue.x + speed;
}

//ƒLƒƒƒ‰ƒNƒ^‚É“–‚½‚Á‚½‚ç
void GM_ironball::hited(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER && spFlg)
		return;
	if (_target->getTag() == def::C_SPIRITUAL)
	{
		spFlg = true;
		return;
	}
	hit = true;
}

//•Ç‚É“–‚½‚Á‚½‚ç
void GM_ironball::onDent()
{
	hit = true;
	speed = -speed;
}

bool GM_ironball::isSpiritual()
{
	return spFlg;
}