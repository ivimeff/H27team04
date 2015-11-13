#include "CharacterFactory.h"
#include "Enemy.h"
#include "GM_ironball.h"
#include "GM_arrow.h"
#include "GM_spidernet.h"
#include "PassageUp.h"
#include "PassageDown.h"

CharacterFactory::CharacterFactory(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera) :
m_DataManager(_DataManager), m_Renderer(_Renderer), m_MapData(_MapData), m_Camera(_Camera) {}

CharacterFactory::CharacterFactory(GamePlayBundle* _GamePlayBundle) : m_GamePlayBundle(_GamePlayBundle) {}

CharacterFactory::~CharacterFactory()
{
	//コメントアウトしないと止まる
	//delete &characters;
}

Character* CharacterFactory::createCharacter(Factory::CharacteNname index, def::Vector2 position)
{
	switch (index)
	{
		// この辺にイベントの追加
	/*case Factory::ENEMY_0:
		return new Enemy(m_GamePlayBundle, position);*/
	/*case Factory::GIMMICK_1:
		return new GM_ironball(m_GamePlayBundle, position);*/
	/*case Factory::GIMMICK_2:
		return new GM_arrow(m_GamePlayBundle, position);*/
	case Factory::GIMMICK_3:
		return new GM_spidernet(m_GamePlayBundle, position);
	case Factory::PASSAGE_UP:
		return new PassageUp(m_GamePlayBundle, position);
	case Factory::PASSAGE_DOWN:
		return new PassageDown(m_GamePlayBundle, position);
	default:
		break;
	}
	return nullptr;
}