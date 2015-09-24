#ifndef _MAPDATA_H
#define _MAPDATA_H

#include "def.h"
#include "gs.h"
#include "DataManager.h"
#include "Camera.h"
#include <vector>
#include <array>

namespace Map
{
	const int width = 16;
	const int height = 16;
	const int chipSize = 64;
	const int widthSize = width * chipSize;
	const int heightSize = height * chipSize;

	typedef std::array<std::array<int, Map::height>, Map::width> Map_t;
}

class MapData
{
public:
	MapData(DataManager *_DataManager, Camera *_camera);
	~MapData();
	void init();
	void update();
	void draw();
	bool isOutStage(const int x, const int y);
	bool isCollisionSide(D3DXVECTOR2 _position, float _sizeY);
	bool isCollisionUpDown(D3DXVECTOR2 _position, float _sizeX);
	bool isCollisionPoint(D3DXVECTOR2 _position);

private:
	void load(const char* _fileName);
	DataManager *m_pDataManager;
	Camera *camera;
	int MapNum;
	int Map_X;
	int Map_Y;
	std::vector<Map::Map_t> mapdata;
	std::vector<Map::Map_t> objdata;
	Map::Map_t currentMap;
	//char m_width[16][16];    //マップの縦タイル数
	//int m_height;
};


#endif