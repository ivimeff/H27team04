#include "CharacterManager.h"

CharacterManager::CharacterManager(DataManager* _DataManager, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_MapData(_MapData), m_Camera(_Camera)
{
	characterFactory = new CharacterFactory(_DataManager, _MapData, _Camera);
}

CharacterManager::~CharacterManager()
{
	delete characterFactory;
}

void CharacterManager::init()
{
	m_Characters.clear();
	for (int y = 0; y < Map::height; ++y)
	{
		for (int x = 0; x < Map::width; ++x)
		{
			int obj = m_MapData->getObj(x, y);
			if (obj != Factory::ENEMY_0) continue;
			Character* ch = characterFactory->createCharacter(Factory::ENEMY_0, D3DXVECTOR2(x * Map::chipSize, y * Map::chipSize));
			add(ch);
		}
	}
}

void CharacterManager::update()
{
	// auto ‚Íitr‚ÌŒ^‚ª–Ê“|‚¾‚©‚çŠÈ’P‚É‚µ‚½‚à‚Ì‚Æl‚¦‚Ä‚æ‚¢‚Ì‚©‚È
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