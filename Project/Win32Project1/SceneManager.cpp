#include "SceneManager.h"
#include "DxLib.h"
#include "Tutorial.h"
#include "GamePlay.h"
#include "GameMenu.h"
#include "GameOver.h"
#include "GameTitle.h"

SceneManager::SceneManager(Renderer* _renderer) :
mNextScene(eScene_None), m_Renderer(_renderer)
{
	m_pDataManager = new DataManager(m_Renderer);
	m_GamePad = new GamePad();
	//�ŏ��̃V�[��
	mScene = (Scene*) new GameTitle(m_pDataManager,m_Renderer,m_GamePad,this);
	fadeCount = 255;
	if (!m_pDataManager->load()) return;
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
	// ��������R�����g�A�E�g����΃V�[���ڍs���Ƀt�F�[�h�C���t�F�[�h�A�E�g���Ȃ��Ȃ�
	if (!fadeUpdate()) return;
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

bool SceneManager::fadeUpdate()
{
	//if (mNextScene != eScene::eScene_None)
	//{
	//	if (++fadeTime <= maxFadeTime)
	//	{
	//		fadeCount += 255 / maxFadeTime;
	//		m_Renderer->setDrawBright(fadeCount, fadeCount, fadeCount);
	//		return false;
	//	}
	//	else
	//	{
	//		fadeTime = fadeCount = 0;
	//		m_Renderer->setDrawBright(255, 255, 255);
	//		return true;
	//	}
	//}
	//else
	//{
	//	if (++fadeTime < maxFadeTime)
	//	{
	//		fadeCount += 255 / maxFadeTime;
	//		m_Renderer->setDrawBright(255 - fadeCount, 255 - fadeCount, 255 - fadeCount);
	//		return false;
	//	}
	//	else
	//	{
	//		fadeTime = fadeCount = 0;
	//		m_Renderer->setDrawBright(0, 0, 0);
	//		return true;
	//	}
	//}

	// ���邢��Ԃł����̃V�[���ֈڍs���Ȃ���Ή��̏������s��Ȃ�
	if (fadeCount >= 255 && mNextScene == eScene::eScene_None) return true;
	int fadeState;
	// 1�͎���ɈÂ��A-1�͖��邭���Ă���
	fadeState = (mNextScene == eScene::eScene_None) ? 1 : -1;
	if (++fadeTime < maxFadeTime)
	{
		// �I���܂ł̎��Ԃ��畽�ς��ăt�F�[�h������
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