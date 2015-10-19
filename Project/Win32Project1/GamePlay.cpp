#include "GamePlay.h"
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include <DxLib.h>

GamePlay::GamePlay(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad,ISceneChanger* _Changer) : Scene(_DataManager, _Renderer, _GamePad,_Changer)
{
	camera = new Camera();
	m_pMapData = new MapData(_DataManager, _Renderer, camera);
	gamePlayBundle = new GamePlayBundle(_DataManager, m_Renderer, m_pMapData, camera, _GamePad);
	m_CharacterManager = new CharacterManager(gamePlayBundle);
}

GamePlay::~GamePlay()
{
	delete m_CharacterManager;
}

void GamePlay::Initialize()
{
	end = false;
	m_pMapData->init();
	m_CharacterManager->init();
	m_CharacterManager->add(new Player(gamePlayBundle, def::Vector2(200, 200)));
}

void GamePlay::Update()
{
	m_pMapData->update();
	m_CharacterManager->update();
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) != 0){	//スペースが押されたら
		m_SceneChanger->ChangeScene(eScene_GameOver);//ゲームオーバーに変更
	}
}

void GamePlay::Draw()
{
	m_pMapData->draw();
	m_CharacterManager->draw();

	Scene::Draw();
	//文字表示
	DrawString(0, 0, "設定画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Spaceキーを押すとゲームオーバー画面に移行します。", GetColor(255, 0, 0));

}