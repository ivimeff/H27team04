#pragma once
#include "DataManager.h"
#include "Scene.h"
#include "def.h"

class Tutorial3 :public Scene
{
public:
	Tutorial3(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound);

	void Initialize() override;
	void Update() override;
	void Draw() override;
};