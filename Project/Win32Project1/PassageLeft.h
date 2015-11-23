#ifndef _PASSAGE_LEFT_
#define _PASSAGE_LEFT_

#include "Passage.h"

// 左のマップに移動するイベント
class PassageLeft : public Passage
{
public:
	PassageLeft(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~PassageLeft();
	void init();
	void update();
	void draw();
};

#endif