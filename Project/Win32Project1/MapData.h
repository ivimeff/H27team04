#ifndef _MAPDATA_H
#define _MAPDATA_H

#include "def.h"
#include "DataManager.h"
#include "Camera.h"
#include <vector>
#include <array>

namespace Map
{
	// �}�b�v�̉��^�C����
	const int width = 16;
	// �}�b�v�̏c�^�C����
	const int height = 16;
	// �}�b�v�`�b�v��̃T�C�Y(�����`�Ƃ��Č��Ă���)
	const int chipSize = 64;
	// �}�b�v�S�̂̉��T�C�Y
	const int widthSize = width * chipSize;
	// �}�b�v�S�̂̏c�T�C�Y
	const int heightSize = height * chipSize;
	// �X�^�[�g�n�_�̕����ԍ�
	const int startMap = 7;
	// ��̃}�b�v���i�[����Œ蒷�z��
	typedef std::array<std::array<int, Map::height>, Map::width> Map_t;
}

class MapData
{
public:
	MapData(DataManager *_DataManager, Renderer *_Renderer, Camera *_camera);
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
	void setMapIndex();
	bool isCheckIndex(int _index);
	DataManager *m_pDataManager;
	Renderer *m_Renderer;
	Camera *camera;
	int MapNum, mMaxMapNum;

	std::vector<std::string> mapNames;
	std::vector<Map::Map_t> mapdata;
	std::vector<Map::Map_t> objdata;
	Map::Map_t currentMap;
	Map::Map_t currentObj;
};


#endif