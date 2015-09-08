#include "Character.h"

Character::Character(DataManager *_DataManager, MapData *_MapData, Camera *_camera) :
dataManager(_DataManager), mapData(_MapData), camera(_camera), position(D3DXVECTOR2(0, 0))
{

}

Character::Character(DataManager *_DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position) :
dataManager(_DataManager), mapData(_MapData), camera(_camera), position(_position)
{}

Character::~Character()
{}

void Character::init()
{}

void Character::update()
{}

void Character::draw()
{}