#include "GameTitle.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

GameTitle::GameTitle(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Changer, _Sound) {}

void GameTitle::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/title.png");
	//mImageHandle = LoadGraph("Image/title2.png");
	timer = 0;
	m_pSound->playBGM("TitleBGM");
}

void GameTitle::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	//スペースorパッドのAボタンが押されたら
	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_SPACE) != 0){
		m_pSound->play("Menu");
		//m_pSound->stopBGM();
		m_SceneChanger->ChangeScene(eScene_Menu);//メニューに変更
	}
	timer++;
}

void GameTitle::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "設定画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Spaceキーを押すとメニュー画面に移行します。", GetColor(255, 0, 0));
#endif

	if ((timer % 100) < 50)
	{
		m_Renderer->drawTexture("Push_b", window::width - 900, 500);
	}

}
