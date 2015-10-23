#include "CharacterManager.h"

CharacterManager::CharacterManager(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_Renderer(_Renderer), m_MapData(_MapData), m_Camera(_Camera)
{
	characterFactory = new CharacterFactory(_DataManager, _Renderer, _MapData, _Camera);
}

CharacterManager::CharacterManager(GamePlayBundle* _GamePlayBundle) : m_GamePlayBundle(_GamePlayBundle), m_MapData(_GamePlayBundle->mapData)
{
	characterFactory = new CharacterFactory(_GamePlayBundle);
}

CharacterManager::~CharacterManager()
{
	delete characterFactory;
}

void CharacterManager::init()
{
	objects.clear();
	for (int y = 0; y < Map::height; ++y)
	{
		for (int x = 0; x < Map::width; ++x)
		{
			int obj = m_MapData->getObj(x, y);
			if (obj != Factory::ENEMY_0) continue;
			Character* ch = characterFactory->createCharacter(Factory::ENEMY_0, def::Vector2(x * Map::chipSize, y * Map::chipSize));
			add(ch);
		}
	}
}

void CharacterManager::initOne(Character* _object)
{

	_object->init();
}

void CharacterManager::updateOne(Character* _object)
{
	//// auto はitrの型が面倒だから簡単にしたものと考えてよいのかな
	//for (auto itr = m_Characters.begin(); itr != m_Characters.end(); ++itr)
	//{
	//	(*itr)->update();
	//	if (!(*itr)->isDead()) continue;
	//	m_Characters.erase(itr);
	//}
	_object->update();
}

void CharacterManager::drawOne(Character* _object)
{
	//for (auto itr = m_Characters.begin(); itr != m_Characters.end(); ++itr)
	//{
	//	(*itr)->draw();
	//}
	_object->draw();
}

//void CharacterManager::add(Character* _character)
//{
//	_character->init();
//	m_Characters.push_back(_character);
//}

bool CharacterManager::isDead(Character* _object)
{
	return _object->isDead();
}

void CharacterManager::removeOne(Character* _object)
{
	delete _object;
}

void CharacterManager::hit()
{

}