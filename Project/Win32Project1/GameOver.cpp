#include "GameOver.h"
#include "Keyboard.h"
#include <DxLib.h>

GameOver::GameOver(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Changer, _Sound) {}

void GameOver::Initialize()
{
	end = fadeInFlg = false;
	mImageHandle = LoadGraph("Image/over.png");
	m_pSound->playBGM("GameOver");
}

void GameOver::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_RETURN) != 0){	//エンターが押されたら
		m_pSound->stop("GameOver");
		m_SceneChanger->ChangeScene(eScene_Title);//タイトルに変更
		fadeInFlg = true;
	}
}

void GameOver::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "ゲームオーバー画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Enterキーを押すとタイトル画面に戻ります。", GetColor(255, 0, 0));
#endif

	if (isPushButton())
	{
		m_Renderer->drawTexture("Push_b", window::width - 900, 500);
	}
}
