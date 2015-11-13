#ifndef _CHARACTER_
#define _CHARACTER_

#include "DataManager.h"
#include "MapData.h"
#include "Camera.h"
#include "Renderer.h"
#include "GamePlayBundle.h"
#include "GamePad.h"

namespace def
{
	enum CTag
	{
		C_NONE,
		C_PLAYER,
		C_ENEMY,
		C_PASS_UP,
		C_PASS_DOWN,
	};
}

// ˆÊ’u‚ğ‚Â’ŠÛƒNƒ‰ƒX
class Character
{
public:
	Character(GamePlayBundle* _GamePlayBundle, def::CTag = def::C_NONE);
	Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::CTag = def::C_NONE);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void hited(Character* _target);
	void setPosition(def::Vector2 _position);
	bool isDead();
	def::Rect getRect();
	def::CTag getTag();
protected:
	def::Vector2 position;
	def::Vector2 size, halfSize;
	def::Vector2 spsize, sphalfSize;
	DataManager* dataManager;
	MapData *mapData;
	Camera *camera;
	Renderer *renderer;
	GamePad* gamePad;
	bool deadFlg;
	def::CTag tag;
};

#endif