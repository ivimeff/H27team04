#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "Character.h"
#include "CharacterFactory.h"
#include "GenericControll.h"
#include "ICharacterMediator.h"
#include <vector>
#include "def.h"

class CharacterManager : public GenericControll<Character>, ICharacterMediator
{
public:
	CharacterManager(DataManager* _DataManager, SoundManager* _SoundManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera);
	CharacterManager(GamePlayBundle* _GamePlayBundle);
	virtual ~CharacterManager();
	void init();
	void addObj(Character* _object);

	def::Vector2 GetPlayerPosition();
	bool isGoal();
private:
	DataManager* m_DataManager;
	SoundManager* m_SoundManager;
	Renderer* m_Renderer;
	MapData* m_MapData;
	Camera* m_Camera;
	GamePlayBundle* m_GamePlayBundle;
	CharacterFactory* characterFactory;

	void hit();
	void hitLoop(Character* _obj1);
	void hitCharacter(Character* _obj1, Character* _obj2);
	void hitleft(Character* _obj1, Character* _obj2);
	void hitright(Character* _obj1, Character* _obj2);
	void hittop(Character* _obj1, Character* _obj2);
	void hitbottom(Character* _obj1, Character* _obj2);

	void initOne(Character* _object);
	void updateOne(Character* _object);
	void drawOne(Character* _object);
	//void add(Character* _object);
	bool isDead(Character* _object);
	void removeOne(Character* _object);
	void reload();
	bool isFinished();
};

#endif