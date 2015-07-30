#ifndef _CHARACTER_
#define _CHARACTER_

#include "gs.h"
#include "DataManager.h"
#include "MapData.h"

namespace PlayerSize
{
	// 横サイズ
	const float x = 64;
	// 縦サイズ
	const float y = 64;
	// 横サイズの半分
	const float hx = 32;
	// 縦サイズの半分
	const float hy = 32;
}

// 位置を持つ抽象クラス
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