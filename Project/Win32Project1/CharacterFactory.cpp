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
		// ‚±‚Ì•Ó‚ÉƒCƒxƒ“ƒg‚Ì’Ç‰Á
	case Factory::ENEMY_0:
		return new Enemy(m_DataManager, m_MapData, m_Camera, position);
	default:
		break;
	}
	return nullptr;
}