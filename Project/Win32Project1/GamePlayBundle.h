#ifndef _GAMEPLAY_BUNDLE_
#define _GAMEPLAY_BUNDLE_

#include "Renderer.h"
#include "DataManager.h"
#include "Camera.h"
#include "MapData.h"
#include "GamePad.h"

class GamePlayBundle
{
public:
	GamePlayBundle(DataManager* _DataManager, Renderer* _Renderer, MapData* _MapData, Camera* _Camera, GamePad* _GamePad) :
		dataManager(_DataManager), renderer(_Renderer), mapData(_MapData), camera(_Camera), gamePad(_GamePad) {}
	DataManager* dataManager;
	Renderer* renderer;
	MapData* mapData;
	Camera* camera;
	GamePad* gamePad;
};

#endif