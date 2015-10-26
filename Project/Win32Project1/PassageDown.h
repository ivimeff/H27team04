#ifndef _PASSAGE_DOWN_
#define _PASSAGE_DOWN_

#include "Passage.h"

// 下のマップに移動するイベント
class PassageDown : public Passage
{
public:
	PassageDown(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~PassageDown();
	void init();
	void update();
	void draw();
	void hited(Character* _target);
};

#endif