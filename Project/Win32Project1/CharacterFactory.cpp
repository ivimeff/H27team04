#include "CharacterFactory.h"
#include "Enemy.h"
#include "GM_ironball.h"
#include "GM_ArrowLauncher.h"
#include "GM_spidernet.h"
#include "PassageUp.h"
#include "PassageDown.h"
#include "PassageLeft.h"
#include "PassageRight.h"
#include "Goal.h"
#include "Treasure.h"
#include"Block.h"
#include"Enemy2.h"

CharacterFactory::CharacterFactory(DataManager* _DataManager, SoundManager* _SoundManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_Renderer(_Renderer), m_MapData(_MapData), m_Camera(_Camera) {}

CharacterFactory::CharacterFactory(GamePlayBundle* _GamePlayBundle) : m_GamePlayBundle(_GamePlayBundle) {}

CharacterFactory::~CharacterFactory()
{
}
// �ړ����������I�u�W�F�N�g
#define __FACTORY_DIR_FUNC(name, obj) case Factory::##name: score++; \
case Factory::##name##_LEFT: score++; \
case Factory::##name##_UP: score++; \
case Factory::##name##_DOWN: return new obj(m_GamePlayBundle, position, \
	score == 3 ? def::Vector2().Right() : \
	score == 2 ? def::Vector2().Left() : \
	score == 1 ? def::Vector2().Up() : def::Vector2().Down());

Character* CharacterFactory::createCharacter(Factory::CharacteNname index, def::Vector2 position)
{
	score = 0;
	switch (index)
	{
		// ���̕ӂɃC�x���g�̒ǉ�
		//�G
	//case Factory::ENEMY_0:
	//	return new Enemy(m_GamePlayBundle, position, def::Vector2().Right());
		__FACTORY_DIR_FUNC(ENEMY_0, Enemy)
		// �S�[��
	case Factory::GOAL:
		return new Goal(m_GamePlayBundle, position);
	case Factory::TREASURE:
		return new Treasure(m_GamePlayBundle, position);
		//�S��
	//case Factory::GIMMICK_1:
	//	return new GM_ironball(m_GamePlayBundle, position, def::Vector2().Right());
		__FACTORY_DIR_FUNC(GIMMICK_1, GM_ironball)
		//��
	//case Factory::GIMMICK_2:
	//	return new GM_ArrowLauncher(m_GamePlayBundle, position, def::Vector2().Right());
		__FACTORY_DIR_FUNC(GIMMICK_2, GM_ArrowLauncher)
		//�w偂̑�
	case Factory::GIMMICK_3:
		return new GM_spidernet(m_GamePlayBundle, position);
		//�u���b�N
	case Factory::BLOCK:
		return new Block(m_GamePlayBundle, position);
		//�ǔ�����G
	case Factory::ENEMY_1:
		return new Enemy2(m_GamePlayBundle, position);

	case Factory::PASSAGE_UP:
		return new PassageUp(m_GamePlayBundle, position);
	case Factory::PASSAGE_DOWN:
		return new PassageDown(m_GamePlayBundle, position);
	case Factory::PASSAGE_LEFT:
		return new PassageLeft(m_GamePlayBundle, position);
	case Factory::PASSAGE_RIGHT:
		return new PassageRight(m_GamePlayBundle, position);
	default:
		break;
	}
	return nullptr;
}