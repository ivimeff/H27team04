#pragma once

#include "MoveObject.h"

class GM_ironball : public MoveObject
{
public:
	GM_ironball(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera);
	GM_ironball(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position);
	GM_ironball(GamePlayBundle* _GamePlayBundle);
	GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	~GM_ironball();

	void init();
	void update();
	void draw();

private:

	void move();
	int animation, time;
};