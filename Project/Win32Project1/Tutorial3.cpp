#include "Tutorial3.h"
#include "Keyboard.h"
#include <stdio.h>
#include <DxLib.h>

Tutorial3::Tutorial3(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Change) : Scene(_DataManager, _Renderer, _GamePad, _Change)
{

}

void Tutorial3::Initialize()
{
	end = false;
	mImageHandle = LoadGraph("Image/tuto3.png");
}

void Tutorial3::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (m_GamePad->getInputButton(PAD_INPUT_2) == State::STATE_DOWN || Key_Get(KEY_INPUT_SPACE) != 0){	//スペースが押されたら
		m_SceneChanger->ChangeScene(eScene_Menu);//メニューに変更
	}
}

void Tutorial3::Draw()
{
	Scene::Draw();

#ifdef _DEBUG
	//文字表示
	DrawString(0, 0, "チュートリアル画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Spaceキーを押すとメニュー画面に戻ります。", GetColor(255, 0, 0));
#endif
}