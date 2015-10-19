#pragma once
#include "DataManager.h"
#include "Scene.h"
#include "def.h"

class Tutorial : public Scene
{
public:
	Tutorial(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer);
	
	void Initialize() override;
	void Update() override;
	void Draw() override;
};
