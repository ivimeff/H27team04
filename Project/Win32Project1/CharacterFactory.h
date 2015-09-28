#ifndef _CHARACTER_FACTORY_
#define _CHARACTER_FACTORY_

#include "Character.h"
#include <map>

namespace Factory
{
	// �C�x���g�̕���
	enum CharacteNname
	{
		// �\���f�o�b�O�p
		ENEMY_0 = 1,
	};
}

class CharacterFactory
{
public:
	CharacterFactory(DataManager* _DataManager, MapData* _MapData, Camera* _Camera);
	Character* createCharacter(Factory::CharacteNname index, D3DXVECTOR2 position);
	~CharacterFactory();
private:
	DataManager* m_DataManager;
	MapData* m_MapData;
	Camera* m_Camera;
	std::map<Factory::CharacteNname, Character*> characters;
};

#endif