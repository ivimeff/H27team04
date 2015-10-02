#include "Scene.h"

Scene::Scene(DataManager* _dataManager, Renderer* _Renderer, GamePad* _GamePad) :
m_pDataManager(_dataManager), m_Renderer(_Renderer), m_GamePad(_GamePad)
{
	end = false;
}

Scene::~Scene() {}

void Scene::init()
{

}

bool Scene::isEnd()
{
	return end;
}

bool Scene::isMenu()	//チュートリアルとかのシーンの分岐に使うやつ
{
	return side;
}