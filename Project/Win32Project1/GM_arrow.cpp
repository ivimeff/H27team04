#include "GM_arrow.h"
#include "Player.h"
#include "CharacterManager.h"
#include "GM_ArrowLauncher.h"

GM_arrow::GM_arrow(GamePlayBundle* _GamePlayBundle) :GM_arrow(_GamePlayBundle, def::Vector2(0, 0)) {}

GM_arrow::GM_arrow(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position, def::C_ARROW)
{
	size = def::Vector2(64, 32);
	halfSize = size / 2;
}

GM_arrow::~GM_arrow(){}

void GM_arrow::init()
{
	speed = 2;
}

void GM_arrow::update()
{
	MoveObject::moveUpdate();
}

void GM_arrow::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);

	renderer->drawTexture(dataManager->arrow, drawPos.x, drawPos.y);

#ifdef _DEBUG
	renderer->drawRect(drawPos.x, drawPos.y, drawPos.x + size.x, drawPos.y + size.y, 0xff0000);
	if (hit)
		renderer->drawString("Hit!", drawPos, 0xffff0000);
	hit = false;
#endif

}

void GM_arrow::move()
{
	moveValue.x = moveValue.x + speed;
}

//キャラクタに当たったら
void GM_arrow::hited(Character* _target)
{
	if (_target->getTag() == def::C_LAUNCHER) return;
	if (_target->getTag() == def::C_PLAYER) return;
	if (_target->getTag() == def::C_ARROW) return;
	hit = true;
	deadFlg = true;
}

//壁に当たったら
void GM_arrow::onDent()
{
	hit = true;
	//position.x = Map::chipSize;
	//戻った場所と壁が重なると矢が止まる
	deadFlg = true;
}

//やること
//壁に当たったら消える