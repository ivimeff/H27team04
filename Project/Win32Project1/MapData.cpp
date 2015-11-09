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

	
	//reinterpret_cast

}

MapData::~MapData()
{
}

void MapData::init()
{

	load("stage/stage1.bin");
	load("stage/stage2.bin");

	MapNum = 0;

	currentMap = mapdata[0];
	currentObj = objdata[0];

}

void MapData::update()
{
	
}

void MapData::draw()
{
	def::Vector2 cPos = camera->getPosition();

	int firstTileX = cPos.x / Map::chipSize;
	int lastTileX = firstTileX + (window::width / Map::chipSize) + 1;
	lastTileX = min(lastTileX, Map::width);

	int firstTileY = cPos.y / Map::chipSize;
	int lastTileY = firstTileY + (window::height / Map::chipSize) + 2;
	lastTileY = min(lastTileY, Map::height);
	int i = lastTileY - firstTileY;
	for (int Map_Y = firstTileY; Map_Y < lastTileY; ++Map_Y)
	{
		for (int Map_X = firstTileX; Map_X < lastTileX; ++Map_X)
		{
			const int x = Map_X * Map::chipSize - cPos.x,
				y = Map_Y * Map::chipSize - cPos.y;
			switch (currentMap[Map_Y][Map_X])
			{
			case 0:
				m_Renderer->drawTexture(m_pDataManager->floor, x, y);
				break;

			case 1:
				m_Renderer->drawTexture(m_pDataManager->wall, x, y);
				break;

			default:
				break;
			}
#ifdef _DEBUG
			m_Renderer->drawRect(x, y, x + Map::chipSize, y + Map::chipSize, 0xffffffff);
			std::ostringstream ostr;
			ostr << currentMap[Map_Y][Map_X];
			m_Renderer->drawString(ostr.str().c_str(), x + 2, y);
			ostr = std::ostringstream();
			ostr << currentObj[Map_Y][Map_X];
			m_Renderer->drawString(ostr.str().c_str(), x + 2, y + 16);
#endif
		}
		--i;
	}
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
}

bool MapData::isCheckIndex(int _index)
{
	return !(_index < 0 || _index >= mapdata.size());
}