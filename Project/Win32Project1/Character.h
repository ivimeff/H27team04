#ifndef _CHARACTER_
#define _CHARACTER_

#include "gs.h"
#include "DataManager.h"
#include "MapData.h"
#include "Camera.h"

// ˆÊ’u‚ğ‚Â’ŠÛƒNƒ‰ƒX
class Character
{
public:
	Character(const Character&);
	Character(DataManager* _DataManager, MapData *_MapData, Camera *_camera);
	Character(DataManager* _DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
	void setPosition(D3DXVECTOR2 _position);
	bool isDead();
	bool isCollision(RECT target);
	RECT getRect();
	Character operator = (Character);
protected:
	D3DXVECTOR2 position;
	gsVec2 size, halfSize;
	DataManager* dataManager;
	MapData *mapData;
	Camera *camera;
	bool deadFlg;
};

#endif