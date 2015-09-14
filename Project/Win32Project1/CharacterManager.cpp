#include "CharacterManager.h"

CharacterManager::CharacterManager(DataManager* _DataManager, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_MapData(_MapData), m_Camera(_Camera)
{

}

CharacterManager::~CharacterManager() {}

void CharacterManager::init()
{
	m_Characters.clear();
}

void CharacterManager::update()
{
	for (auto itr = m_Characters.begin(); itr != m_Characters.end(); ++itr)
	{
		(*itr)->update();
		if (!(*itr)->isDead()) continue;
		m_Characters.erase(itr);
	}
}

void CharacterManager::draw()
{
	for (auto itr = m_Characters.begin(); itr != m_Characters.end(); ++itr)
	{
		(*itr)->draw();
	}
}

void CharacterManager::add(Character* _character)
{
	_character->init();
	m_Characters.push_back(_character);
}