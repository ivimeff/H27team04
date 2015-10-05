#include "Character.h"

Character::Character(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera) :
//dataManager(_DataManager), mapData(_MapData), camera(_camera), position(D3DXVECTOR2(0, 0))
Character::Character(_DataManager, _Renderer, _MapData, _camera, def::Vector2(0, 0))
{}

Character::Character(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position) :
dataManager(_DataManager), renderer(_Renderer), mapData(_MapData), camera(_camera), position(_position)
{
	deadFlg = false;
}

Character::Character(GamePlayBundle* _GamePlayBundle) :
Character(_GamePlayBundle, def::Vector2(0, 0)) {}

Character::Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position) :
dataManager(_GamePlayBundle->dataManager), renderer(_GamePlayBundle->renderer),
mapData(_GamePlayBundle->mapData), camera(_GamePlayBundle->camera), position(_position), gamePad(_GamePlayBundle->gamePad)
{
	deadFlg = false;
}

Character::Character(const Character& _character)
{
	dataManager = _character.dataManager;
	mapData = _character.mapData;
	camera = _character.camera;
	position = def::Vector2(_character.position);
}

Character::~Character()
{}

void Character::init()
{}

void Character::update()
{}

void Character::draw()
{}

void Character::setPosition(def::Vector2 _position)
{
	position = def::Vector2(_position);
}

bool Character::isDead()
{
	return deadFlg;
}

bool Character::isCollision(def::Rect target)
{
	def::Rect rect = getRect();
	return rect.left < target.right &&
		rect.right > target.left &&
		rect.top < target.bottom &&
		rect.bottom > target.top;
}

def::Rect Character::getRect()
{
	def::Rect r = def::Rect(
		position.x - halfSize.x,
		position.y - halfSize.y,
		position.x + halfSize.x,
		position.x + halfSize.y);
	return r;
}