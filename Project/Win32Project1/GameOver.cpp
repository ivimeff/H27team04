#include "GameOver.h"
#include <DxLib.h>

GameOver::GameOver(DataManager *_DataManager, Renderer* _Renderer, GamePad* _GamePad, ISceneChanger* _Changer) : Scene(_DataManager, _Renderer, _GamePad, _Changer) {}

void GameOver::Initialize ()
{
	end = false;
	mImageHandle = LoadGraph("Image/over.png");
}

void GameOver::Update()
{
	if (m_GamePad->getInputButton(PAD_INPUT_10) == State::STATE_DOWN)
	{
		end = true;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) != 0){	//エンターが押されたら
		m_SceneChanger->ChangeScene(eScene_Title);//タイトルに変更
	}
}

void GameOver::Draw()
{
	//m_Renderer->drawTexture(m_pDataManager->over, over_x, over_y);
	Scene::Draw();
	//文字表示
	DrawString(0, 0, "設定画面です。", GetColor(255, 0, 0));
	DrawString(0, 20, "Enterキーを押すとタイトル画面に戻ります。", GetColor(255, 0, 0));

}
