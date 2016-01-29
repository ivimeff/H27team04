#include "TutoPlay.h"
//#include <stdio.h>
//#include <time.h>
//#include "Player.h"
#include "Block.h"
#include "Enemy2.h"
#include <DxLib.h>
//#include <sstream>
#include "Keyboard.h"
#include "DataManager.h"

typedef enum{
	pMenu_title,
	pMenu_end,
	pMenu_play,

	eMenu_Num,
}pMenu;

static int NowSelect = pMenu_play;

TutoPlay::TutoPlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Change, SoundManager* _Sound) : 
Scene(_DataManager, _Renderer, _GamePad, _Change, _Sound)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, _Renderer, camera,mlist);
	m_EffectManager = new EffectManager();
	gamePlayBundle = new GamePlayBundle(_DataManager, _Sound, m_Renderer, m_pMapData, camera, _GamePad, nullptr, (IEffectMediator*)m_EffectManager);
	m_CharacterManager = new CharacterManager(gamePlayBundle);
	//m_CharacterManager->GenericControll<Character>::addObj(new Block(gamePlayBundle, def::Vector2(350, 735)));
	//m_CharacterManager->GenericControll<Character>::addObj(new Enemy2(gamePlayBundle, def::Vector2(350, 335)));
	//gamePlayBundle->mediator = (ICharacterMediator*)m_CharacterManager;
	m_GamePlayUI = new GamePlayUI(_Renderer,_GamePad);
	m_View = new View(_DataManager,_GamePad);
}

TutoPlay::~TutoPlay()
{
	delete camera;
	delete m_pMapData;
	delete m_EffectManager;
	delete gamePlayBundle;
	delete m_CharacterManager;
	delete m_GamePlayUI;
	delete m_View;
}

void TutoPlay::Initialize()
{
	end = false;
	m_pMapData->init();
	m_CharacterManager->init();
	m_EffectManager->init();
	//m_CharacterManager->GenericControll<Character>::addObj(new Player(gamePlayBundle, def::Vector2(200, 200)));
	//m_CharacterManager->GenericControll<Character>::addObj(new Block(gamePlayBundle, def::Vector2(400, 400)));
	pausecount = false;
	m_GamePlayUI->init();
	m_View->init();
}

void TutoPlay::Update()
{
	Pause();
	if (pausecount == 1)
	{
		PauseMenu();
	}
	else if (pausecount == 0)
	{
		m_pMapData->update();
		m_CharacterManager->update();
		m_EffectManager->update();
		if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
		{
			end = true;
		}

		if (CheckHitKey(KEY_INPUT_SPACE) != 0){	//スペースが押されたら
			m_SceneChanger->ChangeScene(eScene_Menu);//ゲームオーバーに変更
		}

		if (m_CharacterManager->isGoal())
		{
			m_SceneChanger->ChangeScene(eScene_Menu);
			return;
		}
	}
	m_GamePlayUI->updata();
	m_View->updata();
	m_View->SetPosition(m_CharacterManager->GetPlayerPosition());

	GetViewSize = m_View->Energie;
	m_GamePlayUI->SetViewSize(GetViewSize);
}

void TutoPlay::drawBack()
{
	m_pMapData->draw();
}

void TutoPlay::drawUI()
{
	m_GamePlayUI->draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "チュートリアル画面です。", GetColor(255, 0, 0));
	//DrawString(0, 20, "Spaceキーを押すとゲームオーバー画面に移行します。", GetColor(255, 0, 0));
#endif


	if (pausecount == 1)
	{
		m_Renderer->drawTexture("Pauseback", 0, 0);

		static int poition[3] = {
			300, 550, 50
		};

		//m_Renderer->drawTexture("Pause_Cursor", 540, poition[NowSelect]);

		switch (NowSelect){
		case pMenu_play:
			m_Renderer->drawTexture("Pause_Cursor", 540, 50);
			break;
		case pMenu_title:
			m_Renderer->drawTexture("Pause_Cursor", 540, 300);
			break;
		case pMenu_end:
			m_Renderer->drawTexture("Pause_Cursor", 540, 550);
			break;
		}
		m_Renderer->drawTexture("Pause", 100, 50);

		m_Renderer->drawTexture("Back", 640, 50);

		m_Renderer->drawTexture("TitleBack", 640, 300);

		m_Renderer->drawTexture("GameEnd", 640, 550);
	}
}

	void TutoPlay::drawMain()
	{
		m_CharacterManager->draw();
		m_EffectManager->draw();
		m_View->draw();
	}

	void TutoPlay::Pause()
	{
		//パッドのスタートボタンに変える
		if (m_GamePad->getInputButton(PAD_INPUT_1) == State::STATE_DOWN || Key_Get(KEY_INPUT_LSHIFT) == 1)
			pausecount = true;
	}

	void TutoPlay::PauseMenu()
	{
		if (m_GamePad->getInputButton(PAD_INPUT_DOWN) == State::STATE_DOWN){
			NowSelect = (NowSelect + 1) % eMenu_Num;
		}
		if (m_GamePad->getInputButton(PAD_INPUT_UP) == State::STATE_DOWN){
			NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;
		}
		if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || CheckHitKey(KEY_INPUT_RETURN) == 1){
			switch (NowSelect){
				//プレイ画面に戻る
			case pMenu_play:
				pausecount = false;
				break;
				//タイトルに戻る
			case pMenu_title:
				m_SceneChanger->ChangeScene(eScene_Title);
				break;
				//ゲームを終了する
			case pMenu_end:
				exit(0);
				break;
			}
		}
	}