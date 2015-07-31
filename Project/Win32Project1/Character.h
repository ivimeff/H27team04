#ifndef _CHARACTER_
#define _CHARACTER_

#include "gs.h"
#include "DataManager.h"
#include "MapData.h"

namespace PlayerSize
{
	// ���T�C�Y
	const float x = 64;
	// �c�T�C�Y
	const float y = 64;
	// ���T�C�Y�̔���
	const float hx = 32;
	// �c�T�C�Y�̔���
	const float hy = 32;
}

// �ʒu�������ۃN���X
class Character
{
public:
	Character(DataManager* _DataManager, MapData *_MapData);
	Character(DataManager* _DataManager, MapData *_MapData, D3DXVECTOR2 _position);
	virtual ~Character();
	virtual void init();
	virtual void update();
	virtual void draw();
protected:
	D3DXVECTOR2 position;
	DataManager* dataManager;
	MapData *mapData;
};

#endif