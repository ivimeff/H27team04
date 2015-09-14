#ifndef _CHARACTER_
#define _CHARACTER_

#include "gs.h"
#include "DataManager.h"
#include "MapData.h"
#include "Camera.h"

namespace PlayerSize
{
	// 横サイズ
	const float x = 32;
	// 縦サイズ
	const float y = 48;
	// 横サイズの半分
	const float hx = 16;
	// 縦サイズの半分
	const float hy = 24;
}

// 位置を持つ抽象クラス
class Character
{
public:
	Character(DataManager* _DataManager, MapData *_MapData, Camera *_camera);
	Character(DataManager* _DataManager, MapData *_MapData, Camera *_camera, D3DXVECTOR2 _position);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
	bool isDead();
	RECT getRect();
protected:
	D3DXVECTOR2 position;
	DataManager* dataManager;
	MapData *mapData;
	Camera *camera;
	bool deadFlg;
};

#endif