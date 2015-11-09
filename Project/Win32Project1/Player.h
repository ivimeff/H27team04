#ifndef _PLAYER_
#define _PLAYER_

#include "def.h"
#include "DataManager.h"
#include "MoveObject.h"

enum DIRECTION
{
	DR_DOWN = 0,
	DR_RIGHT = 1,
	DR_LEFT = 2,
	DR_UP = 3,
};

class Player : public MoveObject
{
public:
	Player(GamePlayBundle* _GamePlayBundle);
	Player(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Player();
	void init();
	void draw();
	void update();
	void hited(Character* _target);
	void reversePosY();
	def::CTag getHitTag();
	bool isHit();
private:
	DIRECTION direction;
	def::CTag hitTag;
	const float speed = 3.0f;
	int animation, time;
	bool hitting, bHit;
	void move();
	void moveUpdate();
	// サイズ
	const def::Vector2 playerSize = def::Vector2(32, 48);
	// 半分のサイズ
	const def::Vector2 playerHalfSize = def::Vector2(16, 24);
};

#endif