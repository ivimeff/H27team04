#ifndef _PASSAGE_UP_
#define _PASSAGE_UP_

#include "Passage.h"

// ��̃}�b�v�Ɉړ�����C�x���g
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