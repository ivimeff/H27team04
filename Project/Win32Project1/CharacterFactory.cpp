#include "CharacterFactory.h"
#include "Enemy.h"

CharacterFactory::CharacterFactory(DataManager* _DataManager, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_MapData(_MapData), m_Camera(_Camera) {}

CharacterFactory::~CharacterFactory()
{
	delete &characters;
}

Character* CharacterFactory::createCharacter(Factory::CharacteNname index, D3DXVECTOR2 position)
{
	switch (index)
		{
		// ���̕ӂɃC�x���g�̒ǉ�
	case Factory::ENEMY_0:
		return new Enemy(m_DataManager, m_MapData, m_Camera, position);
	default:
		break;
	}
	return nullptr;
}