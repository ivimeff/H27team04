#pragma once
#include "DataManager.h"
#include "MapData.h"
#include "Scene.h"
#include "CharacterManager.h"
#include "Camera.h"
#include "GamePlayBundle.h"
#include "Renderer.h"
#include "View.h"
#include "GamePlayUI.h"
#include "EffectManager.h"

class GamePlay : public Scene
{
public:
	GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound);
	~GamePlay();

	void Initialize() override;
	void Update() override;
	void drawBack();
	void drawMain();
	void drawUI();
	//void Draw()override;
	void Pause();
	void PauseMenu();
	int GetViewSize;
private:
	MapData *m_pMapData;
	Camera *camera;
	CharacterManager* m_CharacterManager;
	EffectManager* m_EffectManager;
	GamePlayBundle* gamePlayBundle;
	GamePlayUI*m_GamePlayUI;
	int mlist;
	View*m_View;

	bool pausecount;
};
