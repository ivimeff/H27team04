#include "GamePlay.h"
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include"Block.h"
#include <DxLib.h>
//#include <time.h>
#include <sstream>
#include "Keyboard.h"

typedef enum{
	pMenu_title,
	pMenu_end,
	pMenu_play,

	eMenu_Num,
}pMenu;

static int NowSelect = pMenu_play;

GamePlay::GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Changer, _Sound)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, _Renderer, camera);
	gamePlayBundle = new GamePlayBundle(_DataManager, _Sound, m_Renderer, m_pMapData, camera, _GamePad, nullptr);
	m_CharacterManager = new CharacterManager(gamePlayBundle);
	gamePlayBundle->mediator = (ICharacterMediator*)m_CharacterManager;
	m_GamePlayUI = new GamePlayUI(_DataManager);
	m_View = new View(_DataManager);
}

GamePlay::~GamePlay()
{
	delete camera;
	delete m_pMapData;
	delete gamePlayBundle;
	delete m_CharacterManager;
}

void GamePlay::Initialize()
{
	end = false;
	m_pMapData->init();
	m_CharacterManager->init();
	m_CharacterManager->GenericControll<Character>::addObj(new Player(gamePlayBundle, def::Vector2(200, 200)));
	m_CharacterManager->GenericControll<Character>::addObj(new Block(gamePlayBundle, def::Vector2(350, 400)));
	pausecount = false;
	m_GamePlayUI->init();
	m_View->init();
	m_pSound->play("GamePlayBGM");
}

void GamePlay::Update()
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
		if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
		{
			//m_pSound->stop("GamePlayBGM");
			end = true;
		}

		if (CheckHitKey(KEY_INPUT_SPACE) != 0){	//スペースが押されたら
			m_pSound->stop("GamePlayBGM");
			m_SceneChanger->ChangeScene(eScene_GameOver);//ゲームオーバーに変更
		}

		if (m_CharacterManager->isGoal())
		{
			m_pSound->stop("GamePlayBGM");
			m_SceneChanger->ChangeScene(eScene_GameClear);
			return;
		}
	}
	m_GamePlayUI->updata();
	m_View->updata();
	m_View->SetPosition(m_CharacterManager->GetPlayerPosition());

	GetViewSize = m_View->Energie;
	m_GamePlayUI->SetViewSize(GetViewSize);
}

void GamePlay::drawBack()
{
	// 速度計測用の処理(コメントアウトを解除すれば確認出来る)
	//clock_t sTime = clock();
	m_pMapData->draw();
	//clock_t eTime = clock();
	//std::ostringstream ostr;
	//ostr << eTime - sTime;
	//m_Renderer->drawString(ostr.str().c_str(), 0, 64, 0xff0000ff);
}
//
//void GamePlay::Draw()
//{
//
//}
//
void GamePlay::drawUI()
{
	m_GamePlayUI->draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "設定画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Spaceキーを押すとゲームオーバー画面に移行します。", GetColor(255, 0, 0));
#endif


	if (pausecount == 1)
	{
		m_Renderer->drawTexture(m_pDataManager->pauseback, 0, 0);

		switch (NowSelect){
		case pMenu_play:
			m_Renderer->drawTexture(m_pDataManager->pause_cursor, 540, 50);
			break;
		case pMenu_title:
			m_Renderer->drawTexture(m_pDataManager->pause_cursor, 540, 300);
			break;
		case pMenu_end:
			m_Renderer->drawTexture(m_pDataManager->pause_cursor, 540, 550);
			break;
		}
		m_Renderer->drawTexture(m_pDataManager->pause, 100, 50);

		m_Renderer->drawTexture(m_pDataManager->back, 640, 50);

		m_Renderer->drawTexture(m_pDataManager->titleback, 640, 300);

		m_Renderer->drawTexture(m_pDataManager->gameend, 640, 550);

	}


}

void GamePlay::drawMain()
{
	//clock_t sTime = clock();
	m_CharacterManager->draw();
	m_View->draw();
}

void GamePlay::Pause()
{
	//パッドのスタートボタンに変える
	if (m_GamePad->getInputButton(PAD_INPUT_1) == State::STATE_DOWN || Key_Get(KEY_INPUT_LSHIFT) == 1)
		pausecount = true;
}

void GamePlay::PauseMenu()
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
			exit(-1);
			break;
		}
	}
}