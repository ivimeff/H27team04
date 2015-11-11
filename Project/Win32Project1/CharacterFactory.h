#ifndef _CHARACTER_FACTORY_
#define _CHARACTER_FACTORY_

#include "Character.h"
#include <map>

namespace Factory
{
	// イベントの分類
	enum CharacteNname
	{
		// 表示デバッグ用
		ENEMY_0 = 1,
		GIMMICK_1 = 1,
		PASSAGE_UP = 2,
		PASSAGE_DOWN = 3,
	};
}

class CharacterFactory
{
public:
	CharacterFactory(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera);
	CharacterFactory(GamePlayBundle* _GamePlayBundle);
	Character* createCharacter(Factory::CharacteNname index, def::Vector2 position);
	~CharacterFactory();
private:
	DataManager* m_DataManager;
	MapData* m_MapData;
	Camera* m_Camera;
	GamePlayBundle* m_GamePlayBundle;
	Renderer* m_Renderer;
	std::map<Factory::CharacteNname, Character*> characters;
};

#endif