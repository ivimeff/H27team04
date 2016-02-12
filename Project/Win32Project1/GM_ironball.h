#pragma once

#include "MoveObject.h"
#include "CharacterManager.h"

class GM_ironball : public MoveObject 
{
public:
	//GM_ironball(GamePlayBundle* _GamePlayBundle);
	GM_ironball(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _dir);
	~GM_ironball();

	void init();
	void update();
	void draw();

	void hited(Character* _target);
	bool isSpiritual();

private:
	bool hit;
	void move();
	void onDent();
	int animation, time,speed;
	const int startSpeed = 2, spSpeed = 3;
	float x, y;
	def::Vector2 sepos, direction;
};