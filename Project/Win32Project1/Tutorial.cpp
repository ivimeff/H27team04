#include "Tutorial.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial::Tutorial(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Change, SoundManager* _Sound) : Scene(_DataManager, _Renderer, _GamePad, _Change, _Sound)
{

}

void Tutorial::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/tuto.png");
}

void Tutorial::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_SPACE) != 0){	//スペースが押されたら
		m_pSound->play("Menu");
		m_SceneChanger->ChangeScene(eScene_Tutorial2);//メニューに変更
	}
}

void Tutorial::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "設定画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Spaceキーを押すとメニュー画面に戻ります。", GetColor(255, 0, 0));
#endif
}

