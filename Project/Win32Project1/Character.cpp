#include "Character.h"

Character::Character(DataManager *_DataManager, MapData *_MapData, Camera *_camera) :
//dataManager(_DataManager), mapData(_MapData), camera(_camera), position(D3DXVECTOR2(0, 0))
Character::Character(_DataManager, _MapData, _camera, D3DXVECTOR2(0, 0))
{}

Character::Character(DataManager *_DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position) :
dataManager(_DataManager), mapData(_MapData), camera(_camera), position(_position)
{
	deadFlg = false;
}

Character::Character(const Character& _character)
{
	dataManager = _character.dataManager;
	mapData = _character.mapData;
	camera = _character.camera;
	position = D3DXVECTOR2(_character.position);
}

Character::~Character()
{}

void Character::init()
{}

void Character::update()
{}

void Character::draw()
{}

void Character::setPosition(D3DXVECTOR2 _position)
{
	position = D3DXVECTOR2(_position);
}

bool Character::isDead()
{
	return deadFlg;
}

bool Character::isCollision(RECT target)
{
	RECT rect = getRect();
	return rect.left < target.right &&
		rect.right > target.left &&
		rect.top < target.bottom &&
		rect.bottom > target.top;
}

RECT Character::getRect()
{
	RECT r;
	SetRect(&r,
		position.x - PlayerSize::hx,
		position.y - PlayerSize::hy,
		position.x + PlayerSize::hx,
		position.x + PlayerSize::hy);
	return r;
}