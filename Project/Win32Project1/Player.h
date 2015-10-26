#ifndef _PLAYER_
#define _PLAYER_

#include "def.h"
#include "DataManager.h"
#include "MoveObject.h"

enum DIRECTION
{
	DR_DOWN = 0,
	DR_RIGHT = 1,
	DR_LEFT = 2,
	DR_UP = 3,
};

namespace PlayerSize
{
	// ���T�C�Y
	const float x = 32;
	// �c�T�C�Y
	const float y = 48;
	// ���T�C�Y�̔���
	const float hx = 16;
	// �c�T�C�Y�̔���
	const float hy = 24;
}

namespace
{
	const float speed = 3.0f;
}

class Player : public MoveObject
{
public:
	Player(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera);
	Player(DataManager *_DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position);
	Player(GamePlayBundle* _GamePlayBundle);
	Player(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Player();
	void init();
	void draw();
	void update();
	void hited(Character* _target);
private:
	DIRECTION direction;

	int animation, time;
	void move();
	void moveUpdate();
};

#endif