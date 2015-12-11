#ifndef _SPIRITUAL_
#define _SPIRITUAL_

#include "Character.h"

enum DIRECTION;

class Spiritual : public Character
{
public:
	Spiritual(GamePlayBundle* _GamePlayBundle, def::Vector2& _playerPos, def::Vector2& _halfSize, DIRECTION& _dir);
	virtual ~Spiritual();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
private:
	const def::Vector2& playerPos;
	const def::Vector2& playerHalfSize;
	DIRECTION& dir;
	void setDir();
	int animNum, animTime;
};

#endif