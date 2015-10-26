#ifndef _CHARACTER_
#define _CHARACTER_

#include "DataManager.h"
#include "MapData.h"
#include "Camera.h"
#include "Renderer.h"
#include "GamePlayBundle.h"
#include "GamePad.h"

// ˆÊ’u‚ğ‚Â’ŠÛƒNƒ‰ƒX
class Character
{
public:
	Character(const Character&);
	Character(GamePlayBundle* _GamePlayBundle);
	Character(GamePlayBundle* _GamePlayBundle, def::Vector2 _position);
	Character(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera);
	Character(DataManager* _DataManager, Renderer* _Renderer, MapData *_MapData, Camera *_camera, def::Vector2 _position);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void hited(Character* _target);
	void setPosition(def::Vector2 _position);
	bool isDead();
	def::Rect getRect();
	Character operator = (Character);
protected:
	def::Vector2 position;
	def::Vector2 size, halfSize;
	DataManager* dataManager;
	MapData *mapData;
	Camera *camera;
	Renderer *renderer;
	GamePad* gamePad;
	bool deadFlg;
};

#endif