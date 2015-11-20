#pragma once
#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "Camera.h"
#include "GamePlayBundle.h"
#include "Renderer.h"

class GamePlay : public Scene
{
public:
	GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer);
	~GamePlay();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Pause();
	void PauseMenu();
private:
	MapData *m_pMapData;
	Camera *camera;
	CharacterManager* m_CharacterManager;
	GamePlayBundle* gamePlayBundle;


	bool pausecount;
};
