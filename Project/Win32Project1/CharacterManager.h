#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "Character.h"
#include "CharacterFactory.h"
#include "GenericControll.h"
#include "ICharacterMediator.h"
#include <vector>
#include "def.h"
#include "Player.h"

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
	bool GetPlayerDamageFlg();
private:
	DataManager* m_DataManager;
	SoundManager* m_SoundManager;
	Renderer* m_Renderer;
	MapData* m_MapData;
	Camera* m_Camera;
	GamePlayBundle* m_GamePlayBundle;
	CharacterFactory* characterFactory;
	Player*m_Player;
	 
	void hit();
	void hitLoop(Character* _obj1);
	void hitCharacter(Character* _obj1, Character* _obj2);
	void hitPlayer();
	void hitleft(Character* _obj1, Character* _obj2);
	void hitright(Character* _obj1, Character* _obj2);
	void hittop(Character* _obj1, Character* _obj2);
	void hitbottom(Character* _obj1, Character* _obj2);

	void initOne(Character* _object);
	void firstUpdate();
	void updateOne(Character* _object);
	void firstDraw();
	void drawOne(Character* _object);
	//void add(Character* _object);
	bool isDead(Character* _object);
	void reload();
	bool isFinished();
};

#endif