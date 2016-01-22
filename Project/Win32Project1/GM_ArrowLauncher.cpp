#include "GM_ArrowLauncher.h"
#include "ICharacterMediator.h"
#include "GM_arrow.h"

GM_ArrowLauncher::GM_ArrowLauncher(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _direction) :
Character(_GamePlayBundle, _position, def::C_LAUNCHER), direction(_direction)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
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
	if (spawnTimer-- < 0) spawnTimer = 0;
	spawn();
}

void GM_ArrowLauncher::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		drawPos = position - (cPos + halfSize);

	renderer->drawTexture("Arrowbox", drawPos.x, drawPos.y);

#ifdef _DEBUG
	renderer->drawRect(drawPos, size, 0xff00ff00);
#endif
}

void GM_ArrowLauncher::hited(Character* _target)
{
	if (_target->getTag() == def::C_SPIRITUAL)
		spFlg = true;
}

void GM_ArrowLauncher::spawn()
{
	if (spawnTimer > 0) return;
	mediator->addObj(new GM_arrow(gamePlayBundle, position, spFlg));
	spawnTimer = intervalSpawn;
}