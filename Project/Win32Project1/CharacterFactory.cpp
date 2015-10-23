#include "CharacterFactory.h"
#include "Enemy.h"

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
	case Factory::ENEMY_0:
		return new Enemy(m_GamePlayBundle, position);
	default:
		break;
	}
	return nullptr;
}