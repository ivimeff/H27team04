#pragma once

#include "def.h"
#include "Task.h"
#include "ISceneChanger.h"
#include "DataManager.h"
#include "GamePad.h"
#include"SoundManager.h"
class Scene : public Task
{
public:
	Scene(DataManager* _DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound);
	virtual ~Scene(){}
	virtual void Initialize() override{}
	virtual void Finalize() override;
	virtual void Update() override{}
	// Scene派生クラスからDrawメソッドを消して
	// 代わりにdrawBack, drawMain, drawUIを実装することでレイヤー分けが可能
	virtual void Draw() override;
protected:
	DataManager* m_pDataManager;
	Renderer* m_Renderer;
	SoundManager* m_pSound;
	GamePad* m_GamePad;
	int mImageHandle;	//画像格納用変数
	ISceneChanger* m_SceneChanger;
	bool end;
	bool side;
	// 一番下のレイヤー
	virtual void drawBack();
	// 中間のレイヤー
	virtual void drawMain();
	// 一番上のレイヤー
	virtual void drawUI();
};