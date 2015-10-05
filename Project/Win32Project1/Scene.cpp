#include "Scene.h"

Scene::Scene(DataManager* _dataManager) : m_pDataManager(_dataManager)
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