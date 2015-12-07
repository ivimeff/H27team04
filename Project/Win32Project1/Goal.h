#ifndef _GOAL_
#define _GOLA_

#include "Character.h"

class Goal : public Character
{
public:
	Goal(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~Goal();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
	bool isGoal();
private:
	bool goalFlg;
};

#endif