#pragma once

typedef enum{
	eScene_Title,
	eScene_Menu,
	eScene_GamePlay,
	eScene_Tutorial,
	eScene_Tutorial2,
	eScene_Tutorial3,
	eScene_TutoPlay,
	eScene_GameOver,

	eScene_None,
}eScene;

//シーンを変更するためのインターフェイス
class ISceneChanger{
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;
};
