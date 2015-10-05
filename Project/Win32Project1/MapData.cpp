#include "MapData.h"
#include<fstream>
#include <iostream>
#include <sstream>
#include<string>
#include<stdio.h>

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

	//ifstream bin("stage0.bin", ios::in | ios::binary);
	//if (!bin)
	//{
	//	MessageBox(NULL, "ファイルオープン失敗\n終了します", "Error", MB_OK);
	//	PostQuitMessage(0);
	//}
	////bin.seekg(2 * sizeof(char));
	////讓ｪ繧ｿ繧､繝ｫ謨ｰ蜿門ｾ・
	//bin.read((char*)(&m_width), sizeof(m_width));
	//
	//bin.close();
	//
	//int bin2[Map::height][Map::width];
	////bin2[0][0] = atoi(&m_width[0][1]);
	////m_width[1][1] = bin2[1][1];
	////MapNum = 0;
	//
	//
	//for (int Map_Y = 0; Map_Y < Map::height; Map_Y++)
	//{
	//	for (int Map_X = 0; Map_X < Map::width; Map_X++)
	//	{
	//		bin2[Map_Y][Map_X] = (int)m_width[Map_Y][Map_X];
	//	}
	//}
	//
	//int mapdata2[Map::height][Map::width];
	//
	//{
	//	{
	//		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	//	},
	//	{
	//		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	//		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	//	},
	//};
	////for (int MapNum = 0; MapNum < 2; MapNum++)
	//
	//for (int Map_Y = 0; Map_Y < 10; Map_Y++)
	//{
	//	for (int Map_X = 0; Map_X < 10; Map_X++)
	//	{
	//		mapdata[MapNum][Map_Y][Map_X] = mapdata2[MapNum][Map_Y][Map_X];
	//	}
	//}
	//
	//for (int Map_Y = 0; Map_Y < Map::height; Map_Y++)
	//{
	//	for (int Map_X = 0; Map_X < Map::width; Map_X++)
	//	{
	//		mapdata2[Map_Y][Map_X] = bin2[Map_Y][Map_X];
	//	}
	//}
	//
	//for (int Map_Y = 0; Map_Y < Map::height; Map_Y++)
	//{
	//	for (int Map_X = 0; Map_X < Map::width; Map_X++)
	//	{
	//		mapdata[Map_Y][Map_X] = mapdata2[Map_Y][Map_X];
	//}
	//}
	//

	currentMap = mapdata[0];
	currentObj = objdata[0];

}

void MapData::update()
{
	
}

void MapData::draw()
{
	/*
	for (int Map_Y = 0; Map_Y < 10; Map_Y++)
	{
		for (int Map_X = 0; Map_X < 10; Map_X++)
		{
			switch (mapdata[MapNum][Map_Y][Map_X])
			{
			case 0:
				gsDraw2D(m_pDataManager->green, Map_X * 64, Map_Y * 64);
				break;

			case 1:
				gsDraw2D(m_pDataManager->blue, Map_X * 64, Map_Y * 64);
				break;

			default:
				break;
			}
		}
	}	
	*/
	for (int Map_Y = 0; Map_Y < Map::height; Map_Y++)
	{
		for (int Map_X = 0; Map_X < Map::width; Map_X++)
		{
			const int x = Map_X * Map::chipSize - camera->getPosition().x,
				y = Map_Y * Map::chipSize - camera->getPosition().y;
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
			ostr.clear();
			ostr << currentObj[Map_Y][Map_X];
			m_Renderer->drawString(ostr.str().c_str(), x + 2, y + 16);
#endif
		}
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
	for (int y = 0; y < 6; y++)
	{
		if (isCollisionPoint(characterPosition)) return true;
		characterPosition.y += (_sizeY - 2) / 6;
	}
	return false;
}

bool MapData::isCollisionUpDown(def::Vector2 _position, float _sizeX)
{
	def::Vector2 characterPosition = _position;
	characterPosition.x++;
	for (int x = 0; x < 6; ++x)
	{
		if (isCollisionPoint(characterPosition)) return true;
		characterPosition.x += (_sizeX - 2) / 6;
	}
	return false;
}
