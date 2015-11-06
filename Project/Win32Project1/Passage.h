#ifndef _PASSAGE_
#define _PASSAGE_

#include "def.h"
#include "Character.h"

class GamePlayBundle;

// ŽŸ‚Ì•”‰®‚ÖˆÚ“®‚·‚éƒCƒxƒ“ƒg
class Passage : public Character
{
public:
	Passage(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, int _nIndex);
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