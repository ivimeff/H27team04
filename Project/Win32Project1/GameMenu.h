#pragma once
#include "DataManager.h"
#include "def.h"
#include "Scene.h"

class GameMenu : public Scene
{
public:
	GameMenu(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer);
	
	void Initialize() override;
	void Update() override;
	void Draw() override;
};