#ifndef _PASSAGE_RIGHT_
#define _PASSAGE_RIGHT_

#include "Passage.h"

// �E�̃}�b�v�Ɉړ�����C�x���g
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