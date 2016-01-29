#ifndef _GAMEPLAY_BUNDLE_
#define _GAMEPLAY_BUNDLE_

#include "Renderer.h"
#include "DataManager.h"
#include "Camera.h"
#include "MapData.h"
#include "GamePad.h"
#include "SoundManager.h"
#include "IEffectMediator.h"

class ICharacterMediator;

class GamePlayBundle
{
public:
	GamePlayBundle(
		DataManager* _DataManager,
		SoundManager* _SoundManager,
		Renderer* _Renderer,
		MapData* _MapData,
		Camera* _Camera,
		GamePad* _GamePad,
		ICharacterMediator* _ICharacterMediator,
		IEffectMediator* _IEffectMediator) :
		dataManager(_DataManager),
		soundManager(_SoundManager),
		renderer(_Renderer),
		mapData(_MapData),
		camera(_Camera),
		gamePad(_GamePad),
		mediator(_ICharacterMediator),
		effect(_IEffectMediator){}
public:
	DataManager* dataManager;
	SoundManager* soundManager;
	Renderer* renderer;
	MapData* mapData;
	Camera* camera;
	GamePad* gamePad;
	ICharacterMediator* mediator;
	IEffectMediator* effect;
};

#endif