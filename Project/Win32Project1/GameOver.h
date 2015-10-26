#pragma once

#include "DataManager.h"
#include "Scene.h"
#include "def.h"

class GameOver : public Scene
{
public:
	GameOver(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer);

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	int timer;
};
