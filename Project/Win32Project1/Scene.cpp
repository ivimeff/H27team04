#include "Scene.h"
#include "DxLib.h"

Scene::Scene(DataManager* _dataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer) :
m_pDataManager(_dataManager), m_Renderer(_Renderer), m_GamePad(_GamePad), mImageHandle(0)
{
	end = false;
	m_SceneChanger = _Changer;
}

void Scene::Finalize(){
	DeleteGraph(mImageHandle);
}

void Scene::Draw(){
	m_Renderer->setLayer(def::L_BACK);
	drawBack();
	m_Renderer->setLayer(def::L_MAIN);
	drawMain();
	m_Renderer->setLayer(def::L_UI);
	drawUI();
	DrawGraph(0, 0, mImageHandle, FALSE);
}

void Scene::drawBack()
{

}

void Scene::drawMain()
{

}

void Scene::drawUI()
{

}
