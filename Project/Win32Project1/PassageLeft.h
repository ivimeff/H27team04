#ifndef _PASSAGE_LEFT_
#define _PASSAGE_LEFT_

#include "Passage.h"

// ���̃}�b�v�Ɉړ�����C�x���g
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