#ifndef _BLOCK_
#define _BLOCK_

#include "def.h"
#include "MoveObject.h"

enum MOVE_BLOCK
{
	MOVE_DOWN = 0,
	MOVE_RIGHT = 1,
	MOVE_LEFT = 2,
	MOVE_UP = 3,
	MOVE_STOP = 4,
};

class Block :public MoveObject
{
public:

	Block(GamePlayBundle* _GamePlayBundle);
	Block(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~Block();

	void init();
	void draw();
	void update();
	void hited(Character* _target);

	void hitLeft(Character* _target);
	void hitRight(Character* _target);
	void hitTop(Character* _target);
	void hitBottom(Character* _target);

	void onDent();
private:
	MOVE_BLOCK move_block;
	void move();
	void moveUpdate();
	float movePoint;

	// サイズ
	const def::Vector2 blockSize = def::Vector2(64, 64);
	// 半分のサイズ
	const def::Vector2 blockHalfSize = def::Vector2(32, 32);
};

#endif