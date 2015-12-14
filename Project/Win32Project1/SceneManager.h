#pragma once
#include <map>
#include "Scene.h"
#include "DataManager.h"
#include "def.h"
#include "MapData.h"
#include "GamePad.h"
#include "ISceneChanger.h"
#include "SoundManager.h"

class SceneManager : public ISceneChanger, Task
{
public:
	SceneManager(Renderer* _renderer, SoundManager* _sound);
	~SceneManager();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ChangeScene(eScene NextScene)override;

private:
	std::map<eScene, Scene*> scenes;
	int fadeTime, fadeCount;
	const int maxFadeTime = 30;
	Renderer* m_Renderer;
	SoundManager* m_Sound;
	DataManager *m_pDataManager;
	GamePad* m_GamePad;
	Scene* mScene;	//シーン管理変数
	eScene mNextScene;//次のシーン管理変数
	bool fadeUpdate();
};
