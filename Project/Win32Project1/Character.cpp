#include "Character.h"

Character::Character(DataManager *_DataManager, MapData *_MapData) :
dataManager(_DataManager), mapData(_MapData),  position(D3DXVECTOR2(0, 0))
{

}

Character::Character(DataManager *_DataManager, MapData *_MapData, D3DXVECTOR2 _position) :
dataManager(_DataManager), mapData(_MapData), position(_position)
{}

Character::~Character()
{}

void Character::init()
{}

void Character::update()
{}

void Character::draw()
{}