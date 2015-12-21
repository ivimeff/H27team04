#include "SceneManager.h"
#include "DxLib.h"
#include "Tutorial.h"
#include "Tutorial2.h"
#include "Tutorial3.h"
#include "TutoPlay.h"
#include "GamePlay.h"
#include "GameMenu.h"
#include "GameOver.h"
#include "GameTitle.h"

SceneManager::SceneManager(Renderer* _renderer, SoundManager* _sound) :
mNextScene(eScene_None), m_Renderer(_renderer), m_Sound(_sound)
{
	m_pDataManager = new DataManager(m_Renderer);
	m_GamePad = new GamePad();
	//最初のシーン
	mScene = (Scene*) new GameTitle(m_pDataManager,m_Renderer,m_GamePad,this);
	fadeCount = 255;
	if (!m_pDataManager->load()) return;
	m_Sound->load("Sound/soundList.csv");
	m_Sound->playBGM("TitleBGM");
}

SceneManager::~SceneManager()
{
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
#ifndef _DEBUG
	if (!fadeUpdate()) return;
#endif
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
		case eScene_Tutorial2:
			mScene = (Scene*) new Tutorial2(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_Tutorial3:
			mScene = (Scene*) new Tutorial3(m_pDataManager, m_Renderer, m_GamePad, this);
			break;
		case eScene_TutoPlay:
			mScene = (Scene*) new TutoPlay(m_pDataManager, m_Renderer, m_GamePad, this);
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

bool SceneManager::fadeUpdate()
{
	// 明るい状態でかつ次のシーンへ移行しなければ下の処理を行わない
	if (fadeCount >= 255 && mNextScene == eScene::eScene_None) return true;
	int fadeState;
	// 1は次第に暗く、-1は明るくしていく
	fadeState = (mNextScene == eScene::eScene_None) ? 1 : -1;
	if (++fadeTime < maxFadeTime)
	{
		// 終わりまでの時間から平均してフェードさせる
		fadeCount += 255 / maxFadeTime * fadeState;
		m_Renderer->setDrawBright(fadeCount, fadeCount, fadeCount);
		return false;
	}
	else
	{
		fadeTime = 0;
		fadeCount = fadeState > 0 ? 255 : 0;
		m_Renderer->setDrawBright(fadeCount, fadeCount, fadeCount);
		return true;
	}
	return true;
}