#include "MapData.h"
#include<fstream>
#include <iostream>
#include <sstream>
#include<string>
#include<stdio.h>
#include <math.h>
#include <DxLib.h>

using namespace std;

MapData::MapData(DataManager *_DataManager, Renderer* _Renderer, Camera *_camera)
{
	m_pDataManager = _DataManager;
	camera = _camera;
	m_Renderer = _Renderer;
	setMapIndex();
	
	//reinterpret_cast

}

MapData::~MapData()
{
}

void MapData::init()
{
	for (std::string fileName : mapNames)
	{
		load(fileName.c_str());
	}
	MapNum = Map::startMap < mapdata.size() ? Map::startMap : 0;

	currentMap = mapdata[MapNum];
	currentObj = objdata[MapNum];
	drawMapFirst();

}

void MapData::update()
{
	
}

// 毎回描画する方
void MapData::draw()
{
	def::Vector2 cPos = camera->getPosition();

	int firstTileY = cPos.y / Map::chipSize;
	int lastTileY = firstTileY + (window::height / Map::chipSize) + 2;
	lastTileY = min(lastTileY, Map::height);
	for (int Map_Y = firstTileY; Map_Y < lastTileY; ++Map_Y)
	{
		m_Renderer->setMapPos(Map_Y,
			def::Vector2(0, Map_Y * Map::chipSize) - cPos);
	}
}

// 部屋を移動したときに一度だけ描画する方
void MapData::drawMapFirst()
{
	m_Renderer->clearMapLayer();
	def::Vector2 cPos = camera->getPosition();

	for (int Map_Y = 0, size = currentMap.size(); Map_Y < size; ++Map_Y)
	{
		m_Renderer->setMapLayer(Map_Y);
		for (int Map_X = 0, size = currentMap[Map_Y].size(); Map_X < size; ++Map_X)
		{
			drawOne(Map_X, Map_Y, cPos);
		}
	}
	m_Renderer->setLayer(def::L_BACK);
}

// マップチップ一枚分描画する
void MapData::drawOne(int x, int y, def::Vector2 cPos)
{
	const int dx = x * Map::chipSize - cPos.x;
	switch (currentMap[y][x])
	{
	case 0:
		m_Renderer->drawTexture(m_pDataManager->floor, dx, 0);
		break;

	case 1:
		//m_Renderer->drawTextureEx(m_pDataManager->wall, dx, dy - Map::chipSize / 2, dx + Map::chipSize, dy + Map::chipSize);
		m_Renderer->drawTexture(m_pDataManager->wall, dx, 0);
		break;

	default:
		break;
	}
#ifdef _DEBUG
	m_Renderer->drawRect(dx, 0, dx + Map::chipSize, Map::chipSize, 0xffffffff);
	std::ostringstream ostr;
	ostr << currentMap[y][x];
	m_Renderer->drawString(ostr.str().c_str(), dx + 2, 0);
	ostr = std::ostringstream();
	ostr << currentObj[y][x];
	m_Renderer->drawString(ostr.str().c_str(), dx + 2, 16);
#endif
}

void MapData::load(const char* _fileName)
{

	ifstream bin(_fileName, ios::in | ios::binary);
	if (!bin)
	{
		//MessageBox(NULL, "ファイルオープン失敗\n終了します", "Error", MB_OK);
		//PostQuitMessage(0);
		return;
	}

	int width = 0, height = 0;
	Map::Map_t map, obj;

	// ファイルのデータはC#のbyte(C++では unsigned char)型で出力されている
	bin.read((char*)&width, sizeof(char));
	bin.read((char*)&height, sizeof(char));

	width = width > Map::width ? Map::width : width;
	height = height > Map::height ? Map::height : height;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int a = 0, b = 0;
			bin.read((char*)&a, sizeof(char));
			bin.read((char*)&b, sizeof(char));
			map[y][x] = b;
			obj[y][x] = a;
		}
	}

	bin.close();

	mapdata.push_back(map);
	objdata.push_back(obj);

}

int MapData::getObj(const int x, const int y)
{
	if (isOutStage(x, y)) return 0;
	return currentObj[y][x];
}

int MapData::getLayer(const int y)
{
	if (y < 0 || y >= Map::heightSize) return 0;
	return y / Map::chipSize;
}

bool MapData::isOutStage(const int x, const int y)
{
	return (x < 0 || x >= Map::width || y < 0 || y >= Map::height);
}

bool MapData::isCollisionPoint(def::Vector2 _position)
{
	// マイナス座標にに行ったら-1だけずらす
	const int x = (int)(_position.x >= 0 ? _position.x / Map::chipSize : (_position.x / Map::chipSize) - 1);
	const int y = (int)(_position.y >= 0 ? _position.y / Map::chipSize : (_position.y / Map::chipSize) - 1);
	return isOutStage(x, y) ? true : currentMap[y][x] == 1;
}

bool MapData::isCollisionSide(def::Vector2 _position, float _sizeY)
{
	def::Vector2 characterPosition = _position;
	characterPosition.y++;
	for (int y = 0; y < _sizeY / 2; ++y)
	{
		if (isCollisionPoint(characterPosition)) return true;
		characterPosition.y += 2;
	}
	return false;
}

bool MapData::isCollisionUpDown(def::Vector2 _position, float _sizeX)
{
	def::Vector2 characterPosition = _position;
	characterPosition.x++;
	for (int x = 0; x < _sizeX / 2; ++x)
	{
		if (isCollisionPoint(characterPosition)) return true;
		characterPosition.x += 2;
	}
	return false;
}

void MapData::changeMap(int _moveIndex)
{
	if (!isCheckIndex(_moveIndex + MapNum)) return;
	MapNum += _moveIndex;
	currentMap = mapdata[MapNum];
	currentObj = objdata[MapNum];
	drawMapFirst();
}

bool MapData::isCheckIndex(int _index)
{
	return !(_index < 0 || _index >= mapdata.size());
}

void MapData::setMapIndex()
{
	// ☆現在テスト用のマップを使用中

	std::ifstream ifs("stage/MapList.txt");
	//std::ifstream ifs("stage/d_MapList.txt");
	mMaxMapNum = 0;
	std::string str;
	if (ifs.fail())
	{
		return;
	}
	while (std::getline(ifs, str))
	{
		mapNames.push_back(str);
		++mMaxMapNum;
	}
}