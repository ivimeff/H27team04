#include "GM_ArrowLauncher.h"
#include "ICharacterMediator.h"
#include "GM_arrow.h"

GM_ArrowLauncher::GM_ArrowLauncher(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _direction) :
Character(_GamePlayBundle, _position, def::C_LAUNCHER), direction(_direction)
{
	//size = def::Vector2(64, 64);
	//halfSize = size / 2;
}

GM_ArrowLauncher::~GM_ArrowLauncher()
{

}

void GM_ArrowLauncher::init()
{
	spawnTimer = 0;
}

void GM_ArrowLauncher::update()
{
	spiritualUpdate();
	if (spawnTimer-- < 0) spawnTimer = 0;
	spawn();
	spHitFlg = false;
	if (spFlg == true && spComplete == false)
	{
		soundManager->playSE("SpCompleteSE");
		spComplete = true;
	}
}

void GM_ArrowLauncher::draw()
{
	// ※描画座標をテクスチャの中心に変更している
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(def::DRAWORDER(
		spFlg ? "Arrowbox_SP" : "Arrowbox",
		drawPos, direction.angle() - PI / 2, def::Vector2(0.5f, 0.5f)), layer);
	renderer->addDrawOrder(def::DRAWORDER(
		"Arrowbox_SP", drawPos, (spTime / maxSpTime) * 100), layer);
#ifdef _DEBUG
	renderer->drawRect(drawPos - halfSize, size, 0xff00ff00);
#endif
}

void GM_ArrowLauncher::hited(Character* _target)
{
	if (_target->getTag() == def::C_SPIRITUAL)
		spHitFlg = true;
}

void GM_ArrowLauncher::hitLeft(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER)
	{
		Player::rightstop = true;
	}
}

void GM_ArrowLauncher::hitRight(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER)
	{
		Player::leftstop = true;
	}
}

void GM_ArrowLauncher::hitTop(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER)
	{
		Player::bottomstop = true;
	}
}

void GM_ArrowLauncher::hitBottom(Character* _target)
{
	if (_target->getTag() == def::C_PLAYER)
	{
		Player::topstop = true;
	}
}
void GM_ArrowLauncher::spawn()
{
	if (spawnTimer > 0) return;
	mediator->addObj(new GM_arrow(gamePlayBundle, position, spFlg, direction));
	spawnTimer = intervalSpawn;
}