#pragma once
#include <map>
#include "Scene.h"
#include "DataManager.h"
#include "def.h"
#include "MapData.h"
#include "GamePad.h"
#include "ISceneChanger.h"

class SceneManager : public ISceneChanger, Task
{
public:
	SceneManager(Renderer* _renderer);
	~SceneManager();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ChangeScene(eScene NextScene)override;

private:
	std::map<eScene, Scene*> scenes;
	int fadeTime, fadeCount;
	const int maxFadeTime = 60;
	Renderer* m_Renderer;
	DataManager *m_pDataManager;
	GamePad* m_GamePad;
	Scene* mScene;	//�V�[���Ǘ��ϐ�
	eScene mNextScene;//���̃V�[���Ǘ��ϐ�
	bool fadeUpdate();
};
