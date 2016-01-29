#pragma once

#include "Effect.h"
#include "GenericControll.h"
#include "IEffectMediator.h"

class EffectManager : public GenericControll<Effect>, IEffectMediator
{
public:
	EffectManager();
	void addObj(Effect* _object);
	virtual ~EffectManager();
	void init() {}
private:
	void hit() {}
	void firstUpdate() {}
	void firstDraw() {}
	bool isFinished() { return false; }

	void initOne(Effect* _object);
	void updateOne(Effect* _object);
	void drawOne(Effect* _object);
	void removeOne(Effect* _object);
	bool isDead(Effect* _object);
};