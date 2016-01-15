#pragma once

#include "DataManager.h"
#include "Scene.h"
#include "def.h"

class GameClear : public Scene
{
public:
	GameClear(DataManager* _DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Chager, SoundManager* _Sound);

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	int timer;

};