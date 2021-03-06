#ifndef _MAPDATA_H
#define _MAPDATA_H

#include "def.h"
#include "gs.h"
#include "DataManager.h"

namespace Map
{
	const int width = 16;
	const int height = 16;
	const int chipSize = 64;
}

class MapData
{
public:
	MapData(DataManager *_DataManager);
	~MapData();
	void init();
	void update();
	void draw();
	bool isOutStage(const int x, const int y);
	bool isCollisionSide(D3DXVECTOR2 _position, float _sizeY);
	bool isCollisionUpDown(D3DXVECTOR2 _position, float _sizeX);
	bool isCollisionPoint(D3DXVECTOR2 _position);

private:
	DataManager *m_pDataManager;
	int MapNum;
	int Map_X;
	int Map_Y;
	int mapdata[Map::height][Map::width];
	char m_width[16][16];    //マップの縦タイル数
	int m_height;
};


#endif