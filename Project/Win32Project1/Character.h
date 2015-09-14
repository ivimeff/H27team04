#ifndef _CHARACTER_
#define _CHARACTER_

#include "gs.h"
#include "DataManager.h"
#include "MapData.h"
#include "Camera.h"

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

// �ʒu�������ۃN���X
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