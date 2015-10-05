#ifndef _MOVEOBJECT_
#define _MOVEOBJECT_

#include "Character.h"

class MoveObject : public Character
{
public:
	MoveObject(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera *_camera);
	MoveObject(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera *_camera, def::Vector2 _position);
	MoveObject(GamePlayBundle* _GamePlayBundle);
	MoveObject(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	virtual ~MoveObject();
	virtual void draw() = 0;
protected:
	def::Vector2 moveValue;
	virtual void move() = 0;
	void moveUpdate();
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