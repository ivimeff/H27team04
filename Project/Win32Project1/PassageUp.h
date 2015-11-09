#ifndef _PASSAGE_UP_
#define _PASSAGE_UP_

#include "Passage.h"

// 上のマップに移動するイベント
class PassageUp : public Passage
{
public:
	PassageUp(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~PassageUp();
	void init();
	void update();
	void draw();
};

#endif