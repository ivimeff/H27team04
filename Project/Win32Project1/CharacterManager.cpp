#include "CharacterManager.h"
#include "Player.h"

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
	//objects.clear();
	for (int y = 0; y < Map::height; ++y)
	{
		for (int x = 0; x < Map::width; ++x)
		{
			Factory::CharacteNname obj = (Factory::CharacteNname)m_MapData->getObj(x, y);
			if (obj == 0) continue;
			Character* ch = characterFactory->createCharacter(obj, def::Vector2((x + 0.5f) * Map::chipSize, (y + 0.5f) * Map::chipSize));
			if (ch == nullptr) continue;
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
	for (Character* obj : objects)
	{
		hitLoop(obj);
	}
}

void CharacterManager::hitLoop(Character* _obj1)
{
	for (Character* obj2 : objects)
	{
		hitCharacter(_obj1, obj2);
	}
}

void CharacterManager::hitCharacter(Character* _obj1, Character* _obj2)
{
	if (_obj1 == _obj2 || !_obj1->getRect().isCol(_obj2->getRect())) return;
	_obj1->hited(_obj2);
	_obj2->hited(_obj1);
}

bool CharacterManager::isFinished()
{
	for (Character* obj : objects)
	{
		if (obj->getTag() != def::C_PLAYER) continue;
		if (((Player*)obj)->getHitTag() != def::C_PASS_UP &&
			((Player*)obj)->getHitTag() != def::C_PASS_DOWN) continue;
		obj->init();
		reload();
		return false;
	}
	return false;
}

void CharacterManager::reload()
{
	for (auto itr = objects.begin(); itr != objects.end();)
	{
		if ((*itr)->getTag() != def::C_PLAYER)
		{
			delete *itr;
			itr = objects.erase(itr);
			continue;
		}
		++itr;
	}
	init();
}