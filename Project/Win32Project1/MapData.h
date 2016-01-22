#ifndef _MAPDATA_H
#define _MAPDATA_H

#include "def.h"
#include "DataManager.h"
#include "Camera.h"
#include <vector>
#include <array>

class SceneManager;

namespace Map
{
	// マップの横タイル数
	const int width = 16;
	// マップの縦タイル数
	const int height = 16;
	// マップチップ一つのサイズ(正方形として見ている)
	const int chipSize = 64;
	// マップ全体の横サイズ
	const int widthSize = width * chipSize;
	// マップ全体の縦サイズ
	const int heightSize = height * chipSize;
	// スタート地点の部屋番号
	const int startMap = 7;
	// 一つのマップを格納する固定長配列
	typedef std::array<std::array<int, Map::height>, Map::width> Map_t;
}

class MapData
{
public:
	MapData(DataManager *_DataManager, Renderer *_Renderer, Camera *_camera,int mlist);
	~MapData();
	void init();
	void update();
	void draw();
	bool isOutStage(const int x, const int y);
	bool isCollisionSide(def::Vector2 _position, float _sizeY);
	bool isCollisionUpDown(def::Vector2 _position, float _sizeX);
	bool isCollisionPoint(def::Vector2 _position);
	int getObj(int x, int y);
	int getLayer(int y);
	void changeMap(int _moveIndex);
private:
	void load(const char* _fileName);
	void drawOne(int x, int y, def::Vector2 cPos);
	void setMapIndex(int s = 0);
	void drawMapFirst();
	bool isCheckIndex(int _index);
	DataManager *m_pDataManager;
	Renderer *m_Renderer;
	Camera *camera;
	int MapNum, mMaxMapNum;
	bool startFlg;
	std::vector<std::string> mapNames;
	std::vector<Map::Map_t> mapdata;
	std::vector<Map::Map_t> objdata;
	Map::Map_t currentMap;
	Map::Map_t currentObj;
};


#endif