#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "Character.h"
#include "CharacterFactory.h"
#include <vector>

class CharacterManager
{
public:
	CharacterManager(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera);
	CharacterManager(GamePlayBundle* _GamePlayBundle);
	virtual ~CharacterManager();
	void init();
	void update();
	void draw();
	void add(Character* _character);
private:
	std::vector<Character*> m_Characters;
	DataManager* m_DataManager;
	Renderer* m_Renderer;
	MapData* m_MapData;
	Camera* m_Camera;
	GamePlayBundle* m_GamePlayBundle;
	CharacterFactory* characterFactory;
};

#endif