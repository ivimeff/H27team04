#ifndef _GAMETITLE_H
#define _GAMETITLE_H

#include "DataManager.h"
#include "def.h"
#include "Scene.h"

class GameTitle : public Scene
{
public:
	GameTitle(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer);
	
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	int timer;
};

#endif
