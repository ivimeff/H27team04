#include "SceneManager.h"
#include "DxLib.h"
#include "Tutorial.h"
#include "GamePlay.h"
#include "GameMenu.h"
#include "GameOver.h"
#include "GameTitle.h"

SceneManager::SceneManager() :
	mNextScene(eScene_None)
{
	m_Renderer = new Renderer();
	m_pDataManager = new DataManager(m_Renderer);
	m_GamePad = new GamePad();
	//Å‰‚ÌƒV[ƒ“
	mScene = (Scene*) new GameTitle(m_pDataManager,m_Renderer,m_GamePad,this);
	if (!m_pDataManager->load()) return;
}

SceneManager::~SceneManager()
{
	delete m_Renderer;
	delete m_pDataManager;
	delete m_GamePad;
	delete mScene;
}

void SceneManager::Initialize()
{
	m_GamePad->init();
	mScene->Initialize();

}

void SceneManager::Finalize(){
	mScene->Finalize();
}

void SceneManager::Update()
{
	if (mNextScene != eScene_None){
		mScene->Finalize();
		delete mScene;
		
		switch (mNextScene){
		case eScene_Title:
			mScene = (Scene*) new GameTitle(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_Menu:
			mScene = (Scene*) new GameMenu(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_Tutorial:
			mScene = (Scene*) new Tutorial(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_GamePlay:
			mScene = (Scene*) new GamePlay(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_GameOver:
			mScene = (Scene*) new GameOver(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		}
		mNextScene = eScene_None;
		mScene->Initialize();
	}
	mScene->Update();
	m_GamePad->update();
}

void SceneManager::Draw()
{
	mScene->Draw();
}

void SceneManager::ChangeScene(eScene NextScene){
	mNextScene = NextScene;
}