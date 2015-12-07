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
	renderer->drawTextureRect(dataManager->ironball, drawPos.x, drawPos.y,
		animation % 4 * size.x,0,size.x, size.y);
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
	if ((typeid(_target) == typeid(Player)))
		return;
	hit = true;
}

//•Ç‚É“–‚½‚Á‚½‚ç
void GM_ironball::onDent()
{
	hit = true;
	speed = -speed;
}