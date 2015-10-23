#pragma once

#include "def.h"
#include "Task.h"
#include "ISceneChanger.h"
#include "DataManager.h"
#include "GamePad.h"

class Scene : public Task
{
public:
	Scene(DataManager* _DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer);
	virtual ~Scene(){}
	virtual void Initialize() override{}
	virtual void Finalize() override;
	virtual void Update() override{}
	virtual void Draw() override;
protected:
	DataManager* m_pDataManager;
	Renderer* m_Renderer;
	GamePad* m_GamePad;
	int mImageHandle;	//‰æ‘œŠi”[—p•Ï”
	ISceneChanger* m_SceneChanger;
	bool end;
	bool side;

};