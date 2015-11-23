#ifndef _PASSAGE_RIGHT_
#define _PASSAGE_RIGHT_

#include "Passage.h"

// 右のマップに移動するイベント
class PassageRight : public Passage
{
public:
	PassageRight(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~PassageRight();
	void init();
	void update();
	void draw();
};

#endif