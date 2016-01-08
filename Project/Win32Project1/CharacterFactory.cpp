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

CharacterFactory::CharacterFactory(DataManager* _DataManager, SoundManager* _SoundManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_Renderer(_Renderer), m_MapData(_MapData), m_Camera(_Camera) {}

CharacterFactory::CharacterFactory(GamePlayBundle* _GamePlayBundle) : m_GamePlayBundle(_GamePlayBundle) {}

CharacterFactory::~CharacterFactory()
{
}

Character* CharacterFactory::createCharacter(Factory::CharacteNname index, def::Vector2 position)
{
	switch (index)
	{
		// Ç±ÇÃï”Ç…ÉCÉxÉìÉgÇÃí«â¡
		//ìG
	case Factory::ENEMY_0:
		return new Enemy(m_GamePlayBundle, position);
		// ÉSÅ[Éã
	case Factory::GOAL:
		return new Goal(m_GamePlayBundle, position);
	case Factory::TREASURE:
		return new Treasure(m_GamePlayBundle, position);
		//ìSãÖ
	case Factory::GIMMICK_1:
		return new GM_ironball(m_GamePlayBundle, position);
		//ñÓ
	case Factory::GIMMICK_2:
		return new GM_ArrowLauncher(m_GamePlayBundle, position, def::Vector2(1, 0));
		//íwÂÅÇÃëÉ
	case Factory::GIMMICK_3:
		return new GM_spidernet(m_GamePlayBundle, position);

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