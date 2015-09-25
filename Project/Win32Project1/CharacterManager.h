#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "Character.h"
#include "CharacterFactory.h"
#include <vector>

class CharacterManager
{
public:
	CharacterManager(DataManager* _DataManager, MapData* _MapData, Camera* _Camera);
	virtual ~CharacterManager();
	void init();
	void update();
	void draw();
	void add(Character* _character);
private:
	std::vector<Character*> m_Characters;
	DataManager* m_DataManager;
	MapData* m_MapData;
	Camera* m_Camera;
	CharacterFactory* characterFactory;
};

#endif