#include "GM_spidernet.h"
#include "Player.h"
#include "CharacterManager.h"

GM_spidernet::GM_spidernet(GamePlayBundle* _GamePlayBundle) : GM_spidernet(_GamePlayBundle, def::Vector2(0, 0)) {}

GM_spidernet::GM_spidernet(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_SPIDERNET)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

GM_spidernet::~GM_spidernet(){}

void GM_spidernet::init()
{
	spFlg = false;
}

void GM_spidernet::update()
{
	MoveObject::moveUpdate();
}

void GM_spidernet::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);

	//renderer->drawTexture("Spidernet", drawPos.x, drawPos.y);
	
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(
		spFlg ? "Spidernet_SP" : "Spidernet", drawPos), layer);

#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif
}

void GM_spidernet::hited(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER)
		return;
	if (_target->getTag() == def::C_SPIRITUAL)
	{
		spFlg = true;
		return;
	}
	hit = true;
}

bool GM_spidernet::isSpiritual()
{
	return spFlg;
}

void GM_spidernet::move()
{

}