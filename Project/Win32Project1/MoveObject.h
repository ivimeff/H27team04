#ifndef _MOVEOBJECT_
#define _MOVEOBJECT_

#include "Character.h"

class MoveObject : public Character
{
public:
	//MoveObject(GamePlayBundle* _GamePlayBundle, def::CTag = def::C_NONE);
	MoveObject(GamePlayBundle* _GamePlayBundle, def::Vector2 _position,
		def::Vector2 _size = def::Vector2(64, 64), def::CTag = def::C_NONE);
	MoveObject(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::CTag _tag);
	virtual ~MoveObject();
	virtual void draw() = 0;
protected:
	def::Vector2 moveValue;
	virtual void move() = 0;
	void moveUpdate();
	virtual void onDent();
private:
	void moveReflect();
	void moveReflectSide();
	void moveReflectUpDown();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	bool moveRightOne();
	bool moveLeftOne();
	bool moveUpOne();
	bool moveDownOne();
};

#endif