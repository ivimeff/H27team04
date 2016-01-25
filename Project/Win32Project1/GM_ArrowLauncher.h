#ifndef _GM_ARROW_LAUNCHER_
#define _GM_ARROW_LAUNCHER_

#include "Character.h"

class GM_ArrowLauncher : public Character
{
public:
	GM_ArrowLauncher(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _direction);
	virtual ~GM_ArrowLauncher();

	void init();
	void update();
	void draw();
	void hited(Character* _target);

	void hitLeft(Character* _target);
	void hitRight(Character* _target);
	void hitTop(Character* _target);
	void hitBottom(Character* _target);
private:
	int spawnTimer;
	const int intervalSpawn = 60;
	def::Vector2 direction;
	void spawn();
};

#endif