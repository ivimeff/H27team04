#pragma once
#include "DataManager.h"
#include "Scene.h"
#include "def.h"

class Tutorial2 :public Scene
{
public:
	Tutorial2(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer);

	void Initialize() override;
	void Update() override;
	void Draw() override;
};