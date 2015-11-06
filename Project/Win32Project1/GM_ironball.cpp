#include "GM_ironball.h"
#include "Player.h"

GM_ironball::GM_ironball(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera) :
GM_ironball(_DataManager, _Renderer, _MapData, _camera, def::Vector2(0, 0))
{}

GM_ironball::GM_ironball(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position) :
MoveObject(_DataManager, _Renderer, _MapData, _camera, _position)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle) : GM_ironball(_GamePlayBundle, def::Vector2(0, 0)) {}

GM_ironball::GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) : MoveObject(_GamePlayBundle, _position)
{
	size = def::Vector2(64, 64);
	halfSize = size / 2;
}

GM_ironball::~GM_ironball() {}

void GM_ironball::init()
{
	animation = time = 0;
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
#endif
}

void GM_ironball::move()
{
	moveValue.x++;
	if ((time % 100) < 50)
	{
		moveValue.y--;
	}
	else
	{
		moveValue.y++;
	}
}