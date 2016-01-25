#include "CharacterManager.h"
#include "Goal.h"

CharacterManager::CharacterManager(DataManager* _DataManager, SoundManager* _SoundManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_Renderer(_Renderer), m_MapData(_MapData), m_Camera(_Camera)
{
	characterFactory = new CharacterFactory(_DataManager, _SoundManager, _Renderer, _MapData, _Camera);
}

CharacterManager::CharacterManager(GamePlayBundle* _GamePlayBundle) : m_GamePlayBundle(_GamePlayBundle), m_MapData(_GamePlayBundle->mapData)
{
	_GamePlayBundle->mediator = (ICharacterMediator*)this;
	characterFactory = new CharacterFactory(_GamePlayBundle);
	m_Player = new Player(_GamePlayBundle);
}

CharacterManager::~CharacterManager()
{
	delete characterFactory;
	delete m_Player;
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
			if (obj == Factory::START && !m_Player->isHit())
			{
				m_Player->setPosition(def::Vector2(
					(x + 0.5f) * Map::chipSize,
					(y + 0.5f) * Map::chipSize));
				continue;
			}
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

void CharacterManager::firstUpdate()
{
	m_Player->update();
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

void CharacterManager::firstDraw()
{
	m_Player->draw();
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
	hitLoop(m_Player);
	for (Character* obj : objects)
	{
		hitLoop(obj);
	}
	hitPlayer();
}

void CharacterManager::hitLoop(Character* _obj1)
{
	for (Character* obj2 : objects)
	{
		hitCharacter(_obj1, obj2);
		hitleft(_obj1, obj2);
		hitright(_obj1, obj2);
		hittop(_obj1, obj2);
		hitbottom(_obj1, obj2);
	}
}

void CharacterManager::hitPlayer()
{
	for (Character* obj : objects)
	{
		hitCharacter(obj, m_Player);
		hitleft(obj, m_Player);
		hitright(obj, m_Player);
		hittop(obj, m_Player);
		hitbottom(obj, m_Player);
	}
}

void CharacterManager::hitCharacter(Character* _obj1, Character* _obj2)
{
	if (_obj1 == _obj2 || !_obj1->getRect().isCol(_obj2->getRect())) return;
	_obj1->hited(_obj2);
	//_obj2->hited(_obj1);
}

bool CharacterManager::isFinished()
{
	//for (Character* obj : objects)
	//{
	//	if (obj->getTag() != def::C_PLAYER) continue;
	//	if (
	//		!((Player*)obj)->isHit() ||
	//		((Player*)obj)->getHitTag() != def::C_PASS_UP &&
	//		((Player*)obj)->getHitTag() != def::C_PASS_DOWN &&
	//		((Player*)obj)->getHitTag() != def::C_PASS_LEFT &&
	//		((Player*)obj)->getHitTag() != def::C_PASS_RIGHT) continue;
	//	obj->init();
	//	reload();
	//	return false;
	//}
	if (
			!m_Player->isHit() ||
			m_Player->getHitTag() != def::C_PASS_UP &&
			m_Player->getHitTag() != def::C_PASS_DOWN &&
			m_Player->getHitTag() != def::C_PASS_LEFT &&
			m_Player->getHitTag() != def::C_PASS_RIGHT) return false;
		m_Player->init();
		reload();

	return false;

}

void CharacterManager::reload()
{
	for (auto itr = objects.begin(); itr != objects.end();)
	{
			delete *itr;
			itr = objects.erase(itr);
			continue;
		++itr;
	}
	init();
}

void CharacterManager::hitleft(Character* _obj1, Character* _obj2)
{
	if (!_obj1->getObjLeftRect().isCol(_obj2->getRect())) return;
	{
		_obj1->hitLeft(_obj2);
		//_obj2->hitRight(_obj1);
	}
}

void CharacterManager::hitright(Character* _obj1, Character* _obj2)
{
	if (!_obj1->getObjRightRect().isCol(_obj2->getRect())) return;
	_obj1->hitRight(_obj2);
	//_obj2->hitLeft(_obj1);
}

void CharacterManager::hittop(Character* _obj1, Character* _obj2)
{
	if (_obj1 == _obj2 || !_obj1->getObjTopRect().isCol(_obj2->getRect())) return;
	_obj1->hitTop(_obj2);
	//_obj2->hitTop(_obj1);
}

void CharacterManager::hitbottom(Character* _obj1, Character* _obj2)
{
	if (_obj1 == _obj2 || !_obj1->getObjBottomRect().isCol(_obj2->getRect())) return;
	_obj1->hitBottom(_obj2);
	//_obj2->hitBottom(_obj1);
}

void CharacterManager::addObj(Character* _object)
{
	GenericControll<Character>::addObj(_object);
}

bool CharacterManager::isGoal()
{
	for (auto itr = objects.begin(), end = objects.end(); itr != end; ++itr)
	{
		if ((*itr)->getTag() == def::C_GOAL)
		{
			if (((Goal*)(*itr))->isGoal())
				return true;
		}
	}
	return false;
}

def::Vector2 CharacterManager::GetPlayerPosition()
{
	//for (Character* obj : objects)
	//{
	//	if (obj->getTag() == def::C_PLAYER)
	//	{
	//		return obj->getDrawPos();
	//	}
	//}
	return m_Player->getDrawPos();
}

bool CharacterManager::GetPlayerDamageFlg()
{
	printf("%d", m_Player->PlayerDamageFlg);
	return m_Player->PlayerDamageFlg; 
}