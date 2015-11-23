#ifndef _PASSAGE_
#define _PASSAGE_

#include "def.h"
#include "Character.h"

class GamePlayBundle;

namespace def
{
	enum PassDir
	{
		P_UP = -3,
		P_LEFT = -1,
		P_RIGHT = 1,
		P_DOWN = 3,
	};
}

// ŽŸ‚Ì•”‰®‚ÖˆÚ“®‚·‚éƒCƒxƒ“ƒg
class Passage : public Character
{
public:
	Passage(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::PassDir _nIndex, def::CTag _tag);
	virtual ~Passage();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void hited(Character* _target);
	int getNextIndex();
protected:
	bool hitting;
	int nIndex;
};

#endif