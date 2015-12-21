#pragma once
#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "GamePlayBundle.h"
#include "Renderer.h"
#include "View.h"
#include "GamePlayUI.h"

class TutoPlay : public Scene
{
public:
	TutoPlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer);
	~TutoPlay();

	void Initialize() override;
	void Update() override;
	void drawBack();
	void drawMain();
	void drawUI();
	void Pause();
	void PauseMenu();
	int GetViewSize;

private:
	MapData *m_pMapData;
	Camera *camera;
	CharacterManager* m_CharacterManager;
	GamePlayBundle* gamePlayBundle;
	GamePlayUI* m_GamePlayUI;
	View* m_View;

	bool pausecount;
};