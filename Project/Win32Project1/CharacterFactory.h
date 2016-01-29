#ifndef _CHARACTER_FACTORY_
#define _CHARACTER_FACTORY_

#include "Character.h"
#include <map>

namespace Factory
{
	// イベントの分類
	enum CharacteNname : int
	{
		// 表示デバッグ用
		ENEMY_0 = 1,
		GOAL,
		TREASURE,
		START = 5,
		PASSAGE_UP = 12,
		PASSAGE_LEFT = 14,
		PASSAGE_RIGHT = 16,
		PASSAGE_DOWN = 18,
		GIMMICK_1 = 21,	//後で数字変える
		GIMMICK_2 = 22,	//後で数字変える
		GIMMICK_3 = 23,	//後で数字変える
		BLOCK = 24,
		ENEMY_1 = 25,
	};
}

class CharacterFactory
{
public:
	CharacterFactory(DataManager* _DataManager, SoundManager* _SoundManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera);
	CharacterFactory(GamePlayBundle* _GamePlayBundle);
	Character* createCharacter(Factory::CharacteNname index, def::Vector2 position);
	~CharacterFactory();
private:
	DataManager* m_DataManager;
	SoundManager* m_SoundManager;
	MapData* m_MapData;
	Camera* m_Camera;
	GamePlayBundle* m_GamePlayBundle;
	Renderer* m_Renderer;
	std::map<Factory::CharacteNname, Character*> characters;
};

#endif